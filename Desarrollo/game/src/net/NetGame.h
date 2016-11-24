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

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PT 61111

namespace dwn
{
    class NetGame
    {
        public:
            NetGame();
            virtual ~NetGame();

            void open();
            void close();
            void update();
            void addNetObject(RakNet::Replica3 *replica3);
            bool isLocalObject(RakNet::RakNetGUID id);

        protected:

        private:
            static const int                _max_players        = 32;
            static const unsigned short     _tcp_port           = 0;
            static const RakNet::TimeMS     _udp_sleep_timer    = 30;


            ///////////////////////////////////////////

            class Connection_RM3DireW : public RakNet::Connection_RM3
            {
                public:
                    Connection_RM3DireW(const RakNet::SystemAddress &_systemAddress, RakNet::RakNetGUID _guid, NetGame* ng) : RakNet::Connection_RM3(_systemAddress, _guid) { netGame = ng; }
                    virtual ~Connection_RM3DireW() {}

                    virtual RakNet::Replica3 *AllocReplica(RakNet::BitStream *allocationId, RakNet::ReplicaManager3 *replicaManager3);
                protected:
                    NetGame* netGame;
            };

            class ReplicaManager3DireW : public RakNet::ReplicaManager3
            {
                public:
                    virtual RakNet::Connection_RM3* AllocConnection(const RakNet::SystemAddress &systemAddress, RakNet::RakNetGUID rakNetGUID) const {
                        return new Connection_RM3DireW(systemAddress,rakNetGUID, netGame);
                    }
                    virtual void DeallocConnection(RakNet::Connection_RM3 *connection) const {
                        delete connection;
                    }
                    NetGame* netGame;
            };

            ///////////////////////////////////////////

            RakNet::RakPeerInterface *rakPeer;  // Comunicación básica
            RakNet::NetworkIDManager *networkIDManager; // Unique IDs per network object
            ReplicaManager3DireW *replicaManager3; // Replicación de objetos en red
            RakNet::NatPunchthroughClient *natPunchthroughClient; // Conexión punto a punto entre routers
            RakNet::CloudClient *cloudClient; // Used to upload game instance to the cloud
            RakNet::FullyConnectedMesh2 *fullyConnectedMesh2; // Used to find out who is the session host

            bool isConnectedToNATPunchthroughServer;
    };
}

#endif // NETGAME_H
