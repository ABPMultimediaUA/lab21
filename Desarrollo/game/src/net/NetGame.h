#ifndef NETGAME_H
#define NETGAME_H

/*
    NetGame
    =======

    Clase que gestiona la interfaz entre RakNet y nuestro juego
*/

#include "RakPeerInterface.h"
#include "ReplicaManager3.h"
#include "NatPunchthroughClient.h"
#include "CloudClient.h"
#include "FullyConnectedMesh2.h"
#include "RakNetTime.h"
#include "NetworkIDManager.h"
#include "GetTime.h"

#include "DrawableReplica.h"
#include "NetCommon.h"



#define DEFAULT_IP          "127.0.0.1"
#define DEFAULT_PT          61111
#define NET_CLOUD_KEY       "Lab21Key"
#define MAX_PLAYERS         4
#define MAX_NET_ENTITIES    100

class Entity;

namespace dwn
{
    class NetGame
    {
        public:
            static NetGame* Instance();
            virtual ~NetGame();

            void open();
            void close();
            void update();
            void addNetObject(dwn::DrawableReplica *drawReplica);
            void addNetEntity(Entity* entity);
            bool isLocalObject(RakNet::RakNetGUID id);

            static bool isConnectedToNATPunchthroughServer;

            bool isMultiplayer();
            bool isConnected();
            bool connectionFailed();
            unsigned short getParticipantOrder();

            PlayerMate* getPlayerMate(int i);
            int getNumPlayerMates();

            void startGame();   // Enviamos a los demas que empezamos
            bool getGameStarted();

            void sendBroadcast(unsigned int messageID, unsigned int value);

        protected:

        private:
            NetGame();
            static const int                _max_players        = 32;
            static const unsigned short     _tcp_port           = 0;
            static const RakNet::TimeMS     _udp_sleep_timer    = 30;
            static const unsigned int       _time_search_server = 1500;   // Milisegundos de espera buscando servidores

            bool m_multiplayer;
            bool m_connected;
            bool m_connectionFailed;
            bool m_connectionRejected;
            bool m_isServer;
            bool m_gameStarted;
            unsigned short m_participantOrder;
            std::string m_IP;

            Entity* m_netEntities[MAX_NET_ENTITIES];
            int m_numNetEntities;


            unsigned int getBitStreamEntityID(Packet *packet);


            ///////////////////////////////////////////

            class Connection_RM3DireW : public RakNet::Connection_RM3
            {
                public:
                    Connection_RM3DireW(const RakNet::SystemAddress &_systemAddress, RakNet::RakNetGUID _guid) : RakNet::Connection_RM3(_systemAddress, _guid) {}
                    virtual ~Connection_RM3DireW() {}

                    virtual RakNet::Replica3 *AllocReplica(RakNet::BitStream *allocationId, RakNet::ReplicaManager3 *replicaManager3);
            };

            class ReplicaManager3DireW : public RakNet::ReplicaManager3
            {
                public:
                    virtual RakNet::Connection_RM3* AllocConnection(const RakNet::SystemAddress &systemAddress, RakNet::RakNetGUID rakNetGUID) const {
                        return new Connection_RM3DireW(systemAddress,rakNetGUID);
                    }
                    virtual void DeallocConnection(RakNet::Connection_RM3 *connection) const {
                        delete connection;
                    }
            };

            ///////////////////////////////////////////

            RakNet::RakPeerInterface *rakPeer;  // Comunicación básica
            RakNet::NetworkIDManager *networkIDManager; // Unique IDs per network object
            ReplicaManager3DireW *replicaManager3; // Replicación de objetos en red
            RakNet::NatPunchthroughClient *natPunchthroughClient; // Conexión punto a punto entre routers
            RakNet::CloudClient *cloudClient; // Used to upload game instance to the cloud
            RakNet::FullyConnectedMesh2 *fullyConnectedMesh2; // Used to find out who is the session host

            RakNet::RakString getNATTargetName(RakNet::Packet *p);

    };
}
#define NetInstance dwn::NetGame::Instance()

#endif // NETGAME_H
