#ifndef DRAWABLEREPLICA_H
#define DRAWABLEREPLICA_H

#include <Drawable.h>

#include "RakPeerInterface.h"
#include "ReplicaManager3.h"
#include "NatPunchthroughClient.h"
#include "CloudClient.h"
#include "FullyConnectedMesh2.h"
#include "RakNetTime.h"
#include "NetworkIDManager.h"
#include "GetTime.h"

namespace dwn
{
    class DrawableReplica : public Drawable, public RakNet::Replica3
    {
        public:
            DrawableReplica();
            virtual ~DrawableReplica();

            // Esta función hay que sobrescribirla para obtener el
            // nombre del objeto a crear en el sistema remoto.
            virtual const char* getNetObjectID() const;

            virtual void update(RakNet::TimeMS curTime);

        protected:

        private:
            dwe::vec3f          m_remotePos;
            dwe::vec3f          m_remoteRot;
            dwe::AnimationType  m_remoteAnim;


            // Puestas en private para no heredar
            virtual void SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection);
            virtual bool DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection);
            virtual RakNet::RM3SerializationResult Serialize(RakNet::SerializeParameters *serializeParameters);
            virtual void Deserialize(RakNet::DeserializeParameters *deserializeParameters);

            virtual void PostDeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection);
            virtual void PreDestruction(RakNet::Connection_RM3 *sourceConnection);

            virtual void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const;

            // Necesarias al ser virtuales puras
            virtual RakNet::RM3ConstructionState QueryConstruction(RakNet::Connection_RM3 *destinationConnection, RakNet::ReplicaManager3 *replicaManager3) {return QueryConstruction_PeerToPeer(destinationConnection);}
            virtual bool QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection) {return QueryRemoteConstruction_PeerToPeer(sourceConnection);}
            virtual void SerializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *destinationConnection) {}
            virtual bool DeserializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *sourceConnection) {return true;}
            virtual RakNet::RM3ActionOnPopConnection QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const {return QueryActionOnPopConnection_PeerToPeer(droppedConnection);}
            virtual void DeallocReplica(RakNet::Connection_RM3 *sourceConnection) {delete this;}
            virtual RakNet::RM3QuerySerializationResult QuerySerialization(RakNet::Connection_RM3 *destinationConnection) {return QuerySerialization_PeerToPeer(destinationConnection);}
    };
}

#endif // DRAWABLEREPLICA_H
