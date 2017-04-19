#include "DrawableReplica.h"
#include "NetGame.h"
#include "iostream"
#include <typeinfo>


dwn::DrawableReplica::DrawableReplica():
    m_lastPosUpdate(0), m_updatedPosition(false)
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
	setRotation(m_remoteRot);
	DrawablePhysics::setPosition(m_remotePos);
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
    unsigned char data;

	serializeParameters->outputBitstream[0].Write(getVelocity());
	serializeParameters->outputBitstream[0].Write(getRotation());
	serializeParameters->outputBitstream[0].Write(getAnimation());
	if(RakNet::GetTime() - m_lastPosUpdate > _timeUpdatePosition)
    {
        data = 0b1;
        serializeParameters->outputBitstream[0].WriteBits(&data, 1);  // Marca de que enviamos position
        serializeParameters->outputBitstream[0].Write(getPosition());
        m_lastPosUpdate = RakNet::GetTime();
    }
    else
    {
        data = 0b0;
        serializeParameters->outputBitstream[0].WriteBits(&data, 1);  // Marca de que no enviamos position
    }

	return RakNet::RM3SR_BROADCAST_IDENTICALLY;
}

///////////////////////////
void dwn::DrawableReplica::Deserialize(RakNet::DeserializeParameters* deserializeParameters)
{
	deserializeParameters->serializationBitstream[0].Read(m_remoteVel);
	deserializeParameters->serializationBitstream[0].Read(m_remoteRot);
	deserializeParameters->serializationBitstream[0].Read(m_remoteAnim);
	if (deserializeParameters->serializationBitstream[0].ReadBit())  // Si ha enviado posición
    {
        deserializeParameters->serializationBitstream[0].Read(m_remotePos);
        m_updatedPosition = true;
    }
	// Aqui no podemos hacer setPosition. Es solo para coger los parametros
	// y en el update mover
}

///////////////////////////
void dwn::DrawableReplica::update(RakNet::TimeMS curTime)
{
	if (!NetInstance->isLocalObject(creatingSystemGUID))
    {
        // Objeto creado por red
        setVelocity(m_remoteVel);
        setRotation(m_remoteRot);
        setAnimation(m_remoteAnim);
        if (m_updatedPosition)
        {
            DrawablePhysics::setPosition(m_remotePos);
            m_updatedPosition = false;
        }
    }
}
