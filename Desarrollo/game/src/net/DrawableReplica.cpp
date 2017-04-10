#include "DrawableReplica.h"
#include "NetGame.h"
#include "iostream"
#include <typeinfo>


dwn::DrawableReplica::DrawableReplica():
    m_lastPosUpdate(0)
{

}

dwn::DrawableReplica::~DrawableReplica() {}

//////////////////////////////////
const char* dwn::DrawableReplica::getNetObjectID() const
{
    return (typeid(*this).name());
}

///////////////////////////
void dwn::DrawableReplica::WriteAllocationID(RakNet::Connection_RM3* destinationConnection, RakNet::BitStream* allocationIdBitstream) const
{
    allocationIdBitstream->Write(RakNet::RakString(getNetObjectID()));
}

///////////////////////////
void dwn::DrawableReplica::SerializeConstruction(RakNet::BitStream* constructionBitstream, RakNet::Connection_RM3* destinationConnection)
{
	constructionBitstream->Write(getPosition());
	constructionBitstream->Write(getRotation());
}

///////////////////////////
bool dwn::DrawableReplica::DeserializeConstruction(RakNet::BitStream* constructionBitstream, RakNet::Connection_RM3* sourceConnection)
{
    constructionBitstream->Read(m_remotePos);
    constructionBitstream->Read(m_remoteRot);
	return true;
}

///////////////////////////
void dwn::DrawableReplica::PostDeserializeConstruction(RakNet::BitStream* constructionBitstream, RakNet::Connection_RM3* destinationConnection)
{
	// por ahora nada, el ejemplo lo que hace es crear la malla y demás
	// pero pq solo carga la maya de los demas jugadores, no del propio
	// del host, ya que es 1a persona.
	// Por ejemplo se puede crear en el hud los datos del modelo remoto creado
	// y la posicion inicial
	setPosition(m_remotePos);
	setRotation(m_remoteRot);
}

///////////////////////////
void dwn::DrawableReplica::PreDestruction(RakNet::Connection_RM3* sourceConnection)
{
    // Borramos los datos del objeto remoto en local
    removeNode();
}

/////////////////////////////////////////////////////
RakNet::RM3SerializationResult dwn::DrawableReplica::Serialize(RakNet::SerializeParameters* serializeParameters)
{
    //std::cout << "SSSSSSSerialize.................\n";

	serializeParameters->outputBitstream[0].Write(getVelocity());
	serializeParameters->outputBitstream[0].Write(getPosition());
	serializeParameters->outputBitstream[0].Write(getRotation());
	serializeParameters->outputBitstream[0].Write(getAnimation());
	return RakNet::RM3SR_BROADCAST_IDENTICALLY;
}

///////////////////////////
void dwn::DrawableReplica::Deserialize(RakNet::DeserializeParameters* deserializeParameters)
{
    //std::cout << "DDDDDDDeserialize.................\n";

	deserializeParameters->serializationBitstream[0].Read(m_remoteVel);
	deserializeParameters->serializationBitstream[0].Read(m_remotePos);
	deserializeParameters->serializationBitstream[0].Read(m_remoteRot);
	deserializeParameters->serializationBitstream[0].Read(m_remoteAnim);
	// Aqui no podemos hacer setPosition, no va bien. Es solo para coger los parametros
	// y en el update mover
}

///////////////////////////
void dwn::DrawableReplica::update(RakNet::TimeMS curTime)
{
    // ¿Es objeto local?
	if (NetInstance->isLocalObject(creatingSystemGUID))
	{
	    // Objeto creado localmente
	}
	else
    {
        // Objeto creado por red
        setVelocity(m_remoteVel);
        setRotation(m_remoteRot);
        setAnimation(m_remoteAnim);
        if (curTime - m_lastPosUpdate> 200)
        {
            setPosition(m_remotePos);
            m_lastPosUpdate = curTime;
        }
    }
}
