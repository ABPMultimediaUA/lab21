#include "NetGame.h"
#include "GraphicsEngine.h"
#include "RakSleep.h"
#include "NetCommon.h"

#include <iostream>
#include <vector>
#include <unistd.h>  //para sleep

#include "WorldInstance.h"
#include "DrawableReplica.h"
#include "Player.h"
#include "PlayerMate.h"
#include "Entity.h"
#include "Door.h"
#include "Generator.h"
#include "Scene.h"
#include "Consumable.h"
#include "Enemy.h"


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
void dwn::NetGame::open(Scene *scene, bool multiplayer)
{
    m_connected = false;
    m_connectionFailed = false;
    m_connectionRejected = false;
    m_gameStarted = false;
    m_participantOrder = 0;
    m_isServer = false;
    m_numNetEntities = 0;
    m_numNetConsumables = 0;
    m_numNetEnemies = 0;
    m_netEnemyIndex = 0;
    m_scene = scene;
    m_multiplayer = multiplayer;
    m_gamesSearched = false;

    // RakPeerInterface es la base de RakNet para comunicaciones UDP
	rakPeer=RakNet::RakPeerInterface::GetInstance();

	// Buscamos un puerto v�lido. Using fixed port so we can use AdvertiseSystem and connect on the LAN if the server is not available.
	RakNet::SocketDescriptor sd(1234,0);
	sd.socketFamily=AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
	while (RakNet::IRNS2_Berkley::IsPortInUse(sd.port, sd.hostAddress, sd.socketFamily, SOCK_DGRAM)==true)
		sd.port++;

	// StartupResult solo sirve para hacer el assert y comprobar que ha ido bien
	if (m_multiplayer)
        rakPeer->Startup(_max_players+1,&sd,1);// +1 is for the connection to the NAT punchthrough server

	// Configuraciones de RakPeerInterface
	rakPeer->SetMaximumIncomingConnections(_max_players);
	rakPeer->SetTimeoutTime(5000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);   // Fast disconnect for easier testing of host migration


	// ReplicaManager3 replies on NetworkIDManager.
	// It assigns numbers to objects so they can be looked up over the network
	// It's a class in case you wanted to have multiple worlds,
	// then you could have multiple instances of NetworkIDManager
	networkIDManager = new RakNet::NetworkIDManager;

	// ReplicaManager3 se encarga de la gesti�n de objetos replicados
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


    // Buscar servidores disponibles
    /*if (m_multiplayer)
    {
        RakNet::TimeMS quitTime;
        RakNet::Packet* p;
        std::vector<std::string> dirs;

        quitTime = RakNet::GetTimeMS() + _time_search_server;  // milisegundos de espera
        cout << "//\n// Buscando servidores ";

        rakPeer->Ping("255.255.255.255", DEFAULT_PT, false);
        while (RakNet::GetTimeMS() < quitTime)
        {
            cout << ".";
            p = rakPeer->Receive();

            if (p==0)
            {
                RakSleep(60);
                continue;
            }

            if (p->data[0]==ID_UNCONNECTED_PONG)
            {
                RakNet::TimeMS time;
                RakNet::BitStream bsIn(p->data,p->length,false);
                bsIn.IgnoreBytes(1);
                bsIn.Read(time);
                dirs.push_back(p->systemAddress.ToString());
                //printf("Got pong from %s with time %i\n", p->systemAddress.ToString(), RakNet::GetTimeMS() - time);
            }
            rakPeer->DeallocatePacket(p);

            RakSleep(60);
        }

        if (dirs.size()>0)
        {
            cout << "\n//\n//Servidores de partidas disponibles:\n";

            for(unsigned int i=0; i<dirs.size(); i++)
                cout << "//  ("<<i<<") " << dirs[i] << "\n";

            cout << "// Seleccione el numero de servidor de partidas [0] por defecto]: ";

            getline(cin, m_IP);
            m_IP = dirs[atoi(m_IP.c_str())];  // Si no es valido, o es "", atoi devuelve 0
        }
        else
        {
            cout << "\n// No hay servidores disponibles. Se inicia en modo un jugador. Presione una tecla para continuar.\n";
            getchar();
            m_multiplayer = false;
        }
    }


	// Connect to the NAT punchthrough server
	if (m_multiplayer)
       rakPeer->Connect(m_IP.c_str(), DEFAULT_PT,0,0);

    // Esperamos a conectar
    if (m_multiplayer)
    {
        cout << "// Conectando...\n";
        while (!m_connected && !m_connectionFailed && !m_connectionRejected)
        {
            usleep(40000);
            update();
        }
    }
    if (m_connectionFailed)
    {
        cout << "No se encuentra el servidor " << m_IP << ", se inicia el juego en modo 1 jugador.\n";
        cout << "Presione intro para continuar. ";
        getchar();
    }
    else if (m_connectionRejected)
    {
        m_multiplayer = false;
        cout << "No se puede acceder a la partida seleccionada. Partida llena o empezada, se inicia el juego en modo 1 jugador.\n";
        cout << "Presione intro para continuar. ";
        getchar();
    }*/
}

