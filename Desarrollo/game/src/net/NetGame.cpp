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


dwn::NetGame::NetGame() : m_opened(false)
{
    createMappingMessageFunctions();
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
    m_opened = true;
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
    //m_scene = scene;
    m_multiplayer = multiplayer;
    m_gamesSearched = false;

    // RakPeerInterface es la base de RakNet para comunicaciones UDP
	rakPeer=RakNet::RakPeerInterface::GetInstance();

	// Buscamos un puerto válido. Using fixed port so we can use AdvertiseSystem and connect on the LAN if the server is not available.
	RakNet::SocketDescriptor sd(1234,0);
	unsigned int numLocalIPs = rakPeer->GetNumberOfAddresses();
	strcpy(sd.hostAddress, rakPeer->GetLocalIP(numLocalIPs-1));

	sd.socketFamily=AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
	while (RakNet::IRNS2_Berkley::IsPortInUse(sd.port, sd.hostAddress, sd.socketFamily, SOCK_DGRAM)==true)
		sd.port++;

	// StartupResult solo sirve para hacer el assert y comprobar que ha ido bien
	if (m_multiplayer)
        rakPeer->Startup(_max_players+1, &sd, 1);// +1 is for the connection to the NAT punchthrough server
    std::cout << "Usando red: " << sd.hostAddress << "\n";

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
}

//////////////
void NetGame::close()
{
    m_opened = false;
    rakPeer->Shutdown(100,0);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
	m_connected = false;
	delete networkIDManager;
	delete replicaManager3;
	delete natPunchthroughClient;
	delete cloudClient;
	delete fullyConnectedMesh2;
}

///////////////////
void dwn::NetGame::createMappingMessageFunctions()
{
    for(uint8_t i=0; i<NUM_CUSTOM_NET_MESSAGES; i++)
        mapMessagesFunctions[i].id_message = -1;

    mapMessagesFunctions[0].id_message  = ID_ACTIVE_ENEMY;
    mapMessagesFunctions[0].func        = &dwn::NetGame::activeEnemy;

    mapMessagesFunctions[1].id_message  = ID_DEACTIVE_ENEMY;
    mapMessagesFunctions[1].func        = &dwn::NetGame::deactiveEnemy;

    mapMessagesFunctions[2].id_message  = ID_GAME_PARTICIPANT_ORDER;
    mapMessagesFunctions[2].func        = &dwn::NetGame::readParticipantOrder;

    mapMessagesFunctions[3].id_message  = ID_GAME_STARTED;
    mapMessagesFunctions[3].func        = &dwn::NetGame::startGame;

    mapMessagesFunctions[4].id_message  = ID_DOOR_OPEN;
    mapMessagesFunctions[4].func        = &dwn::NetGame::toggleDoor;

    mapMessagesFunctions[5].id_message  = ID_DOOR_CLOSE;
    mapMessagesFunctions[5].func        = &dwn::NetGame::toggleDoor;

    mapMessagesFunctions[6].id_message  = ID_GENERATOR_ACTIVE;
    mapMessagesFunctions[6].func        = &dwn::NetGame::activeGenerator;

    mapMessagesFunctions[7].id_message  = ID_PROJECTILE_CREATE;
    mapMessagesFunctions[7].func        = &dwn::NetGame::createProjectile;

    mapMessagesFunctions[8].id_message  = ID_PROJECTILEGRENADE_CREATE;
    mapMessagesFunctions[8].func        = &dwn::NetGame::createProjectileGrenade;

    mapMessagesFunctions[9].id_message  = ID_CONSUMABLE_TAKEN;
    mapMessagesFunctions[9].func        = &dwn::NetGame::consumableTaken;

    mapMessagesFunctions[10].id_message = ID_ENEMY_UPDATE;
    mapMessagesFunctions[10].func       = &dwn::NetGame::enemyUpdate;

    mapMessagesFunctions[11].id_message = ID_SEND_MEDKIT;
    mapMessagesFunctions[11].func       = &dwn::NetGame::sendMedkit;

    mapMessagesFunctions[12].id_message = ID_SEND_AMMO;
    mapMessagesFunctions[12].func       = &dwn::NetGame::sendAmmo;
}

