#include "DrawableReplica.h"
#include "NetGame.h"
#include "iostream"
#include <typeinfo>


dwn::DrawableReplica::DrawableReplica() {}
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
    std::cout << "Envio " << getPosition().x << " " << getPosition().y << "\n";
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
	// por ahora nada, el ejemplo lo que hace es crear la malla y dem�s
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
    // Borramos los datos del objeto remoto
}

/////////////////////////////////////////////////////
RakNet::RM3SerializationResult dwn::DrawableReplica::Serialize(RakNet::SerializeParameters* serializeParameters)
{
    // TODO no deveria devolver algo de RakNet, por patr�n fachada
	serializeParameters->outputBitstream[0].Write(getPosition());
	serializeParameters->outputBitstream[0].Write(getRotation());
	return RakNet::RM3SR_BROADCAST_IDENTICALLY;
}

///////////////////////////
void dwn::DrawableReplica::Deserialize(RakNet::DeserializeParameters* deserializeParameters)
{
	deserializeParameters->serializationBitstream[0].Read(m_remotePos);
	deserializeParameters->serializationBitstream[0].Read(m_remoteRot);
	// Aqui no podemos hacer setPosition, no va bien. Es solo para coger los parametros
	// y en el update mover
}

///////////////////////////
void dwn::DrawableReplica::update(RakNet::TimeMS curTime)
{
    // �Es objeto local?
	if (NetInstance->isLocalObject(creatingSystemGUID))
	{
	    // Objeto creado localmente
	}
	else
    {
        // Objeto creado por red
        setPosition(m_remotePos);
        setRotation(m_remoteRot);
    }
}