//////////////
void NetGame::close()
{
    rakPeer->Shutdown(100,0);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
	m_connected = false;
	delete networkIDManager;
	delete replicaManager3;
	delete natPunchthroughClient;
	delete cloudClient;
	delete fullyConnectedMesh2;
}


void PushMessage(RakNet::RakString rs)
{
    std::cout << " <><><>NETENGINE<><><> "<< rs << "\n";
}

///////////////////
bool dwn::NetGame::searchForServers()
{
    // Buscar servidores disponibles
    if (m_multiplayer)
    {
        RakNet::TimeMS quitTime;
        RakNet::Packet* p;
        m_servers.clear();

        quitTime = RakNet::GetTimeMS() + _time_search_server;  // milisegundos de espera

        rakPeer->Ping("255.255.255.255", DEFAULT_PT, false);
        while (RakNet::GetTimeMS() < quitTime)
        {
            p = rakPeer->Receive();

            if (p==0)
            {
                RakSleep(60);
                continue;
            }

            if (p->data[0]==ID_UNCONNECTED_PONG)
            {
                RakNet::TimeMS time;
                RakNet::BitStream bsIn(p->data,p->length,false);
                bsIn.IgnoreBytes(1);
                bsIn.Read(time);
                m_servers.push_back(p->systemAddress.ToString());
            }
            rakPeer->DeallocatePacket(p);

            RakSleep(60);
        }

        return (m_servers.size()>0);
    }
    else
    {
        cout << "\nError: para buscar servidores debe ser una partida multiplayer\n";
        return false;
    }
}


///////////////////
bool dwn::NetGame::connectToServer(unsigned int i)
{
    if (m_multiplayer)
    {
        if(m_servers.size()>0)
        {
            if (i<m_servers.size())
            {
                m_IP = m_servers[i];
                rakPeer->Connect(m_IP.c_str(), DEFAULT_PT,0,0);

                // Conectamos
                while (!m_connected && !m_connectionFailed && !m_connectionRejected)
                {
                    usleep(40000);
                    update();
                }

                return (m_connected && !m_connectionFailed && !m_connectionRejected);
            }
            else
            {
                cout << "\nError: el indice del servidor no existe\n";
                return false;
            }
        }
        else
        {
            cout << "\nError: no hay servidores disponibles\n";
            return false;
        }
    }
    else
    {
        cout << "\nError: para conectar a un servidor debe ser una partida multiplayer\n";
        return false;
    }
}

///////////////////
bool dwn::NetGame::connectToGame(unsigned int i)
{
    m_isServer = (i==0);
    if (m_isServer)
    {
        PushMessage(RakNet::RakString("Creando nueva partida"));
        m_connected = true;

        // Start as a new game instance because no other games are running
        RakNet::CloudKey cloudKey(NET_CLOUD_KEY,0);
        cloudClient->Post(&cloudKey, 0, 0, m_cloudServerGUID);
    }
    else
    {
      	RakNet::SystemAddress serverSystemAddress(m_IP.c_str(), DEFAULT_PT);
        PushMessage(RakNet::RakString("NAT punch to existing game instance"));
        natPunchthroughClient->OpenNAT(m_gamesGUID[i-1], serverSystemAddress);
    }

    return true;
}