///////////////////
bool dwn::NetGame::readMappingMessage(RakNet::Packet *packet)
{
    bool readed = false;
    uint8_t i = 0;
    while(!readed && i<NUM_CUSTOM_NET_MESSAGES && mapMessagesFunctions[i].id_message>0)
    {
        if (mapMessagesFunctions[i].id_message==packet->data[0])
        {
            (this->*(mapMessagesFunctions[i].func))(packet);
            readed = true;
        }
        i++;
    }

    return readed;
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
                m_serverIP = m_servers[i];
                rakPeer->Connect(m_serverIP.c_str(), DEFAULT_PT,0,0);

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
      	RakNet::SystemAddress serverSystemAddress(m_serverIP.c_str(), DEFAULT_PT);
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
    std::string quitar;
	RakNet::SystemAddress facilitatorSystemAddress(m_serverIP.c_str(), DEFAULT_PT);
	RakNet::Packet *packet;
	RakNet::RakString targetName;
	for (packet=rakPeer->Receive(); packet; rakPeer->DeallocatePacket(packet), packet=rakPeer->Receive())
	{
		if (strcmp(packet->systemAddress.ToString(false),m_serverIP.c_str())==0)
			targetName="NATPunchthroughServer";
		else
			targetName=packet->systemAddress.ToString(true);

        if (!readMappingMessage(packet))
        {
            readConnectionMessage(packet, targetName, facilitatorSystemAddress);
        }
    }//for


	RakNet::TimeMS curTime = RakNet::GetTimeMS();

    // Actualizamos las posiciones de los objetos replicables replicamanager3
	unsigned int idx;
	for (idx=0; idx < replicaManager3->GetReplicaCount(); idx++)
		((DrawableReplica*)(replicaManager3->GetReplicaAtIndex(idx)))->update(curTime);

    // Realizamos los ajustes de la posición/rotación de los enemigos, 1 por cada update para
    // no sobrecargar. Solo si somos el host enviamos la info.
    if (fullyConnectedMesh2->IsHostSystem() && m_numNetEntities>0 && m_netEnemies[m_netEnemyIndex])
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

bool NetGame::getOpened() { return m_opened; }

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
void dwn::NetGame::removeNetEnemy(Enemy* enemy)
{
    unsigned int i=0;
    while(i<m_numNetEnemies)
    {
        if (m_netEnemies[i] == enemy)
            m_netEnemies[i] = 0;
        i++;
    }
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
        RakNet::SystemAddress serverAddress(m_serverIP.c_str(), DEFAULT_PT);
        // Envio el comienzo de partida con broadcast a todos los participantes, menos al server
        RakNet::BitStream bsOut;
        bsOut.Write((RakNet::MessageID)ID_GAME_STARTED);
        rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);

        m_gameStarted = true;
    }
}

///////////////////
void dwn::NetGame::sendBroadcastMessage(RakNet::BitStream &bsOut)
{
    RakNet::SystemAddress serverAddress(m_serverIP.c_str(), DEFAULT_PT);
    rakPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serverAddress, true);
}

///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, unsigned int value)
{
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(value);
    sendBroadcastMessage(bsOut);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, RakNet::RakString  value)
{
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(value);
    sendBroadcastMessage(bsOut);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, dwe::vec3f position, float angle)
{
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(position);
    bsOut.Write(angle);
    sendBroadcastMessage(bsOut);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, unsigned int objectID, dwe::vec3f position, dwe::vec3f rotation)
{
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(objectID);
    bsOut.Write(position);
    bsOut.Write(rotation);
    sendBroadcastMessage(bsOut);
}
///////////////////
void dwn::NetGame::sendBroadcast(unsigned int messageID, dwe::vec3f position, float angle, RakNet::RakString value)
{
    RakNet::BitStream bsOut;
    bsOut.Write((RakNet::MessageID)messageID);
    bsOut.Write(position);
    bsOut.Write(angle);
    bsOut.Write(value);
    sendBroadcastMessage(bsOut);
}


///////////////////
bool dwn::NetGame::getGameStarted() { return m_gameStarted; }

