#include "NetGame.h"
#include "MessageIdentifiers.h"
#include "GraphicsEngine.h"
#include <iostream>

#include "DrawableReplica.h"
#include "Player.h"
#include "PlayerMate.h"

using namespace dwn;

dwn::NetGame::NetGame()
{

}

dwn::NetGame* NetGame::Instance()
{
    static NetGame instance;
    return &instance;
}

dwn::NetGame::~NetGame()
{
    //dtor
}

//////////////
void dwn::NetGame::open()
{
    // RakPeerInterface es la base de RakNet para comunicaciones UDP
	rakPeer=RakNet::RakPeerInterface::GetInstance();

	// Buscamos un puerto válido. Using fixed port so we can use AdvertiseSystem and connect on the LAN if the server is not available.
	RakNet::SocketDescriptor sd(1234,0);
	sd.socketFamily=AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
	while (RakNet::IRNS2_Berkley::IsPortInUse(sd.port, sd.hostAddress, sd.socketFamily, SOCK_DGRAM)==true)
		sd.port++;

	// StartupResult solo sirve para hacer el assert y comprobar que ha ido bien
	RakNet::StartupResult sr = rakPeer->Startup(_max_players+1,&sd,1);// +1 is for the connection to the NAT punchthrough server
	RakAssert(sr==RakNet::RAKNET_STARTED);

	// Configuraciones de RakPeerInterface
	rakPeer->SetMaximumIncomingConnections(_max_players);
	rakPeer->SetTimeoutTime(5000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);   // Fast disconnect for easier testing of host migration


	// ReplicaManager3 replies on NetworkIDManager.
	// It assigns numbers to objects so they can be looked up over the network
	// It's a class in case you wanted to have multiple worlds,
	// then you could have multiple instances of NetworkIDManager
	networkIDManager = new RakNet::NetworkIDManager;

	// ReplicaManager3 se encarga de la gestión de objetos replicados
	// Automatically sends around new / deleted / changed game objects
	replicaManager3 = new ReplicaManager3DireW;
	replicaManager3->SetNetworkIDManager(networkIDManager);
	rakPeer->AttachPlugin(replicaManager3);
    // Automatically destroy connections, but don't create them so we have more control over when a system is considered ready to play
	replicaManager3->SetAutoManageConnections(false,true);

	// Poder conectar entre routers
	natPunchthroughClient = new RakNet::NatPunchthroughClient;
	rakPeer->AttachPlugin(natPunchthroughClient);

	// Uploads game instance, basically client half of a directory server
	// Server code is in NATCompleteServer sample
	cloudClient = new RakNet::CloudClient;
	rakPeer->AttachPlugin(cloudClient);

	// Conecta rakPeer con todas las conexiones
	fullyConnectedMesh2 = new RakNet::FullyConnectedMesh2;
	fullyConnectedMesh2->SetAutoparticipateConnections(false);
	fullyConnectedMesh2->SetConnectOnNewRemoteConnection(false, "");
	rakPeer->AttachPlugin(fullyConnectedMesh2);


	// Connect to the NAT punchthrough server
	RakNet::ConnectionAttemptResult car = rakPeer->Connect(DEFAULT_IP, DEFAULT_PT,0,0);
	RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
}

//////////////
void NetGame::close()
{
    rakPeer->Shutdown(100,0);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
	delete networkIDManager;
	delete replicaManager3;
	delete natPunchthroughClient;
	delete cloudClient;
	delete fullyConnectedMesh2;
}


void PushMessage(RakNet::RakString rs)
{
    std::cout << rs << "\n";
}

///////////////////////
RakNet::RakString dwn::NetGame::getNATTargetName(RakNet::Packet* p)
{
    RakNet::RakNetGUID recipientGuid;
    RakNet::BitStream bs(p->data, p->length, false);
    bs.IgnoreBytes(sizeof(RakNet::MessageID));
    bs.Read(recipientGuid);

    return recipientGuid.ToString();
}