////////////////////////////////////////
std::vector<std::string>* dwn::NetGame::getServers() {return &m_servers;}
////////////////////////////////////////
std::vector<std::string>* dwn::NetGame::getGamesIP() {return &m_gamesIP;}


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
	RakNet::SystemAddress facilitatorSystemAddress(m_IP.c_str(), DEFAULT_PT);
	RakNet::Packet *packet;
	RakNet::TimeMS curTime = RakNet::GetTimeMS();
	RakNet::RakString targetName;
	for (packet=rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet=rakPeer->Receive())
	{
		if (strcmp(packet->systemAddress.ToString(false),m_IP.c_str())==0)
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
            PushMessage(RakNet::RakString("La partida en el servidor est� completa ") + targetName + RakNet::RakString("."));
            if (packet->systemAddress==facilitatorSystemAddress)
                PushMessage("Multiplayer will not work without the NAT punchthrough server!");
			break;

		case ID_NEW_INCOMING_CONNECTION:
            if (fullyConnectedMesh2->IsHostSystem())
            {
                // Cuando es el primer juego que se ha creado y accede un nuevo jugador
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
		    {
                // Controlamos que la partida no ha empezado y que no est� completa
                bool aceptar = (getNumPlayerMates() < MAX_PLAYERS  && !m_gameStarted);
                fullyConnectedMesh2->RespondOnVerifiedJoinCapable(packet, aceptar, 0);
		    }
			break;

		case ID_FCM2_VERIFIED_JOIN_ACCEPTED:
		    {
                DataStructures::List<RakNet::RakNetGUID> systemsAccepted;
                bool thisSystemAccepted;
                fullyConnectedMesh2->GetVerifiedJoinAcceptedAdditionalData(packet, &thisSystemAccepted, systemsAccepted, 0);
                if (thisSystemAccepted){
                    PushMessage("Game join request accepted\n");
                    m_connected = true;
                }else
                    PushMessage(RakNet::RakString("System %s joined the mesh\n", systemsAccepted[0].ToString()));

                for (unsigned int i=0; i < systemsAccepted.Size(); i++)
                    replicaManager3->PushConnection(replicaManager3->AllocConnection(rakPeer->GetSystemAddressFromGuid(systemsAccepted[i]), systemsAccepted[i]));
		    }
			break;

		case ID_FCM2_VERIFIED_JOIN_REJECTED:
		    {
		        PushMessage(RakNet::RakString("rejected"));
		        m_connectionRejected = true;
		        // desconectar y marcar como no conectado
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

                // Buscamos partidas en servidor
                int maxPartidas=cloudQueryResult.rowsReturned.Size();
                m_gamesIP.clear();
                m_gamesGUID.clear();
                //cout << "//  (0) Crear una nueva partida.\n";
                if (maxPartidas>0)
                {
                    for(int i=0; i<maxPartidas; i++)
                    {
                        m_gamesIP.push_back(cloudQueryResult.rowsReturned[i]->clientSystemAddress.ToString());
                        m_gamesGUID.push_back(cloudQueryResult.rowsReturned[i]->clientGUID);
                        //cout << "//  ("<<i+1<<") Unirse a " << cloudQueryResult.rowsReturned[i]->clientSystemAddress.ToString() << "\n";
                    }
                }

                m_cloudServerGUID = packet->guid;
                m_connected = true;

                /*std::string seleccion;
                cout << "// Selecciona partida: ";
                getline(cin, seleccion);

                m_isServer = (seleccion=="0");
                if (m_isServer)
                {
                    PushMessage(RakNet::RakString("Creando nueva partida"));
                    m_connected = true;

                    // Start as a new game instance because no other games are running
                    RakNet::CloudKey cloudKey(NET_CLOUD_KEY,0);
                    cloudClient->Post(&cloudKey, 0, 0, packet->guid);
                }
                else
                {
                    PushMessage(RakNet::RakString("NAT punch to existing game instance"));
                    //natPunchthroughClient->OpenNAT(cloudQueryResult.rowsReturned[atoi(seleccion.c_str())-1]->clientGUID, facilitatorSystemAddress);
                    natPunchthroughClient->OpenNAT(m_gamesGUID[i-1], facilitatorSystemAddress);
                }*/

                cloudClient->DeallocateWithDefaultAllocator(&cloudQueryResult);

                m_gamesSearched = true;
		    }
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
            PushMessage(RakNet::RakString("\nConnection attempt to ") + targetName + RakNet::RakString(" failed."));
            m_connectionFailed = true;
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
                rakPeer->Connect(packet->systemAddress.ToString(false), packet->systemAddress.GetPort(), 0, 0);
            }
			break;

		case ID_ADVERTISE_SYSTEM:
			if (packet->guid!=rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
			{
				char hostIP[32];
				packet->systemAddress.ToString(false,hostIP);
				rakPeer->Connect(hostIP,packet->systemAddress.GetPort(),0,0);
			}
			break;

        case ID_GAME_PARTICIPANT_ORDER:
            {
				RakNet::BitStream bsIn(packet->data,packet->length,false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

				bsIn.Read(m_participantOrder);
                break;
            }
        case ID_GAME_STARTED:
            {
                PushMessage(RakNet::RakString("Empieza el juego"));
                m_gameStarted = true;
                break;
            }
        case ID_DOOR_OPEN:
        case ID_DOOR_CLOSE:
            {
				unsigned int entityID = getBitStreamEntityID(packet);

				if (entityID<m_numNetEntities)
                {
                    if (packet->data[0] == ID_DOOR_OPEN)
                        ((Door*)m_netEntities[entityID])->setIsOpening();
                    else
                        ((Door*)m_netEntities[entityID])->setIsClosing();
                }
                break;
            }
        case ID_GENERATOR_ACTIVE:
            {
				unsigned int entityID = getBitStreamEntityID(packet);
				if (entityID<m_numNetEntities)
                    ((Generator*)m_netEntities[entityID])->activateGenerator();
                break;
            }
        case ID_PROJECTILE_CREATE:
            {
                dwe::vec3f position;
                float angle;

                RakNet::BitStream bsIn(packet->data,packet->length,false);
                bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
                bsIn.Read(position);
                bsIn.Read(angle);

                m_scene->createProjectile(position, angle);
                break;
            }
        case ID_CONSUMABLE_TAKEN:
            {
				unsigned int consumableID = getBitStreamEntityID(packet);
				if (consumableID<m_numNetConsumables)
                    (m_netConsumables[consumableID])->take();
                break;
            }
        case ID_ENEMY_UPDATE:
            {
                unsigned int enemyID;
                dwe::vec3f position;
                dwe::vec3f rotation;

                RakNet::BitStream bsIn(packet->data,packet->length,false);
                bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
                bsIn.Read(enemyID);
                bsIn.Read(position);
                bsIn.Read(rotation);

                if (enemyID<m_numNetEnemies)
                {
                    (m_netEnemies[enemyID])->setPosition(position);
                    (m_netEnemies[enemyID])->setRotation(rotation);
                }
                break;
            }
        case ID_SEND_MEDKIT:
            {
                RakNet::RakString value;
                RakNet::BitStream bsIn(packet->data,packet->length,false);
                bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
                bsIn.Read(value);

                // Si player coincide con la cadena que manda, a�adimos medkit
                if (value == World->getMainPlayer()->creatingSystemGUID.ToString())
                    World->getMainPlayer()->addMedkits(1);
                break;
            }

		}
	}

	// Actualizamos las posiciones de los objetos replicables replicamanager3
	unsigned int idx;
	for (idx=0; idx < replicaManager3->GetReplicaCount(); idx++)
		((DrawableReplica*)(replicaManager3->GetReplicaAtIndex(idx)))->update(curTime);

    // Realizamos los ajustes de la posici�n/rotaci�n de los enemigos, 1 por cada update para
    // no sobrecargar. Solo si somos el host enviamos la info.
    if (fullyConnectedMesh2->IsHostSystem() && m_numNetEntities>0)
    {
        sendBroadcast(ID_ENEMY_UPDATE, m_netEnemyIndex, ((Enemy*)(m_netEnemies[m_netEnemyIndex]))->getPosition(), ((Enemy*)(m_netEnemies[m_netEnemyIndex]))->getRotation());
        m_netEnemyIndex = (m_netEnemyIndex < m_numNetEnemies-1)? m_netEnemyIndex+1 : 0;
    }
}