////////////////////////////////////////////////
RakNet::Replica3* dwn::NetGame::Connection_RM3DireW::AllocReplica(RakNet::BitStream* allocationId, RakNet::ReplicaManager3* replicaManager3)
{
    // Obtiene el mensaje desde Replica3::WriteAllocationID
    // Según este mensaje crearemos un objeto u otro.
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


///////////////////
void dwn::NetGame::readConnectionMessage(RakNet::Packet *packet, RakNet::RakString &targetName, RakNet::SystemAddress &facilitatorSystemAddress)
{
    switch (packet->data[0])
    {
    /*case ID_IP_RECENTLY_CONNECTED:
    case ID_INCOMPATIBLE_PROTOCOL_VERSION:
        std::cout << "\n------------------- ID_INCOMPATIBLE_PROTOCOL_VERSION ------------------------\n"; std::cin >> quitar;
        PushMessage(RakNet::RakString("Incompatible protocol version from ") + targetName + RakNet::RakString("."));
        if (packet->systemAddress==facilitatorSystemAddress)
            PushMessage("Multiplayer will not work without the NAT punchthrough server!");
        break;*/

    case ID_DISCONNECTION_NOTIFICATION:
        std::cout << "\n------------------- ID_DISCONNECTION_NOTIFICATION ------------------------\n"; //getline(cin, quitar);
        PushMessage(RakNet::RakString("Desconectado de ") + targetName + RakNet::RakString("."));
        break;

    case ID_CONNECTION_LOST:
        std::cout << "\n------------------- ID_CONNECTION_LOST ------------------------\n"; //std::cin >> quitar;
        PushMessage(RakNet::RakString("Se ha perdido la conexion a ") + targetName + RakNet::RakString("."));
        break;

    case ID_CONNECTION_REQUEST_ACCEPTED:
        std::cout << "\n------------------- ID_CONNECTION_REQUEST_ACCEPTED ------------------------\n"; //getline(cin, quitar);
        PushMessage(RakNet::RakString("Conexion a ") + targetName + RakNet::RakString(" aceptada."));
        if (packet->systemAddress==facilitatorSystemAddress)
        {
            // Query cloud for other running game instances
            RakNet::CloudQuery cloudQuery;
            cloudQuery.keys.Push(RakNet::CloudKey(NET_CLOUD_KEY,0),_FILE_AND_LINE_);
            cloudClient->Get(&cloudQuery, packet->guid);
            std::cout << "\n------------------- cloudClient->Get ------------------------\n"; //getline(cin, quitar);
        }
        break;

    case ID_CONNECTION_ATTEMPT_FAILED:
        std::cout << "\n------------------- ID_CONNECTION_ATTEMPT_FAILED ------------------------\n"; //getline(cin, quitar);
        PushMessage(RakNet::RakString("La conexion a ") + targetName + RakNet::RakString(" ha fallado."));
        m_connectionFailed = true;
        break;

    case ID_NO_FREE_INCOMING_CONNECTIONS:
        std::cout << "\n------------------- ID_NO_FREE_INCOMING_CONNECTIONS ------------------------\n"; //getline(cin, quitar);
        PushMessage(RakNet::RakString("La partida en el servidor está completa ") + targetName + RakNet::RakString("."));
        m_connectionFailed = true;
        break;

    case ID_NEW_INCOMING_CONNECTION:
        std::cout << "\n------------------- ID_NEW_INCOMING_CONNECTION ------------------------\n"; //getline(cin, quitar);
        if (fullyConnectedMesh2->IsHostSystem())
        {
            // Cuando es el primer juego que se ha creado y accede un nuevo jugador
            PushMessage(RakNet::RakString("Enviando la lista de participantes a la nueva conexion"));
            fullyConnectedMesh2->StartVerifiedJoin(packet->guid);
        }
        break;

    case ID_FCM2_VERIFIED_JOIN_START:
        {
        std::cout << "\n------------------- ID_FCM2_VERIFIED_JOIN_START ------------------------\n"; //getline(cin, quitar);
            DataStructures::List<RakNet::SystemAddress> addresses;
            DataStructures::List<RakNet::RakNetGUID> guids;
            DataStructures::List<RakNet::BitStream*> userData;
            fullyConnectedMesh2->GetVerifiedJoinRequiredProcessingList(packet->guid, addresses, guids, userData);
        std::cout << "\n------- enviamos a: ";
            for (unsigned int i=0; i < guids.Size(); i++)
            {
                natPunchthroughClient->OpenNAT(guids[i], facilitatorSystemAddress);
                std::cout << guids[i].ToString();
            }
        std::cout << "-----\n";
        //getline(cin, quitar)
        }
        break;

    case ID_FCM2_VERIFIED_JOIN_FAILED:
        std::cout << "\n------------------- ID_FCM2_VERIFIED_JOIN_FAILED ------------------------\n"; //getline(cin, quitar);
        PushMessage(RakNet::RakString("Failed to join game session"));
        break;

    case ID_FCM2_VERIFIED_JOIN_CAPABLE:
        {
        std::cout << "\n------------------- ID_FCM2_VERIFIED_JOIN_CAPABLE ------------------------\n"; //getline(cin, quitar);
            // Controlamos que la partida no ha empezado y que no está completa
            bool aceptar = (getNumPlayerMates() < MAX_PLAYERS  && !m_gameStarted);
            fullyConnectedMesh2->RespondOnVerifiedJoinCapable(packet, aceptar, 0);
        }
        break;

    case ID_FCM2_VERIFIED_JOIN_ACCEPTED:
        {
        std::cout << "\n------------------- ID_FCM2_VERIFIED_JOIN_ACCEPTED ------------------------\n"; //getline(cin, quitar);
            DataStructures::List<RakNet::RakNetGUID> systemsAccepted;
            bool thisSystemAccepted;
            fullyConnectedMesh2->GetVerifiedJoinAcceptedAdditionalData(packet, &thisSystemAccepted, systemsAccepted, 0);
            if (thisSystemAccepted){
                PushMessage("Peticion de unirse a la partida aceptada.\n");
                m_connected = true;
            }else
                PushMessage(RakNet::RakString("%s se ha unido a la partida\n", systemsAccepted[0].ToString()));

            for (unsigned int i=0; i < systemsAccepted.Size(); i++)
                replicaManager3->PushConnection(replicaManager3->AllocConnection(rakPeer->GetSystemAddressFromGuid(systemsAccepted[i]), systemsAccepted[i]));
        }
        break;

    case ID_FCM2_VERIFIED_JOIN_REJECTED:
        {
        std::cout << "\n------------------- ID_FCM2_VERIFIED_JOIN_REJECTED ------------------------\n"; //getline(cin, quitar);
            PushMessage(RakNet::RakString("rejected"));
            m_connectionRejected = true;
            // desconectar y marcar como no conectado
        }
        break;

    case ID_FCM2_NEW_HOST:
        std::cout << "\n------------------- ID_FCM2_NEW_HOST ------------------------\n"; //getline(cin, quitar);
        if (packet->guid==rakPeer->GetMyGUID())
        {
            // Original host dropped. I am the new session host. Upload to the cloud so new players join this system.
            RakNet::CloudKey cloudKey(NET_CLOUD_KEY,0);

            cloudClient->Post(&cloudKey, 0, 0, rakPeer->GetGuidFromSystemAddress(facilitatorSystemAddress));
        }
        break;

    case ID_CLOUD_GET_RESPONSE:
        {
        std::cout << "\n------------------- ID_CLOUD_GET_RESPONSE ------------------------\n"; //getline(cin, quitar);
            RakNet::CloudQueryResult cloudQueryResult;
            cloudClient->OnGetReponse(&cloudQueryResult, packet);

            // Buscamos partidas en servidor, las guardamos para elegir en menu
            int maxPartidas=cloudQueryResult.rowsReturned.Size();
            m_gamesIP.clear();
            m_gamesGUID.clear();
            if (maxPartidas>0)
            {
                for(int i=0; i<maxPartidas; i++)
                {
                    m_gamesIP.push_back(cloudQueryResult.rowsReturned[i]->clientSystemAddress.ToString());
                    m_gamesGUID.push_back(cloudQueryResult.rowsReturned[i]->clientGUID);
                }
            }

            m_cloudServerGUID = packet->guid;
            m_connected = true;

            cloudClient->DeallocateWithDefaultAllocator(&cloudQueryResult);

            m_gamesSearched = true;
        }
        break;

    case ID_NAT_TARGET_NOT_CONNECTED:
        std::cout << "\n------------------- ID_NAT_TARGET_NOT_CONNECTED ------------------------\n"; //getline(cin, quitar);
        targetName=getNATTargetName(packet);
        PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" not connected."));
        break;

    case ID_NAT_TARGET_UNRESPONSIVE:
        std::cout << "\n------------------- ID_NAT_TARGET_UNRESPONSIVE ------------------------\n"; //getline(cin, quitar);
        targetName=getNATTargetName(packet);
        PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" unresponsive."));
        break;

    case ID_NAT_CONNECTION_TO_TARGET_LOST:
        std::cout << "\n------------------- ID_NAT_CONNECTION_TO_TARGET_LOST ------------------------\n"; //getline(cin, quitar);
        targetName=getNATTargetName(packet);
        PushMessage(RakNet::RakString("NAT target ") + targetName + RakNet::RakString(" connection to lost."));
        break;

    case ID_NAT_ALREADY_IN_PROGRESS:
        std::cout << "\n------------------- ID_NAT_ALREADY_IN_PROGRESS ------------------------\n"; //getline(cin, quitar);
        targetName=getNATTargetName(packet);
        PushMessage(RakNet::RakString("NAT punchthrough to ") + targetName + RakNet::RakString(" in progress (skipping)."));
        break;

    case ID_NAT_PUNCHTHROUGH_SUCCEEDED:
        std::cout << "\n------------------- ID_NAT_PUNCHTHROUGH_SUCCEEDED ------------------------\n"; //getline(cin, quitar);
        if (packet->data[1]==1)  // Si somos los que enviamos el OpenNAT
        {
            PushMessage(RakNet::RakString("Connecting to existing game instance"));
            rakPeer->Connect(packet->systemAddress.ToString(false), packet->systemAddress.GetPort(), 0, 0);
            std::cout << "\n-------------- " << packet->systemAddress.ToString(false) << ":" << packet->systemAddress.GetPort() <<  "\n"; //getline(cin, quitar);
        }
        break;

    case ID_ADVERTISE_SYSTEM:
        std::cout << "\n------------------- ID_ADVERTISE_SYSTEM ------------------------\n"; //getline(cin, quitar);
        if (packet->guid!=rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
        {
            char hostIP[32];
            packet->systemAddress.ToString(false,hostIP);
            rakPeer->Connect(hostIP,packet->systemAddress.GetPort(),0,0);
        }
        break;

    }//switch
}

