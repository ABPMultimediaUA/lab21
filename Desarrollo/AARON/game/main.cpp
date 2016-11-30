#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


#define bwInitPosX 100
#define bwInitPosY 100

#define bwBow_W 1.0f
#define bwBow_H 1.0f

///////// EL MUNDO DE BOX2D /////////
class bwBody{
    public:
        bwBody(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice){
            shape = bShape;
            body = bBody;
            device = bDevice;
        }

        void update(){
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();

            const b2Mat22 mat(0,1,1,0); //CAMBIADO POR AARON... añadido los "0"
            for(int i=0; i < shape.GetVertexCount(); i++){
                //const b2Vec2 vec = body->GetWorldPoint(shape.GetVertex(i));
                const b2Vec2 vec = body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i)));

                device->getVideoDriver()->draw2DLine(position2d<s32>(vec.x,vec.y),
                    (i+1 != shape.GetVertexCount()) ?
                    position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).x, body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).y):
                    position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).x,body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).y),
                    SColor(255, 255, 255, 255));
            }
        }

        b2Body* getBwBody(){return body;};
    private:
        b2PolygonShape shape;
        b2Body* body;
        IrrlichtDevice* device;
};

irr::core::array<bwBody*> bodies; //ARRAY "BODIES"
bwBody* bwPlayer; //BOX2DPLAYER

void createPlayer(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(bwBow_W, bwBow_H);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    bwPlayer = new bwBody(dynamicBox, body, device);
}

void createRigidBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    fixtureDef.restitution = 0.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    bwBody* bww = new bwBody(dynamicBox, body, device);

    bodies.push_back(bww);
}

void createStaticBox(b2World& world, const vector2d<s32>& pos, const int tamX, const int tamY, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape staticBox;
    staticBox.SetAsBox(tamX, tamY);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticBox;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    bwBody* bww = new bwBody(staticBox, body, device);

    bodies.push_back(bww);
}


IrrlichtDevice *device = 0;

b2Vec2 gravity(0.0f, 0.0f);
b2World world(gravity);
///////// EL MUNDO DE BOX2D (END) /////////

//PARA TECLADO Y RATON
class CAppReceiver : public IEventReceiver {
    private:
        bool KeyDown[KEY_KEY_CODES_COUNT];
    public:
         CAppReceiver() {
            for(int i=0;i<KEY_KEY_CODES_COUNT;i++) {
                KeyDown[i] = false;
            }
         }

         virtual bool OnEvent(const SEvent &event) {
            switch(event.EventType) {
                case irr::EET_KEY_INPUT_EVENT:
                    KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                    break;
                case irr::EET_MOUSE_INPUT_EVENT:
                    switch(event.MouseInput.Event){
                        case EMIE_LMOUSE_LEFT_UP:
                            //createRigidBox(world, vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), device);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            return false;
         }

         virtual bool isKeyDown(EKEY_CODE keyCode) const {
            return KeyDown[keyCode];
         }

         virtual bool isKeyUp(EKEY_CODE keyCode) const {
            return !KeyDown[keyCode];
         }

/////START/////////////////////////////////////////////////////////////////////////////////////
        /*
        virtual bool OnEvent(const SEvent& event){
            // Remember the mouse state
            if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
                switch(event.MouseInput.Event){
                    case EMIE_LMOUSE_LEFT_UP:
                        createRigidBox(world, vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), device);
                        break;
                    default:
                        break;
                }
            }
        }
        */
/////END/////////////////////////////////////////////////////////////////////////////////////

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// MAIN //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	//Creamos el receptor que registra el teclado y raton
	CAppReceiver appReceiver;

    /* Illricht */
	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 640), 16,
			false, false, false, &appReceiver);

	if (!device)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"LAB21 - Irrlicht - Box2D");

    // Get a pointer to the VideoDriver, the SceneManager and the graphical user interface environment, so that we do not always have to write
	// device->getVideoDriver(), device->getSceneManager(), ordevice->getGUIEnvironment().
	IVideoDriver*       driver  = device->getVideoDriver();
	ISceneManager*      smgr    = device->getSceneManager();
    IGUIEnvironment*    guienv	= device->getGUIEnvironment();

    ITimer* timer = device->getTimer(); //METIDO DEL DEBUG DRAW DE BOX2D...

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

    //CAMERA (nodo padre, posición, directión)
	ICameraSceneNode* camera1 = smgr->addCameraSceneNode(0, vector3df(0,10,-20), vector3df(0,5,0));
	ICameraSceneNode* camera2 = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	ICameraSceneNode* camera3 = smgr->addCameraSceneNode(0, vector3df(10,50,-20), vector3df(0,5,0));
	smgr->setActiveCamera(camera1); //Activar cámara

	//Player
	IMesh *player = smgr->getMesh("mayas/bluebox.obj");
	if (!player){
		device->drop();
		return 1;
	}

    IMeshSceneNode* node = smgr->addMeshSceneNode( player );

	if (node){
		node->setMaterialFlag(EMF_LIGHTING, false);
	}

	//Escenario
	IMesh *escenario = smgr->getMesh("mayas/redfloor.obj");
	if (!escenario){
		device->drop();
		return 1;
	}

    IMeshSceneNode* node2 = smgr->addMeshSceneNode( escenario );

	if (node2){
		node2->setMaterialFlag(EMF_LIGHTING, false);
        node2->setRotation(vector3df(0.f,180.f,0.f));
	}

    /////////////////
   // Box2D Stuff //
   /////////////////