//////////////////////
unsigned int NetGame::getBitStreamEntityID(Packet *packet)
{
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

    unsigned int entityID;
    bsIn.Read(entityID);

    return entityID;
}

//////////////
bool NetGame::isMultiplayer() { return m_multiplayer; }
//////////////
bool NetGame::isServer() { return m_isServer; }

//////////////
bool NetGame::getConnected() { return m_connected; }
//////////////
bool NetGame::getConnectionFailed() { return m_connectionFailed; }
//////////////
bool NetGame::getConnectionRejected() { return m_connectionRejected; }
//////////////
bool NetGame::getGamesSearched() { return m_gamesSearched; }
//////////////
void NetGame::setMultiplayer(bool m) { m_multiplayer = m; }


////////////////////////
unsigned short NetGame::getParticipantOrder()
{
    return m_participantOrder;
}

///////////////////
void dwn::NetGame::addNetObject(dwn::DrawableReplica *drawReplica)
{
    replicaManager3->Reference(drawReplica);
}

///////////////////
void dwn::NetGame::addNetEntity(Entity* entity)
{
    m_netEntities[m_numNetEntities] = entity;
    entity->setNetID(m_numNetEntities);
    m_numNetEntities++;
}

///////////////////
void dwn::NetGame::addNetConsumable(Consumable* consumable)
{
    m_netConsumables[m_numNetConsumables] = consumable;
    consumable->setNetID(m_numNetConsumables);
    m_numNetConsumables++;
}

