#ifndef NETGAME_H
#define NETGAME_H

/*
    NetGame
    =======

    Clase que gestiona la interfaz entre RakNet y nuestro juego
*/
#include <vector>

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
#define MAX_NET_CONSUMABLES 100
#define MAX_NET_ENEMIES     100

class Entity;
class Scene;
class Consumable;
class Enemy;

namespace dwn
{
    class NetGame
    {
        public:
            static NetGame* Instance();
            virtual ~NetGame();

            void open(Scene *scene, bool multiplayer);
            void close();
            void update();

            void addNetObject(dwn::DrawableReplica *drawReplica);
            void addNetEntity(Entity* entity);
            void addNetConsumable(Consumable* consumable);
            void addNetEnemy(Enemy* enemy);

            bool isLocalObject(RakNet::RakNetGUID id);

            bool isMultiplayer();
            bool isServer();
            void setMultiplayer(bool m);
            bool getConnected();
            bool getConnectionFailed();
            bool getConnectionRejected();
            bool getGamesSearched();
            unsigned short getParticipantOrder();

            PlayerMate* getPlayerMate(unsigned int i);
            int getNumPlayerMates();

            void startGame();   // Enviamos a los demas que empezamos
            bool getGameStarted();

            std::vector<std::string>* getServers();
            std::vector<std::string>* getGamesIP();

            /// \brief Buscar servidores
            /// \details Busca en la red los servidores disponibles y rellena m_servers
            /// con la lista de servidores encontrados.
            /// \return true si hay partidas disponibles.
            bool searchForServers();

            /// \brief Conecta a un servidor
            /// \details Una vez buscados los servidores con searchForServers, por lo que m_servers tiene datos,
            /// se llama a esta función para conectar al servidor específico. Despues de conectar se pueden consultar
            /// m_connected, m_connectionFailed y m_connectionRejected.
            /// \param[in] index El indice en m_servers del servidor a conectar.
            /// \return  true si ha conectado (m_connected), y no ha habido Failed (m_connectionFailed) o Rejected (m_connectionRejected).
            bool connectToServer(unsigned int index);

            /// \brief Conectar a una partida
            /// \details Conecta a una de las partidas de gamesIP que deben haber sido previamente buscadas (m_gamesSearched true)
            /// Si se le especifica index=0 crea un servidor de partidas
            /// \param[in] index el indice en m_gameIP donde conectar
            /// \return Devuelve true si no ha habido ningún error
            bool connectToGame(unsigned int index);

            /// \brief Enviar mensajes
            /// \details Envian mensajes a todas las máquinas conectadas en la misma partida y se reciben en update() en
            /// los demás ordenadores.
            /// \param[in] messageID El id de mensaje que se envian, definidos en NetCommon.h
            /// \param[in] ... resto de parametros son los datos que se envian junto con el mensaje.
            void sendBroadcast(unsigned int messageID, unsigned int value);
            void sendBroadcast(unsigned int messageID, RakNet::RakString value);
            void sendBroadcast(unsigned int messageID, dwe::vec3f position, float angle);
            void sendBroadcast(unsigned int messageID, unsigned int objectID, dwe::vec3f position, dwe::vec3f rotation);

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
            bool m_gamesSearched;         // Si ya ha hecho la búsqueda de partidas o no
            bool m_isServer;
            bool m_gameStarted;
            unsigned short m_participantOrder;
            std::string m_serverIP;
            Scene* m_scene;
            RakNetGUID m_cloudServerGUID;


            Entity* m_netEntities[MAX_NET_ENTITIES];
            unsigned int m_numNetEntities;

            Consumable* m_netConsumables[MAX_NET_CONSUMABLES];
            unsigned int m_numNetConsumables;

            Enemy* m_netEnemies[MAX_NET_ENEMIES];
            unsigned int m_numNetEnemies;
            unsigned int m_netEnemyIndex;

            std::vector<std::string> m_servers;
            std::vector<std::string> m_gamesIP;
            std::vector<RakNetGUID> m_gamesGUID;


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
