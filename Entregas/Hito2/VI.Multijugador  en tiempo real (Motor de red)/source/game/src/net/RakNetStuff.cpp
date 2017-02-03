/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include "RakNetStuff.h"

#include "NetworkIDManager.h"
#include "RakNetTime.h"
#include "GetTime.h"
#include "SocketLayer.h"

using namespace RakNet;

RakPeerInterface *rakPeer;
NetworkIDManager *networkIDManager;
ReplicaManager3Irrlicht *replicaManager3;
NatPunchthroughClient *natPunchthroughClient;
CloudClient *cloudClient;
RakNet::FullyConnectedMesh2 *fullyConnectedMesh2;
PlayerReplica *playerReplica;


DataStructures::List<PlayerReplica*> PlayerReplica::playerList;

// Take this many milliseconds to move the visible position to the real position
static const float INTERP_TIME_MS=100.0f;

void InstantiateRakNetClasses(void)
{
	static const int MAX_PLAYERS=32;
	static const unsigned short TCP_PORT=0;
	static const RakNet::TimeMS UDP_SLEEP_TIMER=30;

	// Basis of all UDP communications, RakPeerInterface es la base de RakNet
	rakPeer=RakNet::RakPeerInterface::GetInstance();

	// Buscamos un puerto válido. Using fixed port so we can use AdvertiseSystem and connect on the LAN if the server is not available.
	RakNet::SocketDescriptor sd(1234,0);
	sd.socketFamily=AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
	while (IRNS2_Berkley::IsPortInUse(sd.port, sd.hostAddress, sd.socketFamily, SOCK_DGRAM)==true)
		sd.port++;

	// StartupResult solo sirve para hacer el assert y comprobar que ha ido bien
	RakNet::StartupResult sr = rakPeer->Startup(MAX_PLAYERS+1,&sd,1);// +1 is for the connection to the NAT punchthrough server
	RakAssert(sr==RakNet::RAKNET_STARTED);

	// Configuraciones de RakPeerInterface
	rakPeer->SetMaximumIncomingConnections(MAX_PLAYERS);
	rakPeer->SetTimeoutTime(5000,UNASSIGNED_SYSTEM_ADDRESS);   // Fast disconnect for easier testing of host migration



	// ReplicaManager3 replies on NetworkIDManager. It assigns numbers to objects so they can be looked up over the network
	// It's a class in case you wanted to have multiple worlds, then you could have multiple instances of NetworkIDManager
	networkIDManager=new NetworkIDManager;
	// Automatically sends around new / deleted / changed game objects
	replicaManager3=new ReplicaManager3Irrlicht;
	replicaManager3->SetNetworkIDManager(networkIDManager);
	rakPeer->AttachPlugin(replicaManager3);
	// Automatically destroy connections, but don't create them so we have more control over when a system is considered ready to play
	replicaManager3->SetAutoManageConnections(false,true);
	// Create and register the network object that represents the player
	playerReplica = new PlayerReplica;
	replicaManager3->Reference(playerReplica);
	// Lets you connect through routers
	natPunchthroughClient=new NatPunchthroughClient;
	rakPeer->AttachPlugin(natPunchthroughClient);
	// Uploads game instance, basically client half of a directory server
	// Server code is in NATCompleteServer sample
	cloudClient=new CloudClient;
	rakPeer->AttachPlugin(cloudClient);
	fullyConnectedMesh2=new FullyConnectedMesh2;
	fullyConnectedMesh2->SetAutoparticipateConnections(false);
	fullyConnectedMesh2->SetConnectOnNewRemoteConnection(false, "");
	rakPeer->AttachPlugin(fullyConnectedMesh2);



	// Connect to the NAT punchthrough server
	ConnectionAttemptResult car = rakPeer->Connect(DEFAULT_NAT_PUNCHTHROUGH_FACILITATOR_IP, DEFAULT_NAT_PUNCHTHROUGH_FACILITATOR_PORT,0,0);
	RakAssert(car==CONNECTION_ATTEMPT_STARTED);



	// Advertise ourselves on the lAN if the NAT punchthrough server is not available
 	//for (int i=0; i < 8; i++)
 	//	rakPeer->AdvertiseSystem("255.255.255.255", 1234+i, 0,0,0);
}
void DeinitializeRakNetClasses(void)
{
	// Shutdown so the server knows we stopped
	rakPeer->Shutdown(100,0);
	RakNet::RakPeerInterface::DestroyInstance(rakPeer);
	delete networkIDManager;
	delete replicaManager3;
	delete natPunchthroughClient;
	delete cloudClient;
	delete fullyConnectedMesh2;
	// ReplicaManager3 deletes all referenced objects, including this one
	//playerReplica->PreDestruction(0);
	//delete playerReplica;
}
BaseIrrlichtReplica::BaseIrrlichtReplica()
{
}
BaseIrrlichtReplica::~BaseIrrlichtReplica()
{

}
void BaseIrrlichtReplica::SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
{
	constructionBitstream->Write(position);
}
bool BaseIrrlichtReplica::DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection)
{
	constructionBitstream->Read(position);
	return true;
}
RM3SerializationResult BaseIrrlichtReplica::Serialize(RakNet::SerializeParameters *serializeParameters)
{
	return RM3SR_BROADCAST_IDENTICALLY;
}
void BaseIrrlichtReplica::Deserialize(RakNet::DeserializeParameters *deserializeParameters)
{
}
void BaseIrrlichtReplica::Update(RakNet::TimeMS curTime)
{
}
PlayerReplica::PlayerReplica()
{
	model=0;
	rotationDeltaPerMS=0.0f;
	isMoving=false;
	deathTimeout=0;
	playerList.Push(this,_FILE_AND_LINE_);


	// Tiempo que ha pasado para interpolación
	// Solo necesito esta linea para raknet
	lastUpdate=RakNet::GetTimeMS();
}
PlayerReplica::~PlayerReplica()
{
    // No necesito nada de aquí para raknet
	unsigned int index = playerList.GetIndexOf(this);
	if (index != (unsigned int) -1)
		playerList.RemoveAtIndexFast(index);
}
void PlayerReplica::WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const
{
    // Envia una cadena que sera leida por Connection_RM3::AllocReplica
    // En AllocReplica es donde creamos el objeto segun el mensaje que le enviamos aqui
	allocationIdBitstream->Write(RakNet::RakString("PlayerReplica"));
}
void PlayerReplica::SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
{
	BaseIrrlichtReplica::SerializeConstruction(constructionBitstream, destinationConnection);

	// Los datos que necesitamos cuando creamos el objeto.
	// Son recibidos por Replica3::DeserializeConstruction en el otro ordenador
	// Después se ejecuta Replica3::Serialize() en este mismo ordenador
	constructionBitstream->Write(rotationAroundYAxis);
	constructionBitstream->Write(playerName);
	constructionBitstream->Write(IsDead());
}
bool PlayerReplica::DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection)
{
    // Devolvemos false para no crear el objeto, si no se ha podido crear bien
	if (!BaseIrrlichtReplica::DeserializeConstruction(constructionBitstream, sourceConnection))
		return false;

    // Los datos enviados desde otro ordenador, necesarios para crear el objeto
    // Son enviados por Replica3::SerializeConstruction
	constructionBitstream->Read(rotationAroundYAxis);
	constructionBitstream->Read(playerName);
	constructionBitstream->Read(isDead);

	return true;
}
void PlayerReplica::PostDeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
{
    // Se ejecuta despues de DeserializeConstruction
    // Creamos el objeto, malla y demás, no necesario nada de aqui para raknet



	// Object was remotely created and all data loaded. Now we can make the object visible
	scene::IAnimatedMesh* mesh = 0;
	scene::ISceneManager *sm = demo->GetSceneManager();
	mesh = sm->getMesh(IRRLICHT_MEDIA_PATH "sydney.md2");
	model = sm->addAnimatedMeshSceneNode(mesh, 0);

	model->setPosition(position);
	model->setRotation(core::vector3df(0, rotationAroundYAxis, 0));
	model->setScale(core::vector3df(2,2,2));
	model->setMD2Animation(scene::EMAT_STAND);
	curAnim=scene::EMAT_STAND;
	model->setMaterialTexture(0, demo->GetDevice()->getVideoDriver()->getTexture(IRRLICHT_MEDIA_PATH "sydney.bmp"));
	model->setMaterialFlag(video::EMF_LIGHTING, true);
	model->addShadowVolumeSceneNode();
	model->setAutomaticCulling ( scene::EAC_BOX );
	model->setVisible(true);
	model->setAnimationEndCallback(this);
	wchar_t playerNameWChar[1024];
	mbstowcs(playerNameWChar, playerName.C_String(), 1024);
	scene::IBillboardSceneNode *bb = sm->addBillboardTextSceneNode(0, playerNameWChar, model);
	bb->setSize(core::dimension2df(40,20));
	bb->setPosition(core::vector3df(0,model->getBoundingBox().MaxEdge.Y+bb->getBoundingBox().MaxEdge.Y-bb->getBoundingBox().MinEdge.Y+5.0,0));
	bb->setColor(video::SColor(255,255,128,128), video::SColor(255,255,128,128));
}
void PlayerReplica::PreDestruction(RakNet::Connection_RM3 *sourceConnection)
{
    // Llamado después de DeserializeDestruction
    // Para borrar el objeto
    // No necesario para raknet el codigo siguiente
	if (model)
		model->remove();
}
RM3SerializationResult PlayerReplica::Serialize(RakNet::SerializeParameters *serializeParameters)
{
    // Se ejecuta después de Replica3::SerializeConstruction en el mismo ordenador.
    // Se ejecuta según el intervalo definido por ReplicaManager3::SetAutoSerializeInterval()
    // y después se ejecuta ReplicaManager3::Update
    // Se actualizan los parámetros que son cambiantes.
    // Estos datos los recibirán los otros ordenadores en Replica3::Deserialize
	BaseIrrlichtReplica::Serialize(serializeParameters);
	serializeParameters->outputBitstream[0].Write(position);
	serializeParameters->outputBitstream[0].Write(rotationAroundYAxis);
	serializeParameters->outputBitstream[0].Write(isMoving);
	serializeParameters->outputBitstream[0].Write(IsDead());
	return RM3SR_BROADCAST_IDENTICALLY;
}
void PlayerReplica::Deserialize(RakNet::DeserializeParameters *deserializeParameters)
{
    // Se reciben los datos enviados desde otro ordenador mediante Replica3::Serialize
    // Se actualizan los datos cambiantes del objeto que queramos.
	BaseIrrlichtReplica::Deserialize(deserializeParameters);
	deserializeParameters->serializationBitstream[0].Read(position);
	deserializeParameters->serializationBitstream[0].Read(rotationAroundYAxis);
	deserializeParameters->serializationBitstream[0].Read(isMoving);
	bool wasDead=isDead;
	deserializeParameters->serializationBitstream[0].Read(isDead);
	if (isDead==true && wasDead==false)
	{
		demo->PlayDeathSound(position);
	}

	core::vector3df positionOffset;
	positionOffset=position-model->getPosition();
	positionDeltaPerMS = positionOffset / INTERP_TIME_MS;
	float rotationOffset;
	rotationOffset=GetRotationDifference(rotationAroundYAxis,model->getRotation().Y);
	rotationDeltaPerMS = rotationOffset / INTERP_TIME_MS;
	interpEndTime = RakNet::GetTimeMS() + (RakNet::TimeMS) INTERP_TIME_MS;
}
void PlayerReplica::Update(RakNet::TimeMS curTime)
{
    // creatingSystemGUID se crea automaticamente cuando se constuye el objeto.
    // Con esto podemos saber si el objeto es el construido localmente
    // Aqui no hay nada de raknet, solo actualización de las posiciones/rotaciones/animaciones de los playerReplica
    // Esta función no es heredada. Se llama desde game para actualizar el modelo y posiciones en raknet.

	// ¿Creado localmente?
	if (creatingSystemGUID==rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
	{
	    // No se interpola.
	    // La posición del player es la de la cámara
		playerReplica->position=demo->GetSceneManager()->getActiveCamera()->getPosition()-irr::core::vector3df(0,CAMERA_HEIGHT,0);
		playerReplica->rotationAroundYAxis=demo->GetSceneManager()->getActiveCamera()->getRotation().Y-90.0f;
		isMoving=demo->IsMovementKeyDown();

		return;
	}

	// Si no es objeto creado localmente, interpolamos posición

	// Update interpolation
	RakNet::TimeMS elapsed = curTime-lastUpdate;
	if (elapsed<=1)
		return;
	if (elapsed>100)
		elapsed=100;

	lastUpdate=curTime;
	irr::core::vector3df curPositionDelta = position-model->getPosition();
	irr::core::vector3df interpThisTick = positionDeltaPerMS*(float) elapsed;
	if (curTime < interpEndTime && interpThisTick.getLengthSQ() < curPositionDelta.getLengthSQ())
	{
		model->setPosition(model->getPosition()+positionDeltaPerMS*(float) elapsed);
	}
	else
	{
		model->setPosition(position);
	}

	float curRotationDelta = GetRotationDifference(rotationAroundYAxis,model->getRotation().Y);
	float interpThisTickRotation = rotationDeltaPerMS*(float)elapsed;
	if (curTime < interpEndTime && fabs(interpThisTickRotation) < fabs(curRotationDelta))
	{
		model->setRotation(model->getRotation()+core::vector3df(0,interpThisTickRotation,0));
	}
	else
	{
		model->setRotation(core::vector3df(0,rotationAroundYAxis,0));
	}

	if (isDead)
	{
		UpdateAnimation(scene::EMAT_DEATH_FALLBACK);
		model->setLoopMode(false);
	}
	else if (curAnim!=scene::EMAT_ATTACK)
	{
		if (isMoving)
		{
			UpdateAnimation(scene::EMAT_RUN);
			model->setLoopMode(true);
		}
		else
		{
			UpdateAnimation(scene::EMAT_STAND);
			model->setLoopMode(true);
		}
	}
}
void PlayerReplica::UpdateAnimation(irr::scene::EMD2_ANIMATION_TYPE anim)
{
    // se llama desde Update, no necesario en raknet. Para animar el modelo
	if (anim!=curAnim)
		model->setMD2Animation(anim);
	curAnim=anim;
}
float PlayerReplica::GetRotationDifference(float r1, float r2)
{
    // Funcion auxiliar no necesaria para raknet
	float diff = r1-r2;
	while (diff>180.0f)
		diff-=360.0f;
	while (diff<-180.0f)
		diff+=360.0f;
	return diff;
}
void PlayerReplica::OnAnimationEnd(scene::IAnimatedMeshSceneNode* node)
{
    // De irrlicht, nada de raknet
	if (curAnim==scene::EMAT_ATTACK)
	{
		if (isMoving)
		{
			UpdateAnimation(scene::EMAT_RUN);
			model->setLoopMode(true);
		}
		else
		{
			UpdateAnimation(scene::EMAT_STAND);
			model->setLoopMode(true);
		}
	}
}
void PlayerReplica::PlayAttackAnimation(void)
{
    // Funcion auxiliar no necesaria para raknet
	if (isDead==false)
	{
		UpdateAnimation(scene::EMAT_ATTACK);
		model->setLoopMode(false);
	}
}
bool PlayerReplica::IsDead(void) const
{
    // Funcion auxiliar no necesaria para raknet
	return deathTimeout > RakNet::GetTimeMS();
}
//BallReplica::BallReplica()
//{
//	creationTime=RakNet::GetTimeMS();
//}
//BallReplica::~BallReplica()
//{
//}
//void BallReplica::WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const
//{
//	allocationIdBitstream->Write(RakNet::RakString("BallReplica"));
//}
//void BallReplica::SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
//{
//	BaseIrrlichtReplica::SerializeConstruction(constructionBitstream, destinationConnection);
//	constructionBitstream->Write(shotDirection);
//}
//bool BallReplica::DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection)
//{
//	if (!BaseIrrlichtReplica::DeserializeConstruction(constructionBitstream, sourceConnection))
//		return false;
//	constructionBitstream->Read(shotDirection);
//	return true;
//}
//void BallReplica::PostDeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)
//{
//	// Shot visible effect and BallReplica classes are not linked, but they update the same way, such that
//	// they are in the same spot all the time
//	demo->shootFromOrigin(position, shotDirection);
//
//	// Find the owner of this ball, and make them play the attack animation
//	unsigned int idx;
//	for (idx=0; idx < PlayerReplica::playerList.Size(); idx++)
//	{
//		if (PlayerReplica::playerList[idx]->creatingSystemGUID==creatingSystemGUID)
//		{
//			PlayerReplica::playerList[idx]->PlayAttackAnimation();
//			break;
//		}
//	}
//}
//void BallReplica::PreDestruction(RakNet::Connection_RM3 *sourceConnection)
//{
//	// The system that shot this ball destroyed it, or disconnected
//	// Technically we should clear out the node visible effect too, but it's not important for now
//}
//RM3SerializationResult BallReplica::Serialize(RakNet::SerializeParameters *serializeParameters)
//{
//	BaseIrrlichtReplica::Serialize(serializeParameters);
//	return RM3SR_BROADCAST_IDENTICALLY;
//}
//void BallReplica::Deserialize(RakNet::DeserializeParameters *deserializeParameters)
//{
//	BaseIrrlichtReplica::Deserialize(deserializeParameters);
//}
//void BallReplica::Update(RakNet::TimeMS curTime)
//{
//	// Is a locally created object?
//	if (creatingSystemGUID==rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
//	{
//		// Destroy if shot expired
//		if (curTime > shotLifetime)
//		{
//			// Destroy on network
//			BroadcastDestruction();
//			delete this;
//			return;
//		}
//	}
//
//	// Keep at the same position as the visible effect
//	// Deterministic, so no need to actually transmit position
//	// The variable position is the origin that the ball was created at. For the player, it is their actual position
//	RakNet::TimeMS elapsedTime;
//	// Due to ping variances and timestamp miscalculations, it's possible with very low pings to get a slightly negative time, so we have to check
//	if (curTime>=creationTime)
//		elapsedTime = curTime - creationTime;
//	else
//		elapsedTime=0;
//	irr::core::vector3df updatedPosition = position + shotDirection * (float) elapsedTime * SHOT_SPEED;
//
//	// See if the bullet hit us
//	if (creatingSystemGUID!=rakPeer->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS))
//	{
//		if (playerReplica->IsDead()==false)
//		{
//			float playerHalfHeight=demo->GetSyndeyBoundingBox().getExtent().Y/2;
//			irr::core::vector3df positionRelativeToCharacter = updatedPosition-playerReplica->position;//+core::vector3df(0,playerHalfHeight,0);
//			if (demo->GetSyndeyBoundingBox().isPointInside(positionRelativeToCharacter))
//			//if ((playerReplica->position+core::vector3df(0,playerHalfHeight,0)-updatedPosition).getLengthSQ() < BALL_DIAMETER*BALL_DIAMETER/4.0f)
//			{
//				// We're dead for 3 seconds
//				playerReplica->deathTimeout=curTime+3000;
//			}
//		}
//	}
//}
RakNet::Replica3 *Connection_RM3DireW::AllocReplica(RakNet::BitStream *allocationId, ReplicaManager3 *replicaManager3)
{
    // Obtiene el mensaje desde Replica3::WriteAllocationID
    // Según este mensaje crearemos un objeto u otro.
	RakNet::RakString typeName; allocationId->Read(typeName);
	if (typeName=="PlayerReplica") {BaseIrrlichtReplica *r = new PlayerReplica; r->demo=demo; return r;}
	if (typeName=="BallReplica") {BaseIrrlichtReplica *r = new BallReplica; r->demo=demo; return r;}
	return 0;
}