///////////////////
void dwn::NetGame::activeEnemy(RakNet::Packet *packet)
{
    unsigned int enemyID;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(enemyID);

    Scene::Instance()->activeEnemy(enemyID);
}

///////////////////
void dwn::NetGame::deactiveEnemy(RakNet::Packet *packet)
{
    unsigned int enemyID;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(enemyID);

    Scene::Instance()->deactiveEnemy(enemyID);
}

///////////////////
void dwn::NetGame::readParticipantOrder(RakNet::Packet *packet)
{
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

    bsIn.Read(m_participantOrder);
}

///////////////////
void dwn::NetGame::startGame(RakNet::Packet *packet)
{
    PushMessage(RakNet::RakString("Empieza el juego"));
    m_gameStarted = true;
}

///////////////////
void dwn::NetGame::toggleDoor(RakNet::Packet *packet)
{
    unsigned int entityID = getBitStreamEntityID(packet);

    if (entityID<m_numNetEntities)
    {
        if (packet->data[0] == ID_DOOR_OPEN)
            ((Door*)m_netEntities[entityID])->setIsOpening();
        else
            ((Door*)m_netEntities[entityID])->setIsClosing();
    }
}

///////////////////
void dwn::NetGame::activeGenerator(RakNet::Packet *packet)
{
    unsigned int entityID = getBitStreamEntityID(packet);
    if (entityID<m_numNetEntities)
        ((Generator*)m_netEntities[entityID])->activateGenerator();
}