///////////////////
void dwn::NetGame::addNetEnemy(Enemy* enemy)
{
    m_netEnemies[m_numNetEnemies] = enemy;
    enemy->setNetID(m_numNetEnemies);
    m_numNetEnemies++;
}

///////////////////
bool dwn::NetGame::isLocalObject(RakNet::RakNetGUID id)
{
    return (id == rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS));
}

//////////////////////////
PlayerMate* dwn::NetGame::getPlayerMate(unsigned int i)
{
    if (i<replicaManager3->GetReplicaCount())
        return (PlayerMate*)(replicaManager3->GetReplicaAtIndex(i));
    else
        return NULL;
}

//////////////////
int dwn::NetGame::getNumPlayerMates() { return replicaManager3->GetReplicaCount(); }

///////////////////
void dwn::NetGame::startGame()
{
    if (fullyConnectedMesh2->IsHostSystem())
    {
        RakNet::SystemAddress serverAddress(m_IP.c_str(), DEFAULT_PT);
        // Envio el comienzo de partida con broadcast a todos los participantes, menos al server
        RakNet::BitStream bsOut;
        bsOut.Write((RakNet::MessageID)ID_GAME_STARTED);
        rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);

        m_gameStarted = true;
    }
}


///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, unsigned int value)
{
    RakNet::SystemAddress serverAddress(m_IP.c_str(), DEFAULT_PT);
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(value);
    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, RakNet::RakString  value)
{
    RakNet::SystemAddress serverAddress(m_IP.c_str(), DEFAULT_PT);
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(value);
    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, dwe::vec3f position, float angle)
{
    RakNet::SystemAddress serverAddress(m_IP.c_str(), DEFAULT_PT);
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(position);
    bsOut.Write(angle);
    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, unsigned int objectID, dwe::vec3f position, dwe::vec3f rotation)
{
    RakNet::SystemAddress serverAddress(m_IP.c_str(), DEFAULT_PT);
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(objectID);
    bsOut.Write(position);
    bsOut.Write(rotation);
    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);
}


///////////////////
bool dwn::NetGame::getGameStarted() { return m_gameStarted; }

////////////////////////////////////////////////
RakNet::Replica3* dwn::NetGame::Connection_RM3DireW::AllocReplica(RakNet::BitStream* allocationId, RakNet::ReplicaManager3* replicaManager3)
{
    // Obtiene el mensaje desde Replica3::WriteAllocationID
    // Seg�n este mensaje crearemos un objeto u otro.
	RakNet::RakString typeName;
	allocationId->Read(typeName);

	if (typeName == "Player")
    {
        PlayerMate* obj = GEInstance->createPlayerMate();
        return obj;
    }
    else
        return 0;
}