//////////////
void dwn::NetGame::update()
{
	RakNet::SystemAddress facilitatorSystemAddress(DEFAULT_IP, DEFAULT_PT);
	RakNet::Packet *packet;
	RakNet::TimeMS curTime = RakNet::GetTimeMS();
	RakNet::RakString targetName;
	for (packet=rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet=rakPeer->Receive())
	{
		if (strcmp(packet->systemAddress.ToString(false),DEFAULT_IP)==0)
			targetName="NATPunchthroughServer";
		else
			targetName=packet->systemAddress.ToString(true);

		switch (packet->data[0])
		{
		case ID_IP_RECENTLY_CONNECTED:
		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
            PushMessage(RakNet::RakString("Incompatible protocol version from ") + targetName + RakNet::RakString("."));
            if (packet->systemAddress==facilitatorSystemAddress)
                PushMessage("Multiplayer will not work without the NAT punchthrough server!");
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			PushMessage(RakNet::RakString("Disconnected from ") + targetName + RakNet::RakString("."));
			break;

		case ID_CONNECTION_LOST:
			PushMessage(RakNet::RakString("Connection to ") + targetName + RakNet::RakString(" lost."));
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS:
            PushMessage(RakNet::RakString("No free incoming connections to ") + targetName + RakNet::RakString("."));
            if (packet->systemAddress==facilitatorSystemAddress)
                PushMessage("Multiplayer will not work without the NAT punchthrough server!");
			break;

		case ID_NEW_INCOMING_CONNECTION:
            if (fullyConnectedMesh2->IsHostSystem())
            {
                PushMessage(RakNet::RakString("Sending player list to new connection"));
                fullyConnectedMesh2->StartVerifiedJoin(packet->guid);
            }
			break;

		case ID_FCM2_VERIFIED_JOIN_START:
		    {
                DataStructures::List<RakNet::SystemAddress> addresses;
                DataStructures::List<RakNet::RakNetGUID> guids;
                DataStructures::List<RakNet::BitStream*> userData;
                fullyConnectedMesh2->GetVerifiedJoinRequiredProcessingList(packet->guid, addresses, guids, userData);
                for (unsigned int i=0; i < guids.Size(); i++)
                    natPunchthroughClient->OpenNAT(guids[i], facilitatorSystemAddress);
		    }
			break;

		case ID_FCM2_VERIFIED_JOIN_FAILED:
			PushMessage(RakNet::RakString("Failed to join game session"));
			break;

		case ID_FCM2_VERIFIED_JOIN_CAPABLE:
			fullyConnectedMesh2->RespondOnVerifiedJoinCapable(packet, true, 0);
			break;

		case ID_FCM2_VERIFIED_JOIN_ACCEPTED:
		    {
                DataStructures::List<RakNet::RakNetGUID> systemsAccepted;
                bool thisSystemAccepted;
                fullyConnectedMesh2->GetVerifiedJoinAcceptedAdditionalData(packet, &thisSystemAccepted, systemsAccepted, 0);
                if (thisSystemAccepted)
                    PushMessage("Game join request accepted\n");
                else
                    PushMessage(RakNet::RakString("System %s joined the mesh\n", systemsAccepted[0].ToString()));

                for (unsigned int i=0; i < systemsAccepted.Size(); i++)
                    replicaManager3->PushConnection(replicaManager3->AllocConnection(rakPeer->GetSystemAddressFromGuid(systemsAccepted[i]), systemsAccepted[i]));
		    }
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
            PushMessage(RakNet::RakString("Connection request to ") + targetName + RakNet::RakString(" accepted."));
            if (packet->systemAddress==facilitatorSystemAddress)
            {
                // Query cloud for other running game instances
                RakNet::CloudQuery cloudQuery;
                cloudQuery.keys.Push(RakNet::CloudKey(NET_CLOUD_KEY,0),_FILE_AND_LINE_);
                cloudClient->Get(&cloudQuery, packet->guid);
            }
			break;

		case ID_FCM2_NEW_HOST:
            if (packet->guid==rakPeer->GetMyGUID())
            {
                // Original host dropped. I am the new session host. Upload to the cloud so new players join this system.
                RakNet::CloudKey cloudKey(NET_CLOUD_KEY,0);
                cloudClient->Post(&cloudKey, 0, 0, rakPeer->GetGuidFromSystemAddress(facilitatorSystemAddress));
            }
			break;

		case ID_CLOUD_GET_RESPONSE:
		    {
                RakNet::CloudQueryResult cloudQueryResult;
                cloudClient->OnGetReponse(&cloudQueryResult, packet);
                if (cloudQueryResult.rowsReturned.Size()>0)
                {
                    PushMessage(RakNet::RakString("NAT punch to existing game instance"));
                    natPunchthroughClient->OpenNAT(cloudQueryResult.rowsReturned[0]->clientGUID, facilitatorSystemAddress);
                }
                else
                {
                    PushMessage(RakNet::RakString("Publishing new game instance"));

                    // Start as a new game instance because no other games are running
                    RakNet::CloudKey cloudKey(NET_CLOUD_KEY,0);
                    cloudClient->Post(&cloudKey, 0, 0, packet->guid);
                }

                cloudClient->DeallocateWithDefaultAllocator(&cloudQueryResult);
		    }
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
            PushMessage(RakNet::RakString("Connection attempt to ") + targetName + RakNet::RakString(" failed."));
            if (packet->systemAddress==facilitatorSystemAddress)
                PushMessage("Multiplayer will not work without the NAT punchthrough server!");
			break;

		case ID_NAT_TARGET_NOT_CONNECTED:
            targetName=getNATTargetName(packet);
            PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" not connected."));
			break;

		case ID_NAT_TARGET_UNRESPONSIVE:
            targetName=getNATTargetName(packet);
            PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" unresponsive."));
			break;

		case ID_NAT_CONNECTION_TO_TARGET_LOST:
            targetName=getNATTargetName(packet);
            PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" connection to lost."));
			break;

		case ID_NAT_ALREADY_IN_PROGRESS:
            targetName=getNATTargetName(packet);
            PushMessage(RakNet::RakString("NAT punchthrough to ") + targetName + RakNet::RakString(" in progress (skipping)."));
			break;

		case ID_NAT_PUNCHTHROUGH_SUCCEEDED:
            if (packet->data[1]==1)
            {
                PushMessage(RakNet::RakString("Connecting to existing game instance"));
                RakNet::ConnectionAttemptResult car = rakPeer->Connect(packet->systemAddress.ToString(false), packet->systemAddress.GetPort(), 0, 0);
                RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
            }
			break;

		case ID_ADVERTISE_SYSTEM:
			if (packet->guid!=rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
			{
				char hostIP[32];
				packet->systemAddress.ToString(false,hostIP);
				RakNet::ConnectionAttemptResult car = rakPeer->Connect(hostIP,packet->systemAddress.GetPort(),0,0);
				RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
			}
			break;
		}
	}

	// Call the Update function for networked game objects added to BaseIrrlichtReplica once the game is ready
	unsigned int idx;
	for (idx=0; idx < replicaManager3->GetReplicaCount(); idx++)
		((DrawableReplica*)(replicaManager3->GetReplicaAtIndex(idx)))->update(curTime);;
}

//////////////
void dwn::NetGame::addNetObject(dwn::DrawableReplica *drawReplica)
{
    replicaManager3->Reference(drawReplica);
}

//////////////
bool dwn::NetGame::isLocalObject(RakNet::RakNetGUID id)
{
    return (id == rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS));
}


////////////////////////////////////////////////
RakNet::Replica3* dwn::NetGame::Connection_RM3DireW::AllocReplica(RakNet::BitStream* allocationId, RakNet::ReplicaManager3* replicaManager3)
{
    // Obtiene el mensaje desde Replica3::WriteAllocationID
    // Según este mensaje crearemos un objeto u otro.
	RakNet::RakString typeName;
	allocationId->Read(typeName);

	if (typeName == "Player") { PlayerMate* obj = GEInstance->createPlayerMate(); return obj; }
	else return 0;
}