///////////////////
void dwn::NetGame::createProjectile(RakNet::Packet *packet)
{
    dwe::vec3f position;
    float angle;
    RakNet::RakString value;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(position);
    bsIn.Read(angle);
    bsIn.Read(value);

    Scene::Instance()->createProjectile(position, angle, value.C_String(), 5); ///TO DO Poner un daño diferente a cada arma
}

///////////////////
void dwn::NetGame::createProjectileGrenade(RakNet::Packet *packet)
{
    dwe::vec3f position;
    float angle;
    std::string weapon;

    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(position);
    bsIn.Read(angle);

    m_scene->createProjectileGrenade(position, angle);
}

///////////////////
void dwn::NetGame::consumableTaken(RakNet::Packet *packet)
{
    unsigned int consumableID = getBitStreamEntityID(packet);
    if (consumableID<m_numNetConsumables)
        (m_netConsumables[consumableID])->take();
}

///////////////////
void dwn::NetGame::enemyUpdate(RakNet::Packet *packet)
{
    unsigned int enemyID;
    dwe::vec3f position;
    dwe::vec3f rotation;

    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(enemyID);
    bsIn.Read(position);
    bsIn.Read(rotation);

    if (enemyID<m_numNetEnemies && m_netEnemies[enemyID])
    {
        (m_netEnemies[enemyID])->setPosition(position);
        (m_netEnemies[enemyID])->setRotation(rotation);
    }
}

///////////////////
void dwn::NetGame::sendMedkit(RakNet::Packet *packet)
{
    RakNet::RakString value;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(value);

    // Si player coincide con la cadena que manda, añadimos medkit
    if (value == World->getMainPlayer()->creatingSystemGUID.ToString())
        World->getMainPlayer()->addMedkits(1);
}

///////////////////
void dwn::NetGame::sendAmmo(RakNet::Packet *packet)
{
    RakNet::RakString value;
    RakNet::BitStream bsIn(packet->data,packet->length,false);
    bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
    bsIn.Read(value);

    // Si player coincide con la cadena que manda, añadimos ammo
    if (value == World->getMainPlayer()->creatingSystemGUID.ToString())
        //World->getMainPlayer()->addAmmo(0,10);
        World->getMainPlayer()->getPlayerGun()->addAmmo(10);
}