/*
   // Define the ground body.
   b2BodyDef groundBodyDef;
   groundBodyDef.position.Set(290.0f, 350.0f);

   // Call the body factory which allocates memory for the ground body
   // from a pool and creates the ground box shape (also from a pool).
   // The body is also added to the world.
   b2Body* groundBody = world.CreateBody(&groundBodyDef);

   // Define the ground box shape.
   b2PolygonShape groundBox;

   // The extents are the half-widths of the box.
   groundBox.SetAsBox(290.0f, 10.0f);

   // Add the ground fixture to the ground body.
   groundBody->CreateFixture(&groundBox, 0.0f);

   bwBody* bww = new bwBody(groundBox, groundBody, device);
*/

//////// CREACION MANUAL DE LAS COLISIONES COINCIDENTES CON EL ESCENARIO
   //for(int i=0; i < 2; i++){
     //   for(int j=0; j < 4; j++){
            //createRigidBox(world,vector2d<s32>(0+(i*45), 0-(j*20)), device);
            createStaticBox(world,vector2d<s32>(87,100), 1, 10,device);
  //      }
   //}

    createPlayer(world,vector2d<s32>(bwInitPosX,bwInitPosY), device);



   // Prepare for simulation. Typically we use a time step of 1/60 of a
   // second (60Hz) and 10 iterations. This provides a high quality simulation
   // in most game scenarios.
   float32 timeStep = 1.0f / 250.0f;
   int32 velocityIterations = 6;
   int32 positionIterations = 2;

    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;


/////////////////////////////////////////////////////////////////////////////////////////////
    //TIEMPO
    u32 then = device->getTimer()->getTime();

    /////booleano
    bool apretado;

    //DEVICE RUN ----------------- BUCLE
	while(device->run()){
        if(device->isWindowActive()){
            //Calcular DELTA TIME ( dt )
            const u32 now = device->getTimer()->getTime();
            const f32 dt = (f32) (now - then) / 1000.f;
            const f32 MOVEMENT_SPEED = 10.0f;

            //CAMBIO DE CAMARA
            if (appReceiver.isKeyDown(KEY_KEY_1)){
                printf("- Camara 1 \n");
                smgr->setActiveCamera(camera1);
            }else if(appReceiver.isKeyDown(KEY_KEY_2)){
                printf("- Camara 2 \n");
                smgr->setActiveCamera(camera2);
            }else if(appReceiver.isKeyDown(KEY_KEY_3)){
                printf("- Camara 3 \n");
                smgr->setActiveCamera(camera3);
            }

            //MOVER CUBO
            //vector3df nodePos = node->getPosition(); //Get Position
            apretado = false;

            if(appReceiver.isKeyDown(KEY_ESCAPE)) {
                 device->closeDevice(); //CERRAR VENTANA
                 return 0;
            } else if(appReceiver.isKeyDown(KEY_RIGHT)) {
                //nodePos.X += MOVEMENT_SPEED * dt;
                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(10.0,0.0));
                apretado = true;
            } else if(appReceiver.isKeyDown(KEY_LEFT)) {
                //nodePos.X -= MOVEMENT_SPEED * dt;
                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(-10.0,0.0));
                apretado = true;
            }else{
                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,0.0));
            }

            if(appReceiver.isKeyDown(KEY_UP)) {
                //nodePos.Z += MOVEMENT_SPEED * dt;
                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,10.0));
                apretado = true;
            } else if(appReceiver.isKeyDown(KEY_DOWN)) {
                //nodePos.Z -= MOVEMENT_SPEED * dt;
                bwPlayer->getBwBody()->SetLinearVelocity(b2Vec2(0.0,-10.0));
                apretado = true;
            }

            if(apretado) {
                cout    << "Estoy en la posicion: X = " << bwPlayer->getBwBody()->GetPosition().x
                        << " ; Y = " << bwPlayer->getBwBody()->GetPosition().y <<endl;
            }

            //node->setPosition(nodePos); //Cambio de posición
            then = now; //Actualizar TIMEPO

            camera1->setTarget(node->getPosition()); //Camara1 mira al nodo del jugador
            camera2->setTarget(node->getPosition()); //Camara2mira al nodo del jugador
            camera3->setTarget(node->getPosition()); //Camara3 mira al nodo del jugador

/////END - ESCRIBIR EN PANTALLA/////////////////////////////////////////////////////////////////////////////////////
            //beginScene() -- TODO LO QUE QUERAMOS ESCRIBIR POR PANTALLA -- endScene().
            driver->beginScene(true, true, SColor(255,100,101,140));

            smgr->drawAll();
            guienv->drawAll();

            DeltaTime = timer->getTime() - TimeStamp;
            TimeStamp = timer->getTime();
            // Instruct the world to perform a single step of simulation.
            // It is generally best to keep the time step and iterations fixed.
            world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
            // Clear applied body forces. We didn't apply any forces, but you
            // should know about this function.
            world.ClearForces();

            for(int i=0; i < bodies.size(); i++){
                bodies[i]->update();
            }
            bwPlayer->update(); //UPDATE de mi player BOX2D
            //Posición actualizada de Irrlicht Player
            node->setPosition(vector3df(bwPlayer->getBwBody()->GetPosition().x - bwInitPosX,0,bwPlayer->getBwBody()->GetPosition().y - bwInitPosY));

////        bww->update();
            driver->endScene();
/////END - ESCRIBIR EN PANTALLA/////////////////////////////////////////////////////////////////////////////////////
        }else{
            device->yield();
        }
	}


{ /////ELIMINANDO TODO////////////parentesis puesto solo para poder minimizar/////////////////////////////////////////////////////////
	for(int i=0; i < bodies.size(); i++){
        delete bodies[i];
    }
    bodies.clear();

    delete bwPlayer; //DELETE player del BOX2D
////    delete bww;

	//Delete the Irrlicht Device created before with createDevice().
	device->drop();
	return 0;
}
}
