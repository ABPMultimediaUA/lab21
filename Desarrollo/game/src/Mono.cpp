#include "Mono.h"
#include "NetGame.h"
#include <iostream>

Mono::Mono() : fde::Node(NULL){};

//Mono::Mono(ISceneNode* n) : fde::Node(n)
//{
////    netGame = ng;
////    netGame->addNetObject(this);
//};

void Mono::WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const
{
   	allocationIdBitstream->Write(RakNet::RakString("Mono"));
}

void Mono::SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
{
//	constructionBitstream->Write(getPosition());
    position = getPosition();
	constructionBitstream->Write(position);
    std::cout << "Serialize construction................" << position.x << "-" << position.z << "-" << "\n";

}

bool Mono::DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection)
{

    //fde::vec3f position;
    constructionBitstream->Read(position);
    //setPosition(position);
    std::cout << "Deserialize construction................" << position.x << "-" << position.z << "-" << "\n";
	return true;
}

void Mono::PostDeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
{
	// por ahora nada, el ejemplo lo que hace es crear la malla y demás
	// pero pq solo carga la maya de los demas jugadores, no del propio
	// del host, ya que es 1a persona.
	// Por ejemplo se puede crear en el hud los datos del modelo remoto creado
	// y la posicion inicial
    std::cout << "PostDeserialize construction................" << position.x << "-" << position.z << "-" << "\n";
	setPosicion(position);
}

void Mono::PreDestruction(RakNet::Connection_RM3 *sourceConnection)
{
    // Borramos los datos del objeto remoto
}

RakNet::RM3SerializationResult Mono::Serialize(RakNet::SerializeParameters *serializeParameters)
{
    // TODO no deveria devolver algo de RakNet, por patrón fachada
  //  std::cout << "Serialize................." << getPosition().x << "\n";

	serializeParameters->outputBitstream[0].Write(getPosition());
	return RakNet::RM3SR_BROADCAST_IDENTICALLY;
}

void Mono::Deserialize(RakNet::DeserializeParameters *deserializeParameters)
{
	//deserializeParameters->serializationBitstream[0].Read(position);
	// Aqui no podemos hacer setPosition, no va bien. Es solo para coger los parametros
	// y en el update mover
    //std::cout << "Deserialize................." << p << "\n";
}

void Mono::Update(RakNet::TimeMS curTime)
{
    // ¿Es objeto local?
	if (netGame->isLocalObject(creatingSystemGUID))
	{
	    // Objeto creado localmente
	}
	else
    {
        // Objeto creado por red

        setPosicion(position);
    }
    // Por ahora lo muevo en Deserialize. Y el local en el main()
}
