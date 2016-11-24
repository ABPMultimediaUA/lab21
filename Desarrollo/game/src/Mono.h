#ifndef MONO_H
#define MONO_H

#include "RakPeerInterface.h"
#include "ReplicaManager3.h"
#include "NatPunchthroughClient.h"
#include "CloudClient.h"
#include "FullyConnectedMesh2.h"
#include "RakNetTime.h"
#include "NetworkIDManager.h"
#include "GetTime.h"

#include "FachadeDireEngine.h"

namespace dwn { class NetGame; };

class BaseDireWReplica : public RakNet::Replica3
{
public:
	BaseDireWReplica() {};
	virtual ~BaseDireWReplica() {};

	virtual void SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection) {}
	virtual bool DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection) { return true; }
	virtual RakNet::RM3SerializationResult Serialize(RakNet::SerializeParameters *serializeParameters) { return RakNet::RM3SR_BROADCAST_IDENTICALLY; }
	virtual void Deserialize(RakNet::DeserializeParameters *deserializeParameters) {}
	virtual void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const {}

    // Necesarias al ser virtuales puras
    virtual RakNet::RM3ConstructionState QueryConstruction(RakNet::Connection_RM3 *destinationConnection, RakNet::ReplicaManager3 *replicaManager3) {return QueryConstruction_PeerToPeer(destinationConnection);}
    virtual bool QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection) {return QueryRemoteConstruction_PeerToPeer(sourceConnection);}
    virtual void SerializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *destinationConnection) {}
    virtual bool DeserializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *sourceConnection) {return true;}
    virtual RakNet::RM3ActionOnPopConnection QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const {return QueryActionOnPopConnection_PeerToPeer(droppedConnection);}
    virtual void DeallocReplica(RakNet::Connection_RM3 *sourceConnection) {delete this;}
    virtual RakNet::RM3QuerySerializationResult QuerySerialization(RakNet::Connection_RM3 *destinationConnection) {return QuerySerialization_PeerToPeer(destinationConnection);}


	virtual void Update(RakNet::TimeMS curTime) {};
};

class Mono : public BaseDireWReplica, public fde::Node
{
    public:
        Mono();
        //Mono(ISceneNode* n);
        virtual ~Mono() {};

      	virtual void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const;
    	virtual void SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection);
        virtual bool DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection);
        virtual void PostDeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection);
        virtual RakNet::RM3SerializationResult Serialize(RakNet::SerializeParameters *serializeParameters);
        virtual void Deserialize(RakNet::DeserializeParameters *deserializeParameters);
       	virtual void PreDestruction(RakNet::Connection_RM3 *sourceConnection);

        virtual void Update(RakNet::TimeMS curTime);

        fde::vec3f position;
        dwn::NetGame* netGame;
    private:

};


#endif // MONO_H
