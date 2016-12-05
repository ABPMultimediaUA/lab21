#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>

#include "NetGame.h"
#include "Player.h"
#include "Bat.h"
#include "Mother.h"
#include "Guardian.h"
#include "Legless.h"
#include "Dog.h"
#include "Humanoid.h"

#define speed 0.1f


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
    dynamicBox.SetAsBox(10.0f, 10.0f);

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

void createStaticBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device){
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    //bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.X, pos.Y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape staticBox;
    staticBox.SetAsBox(10.0f, 10.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &staticBox;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    bwBody* bww = new bwBody(staticBox, body, device);

    bodies.push_back(bww);
}


IrrlichtDevice *device = 0;

//initPhysicsWorld();
b2Vec2 gravity(0.0f, 0.0f);
b2World world(gravity);
///////// EL MUNDO DE BOX2D (END) /////////


///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // Box2D
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -1.0f);


    // Illricht
    AppReceiver* appReceiver = new AppReceiver();
	GEInstance->init(appReceiver);

	// Motor de red
    NetInstance->open();

    // Creación de jugador
	Player* mainPlayer = GEInstance->createMainPlayer();
	mainPlayer->setPosition(dwe::vec3f(0,24,90));
    dwe::vec3f pos= mainPlayer->getPosition();
    cout << "POS: X = " << pos.x << " ... Y = " << pos.y << " ... Z = " << pos.z << endl;

    // Creación de escenario
	dwe::Node* suelo = GEInstance->createNode("media/suelo");
	dwe::Node* paredes = GEInstance->createNode("media/paredes");
	suelo->setPosition(dwe::vec3f(0,0,0));
	paredes->setPosition(dwe::vec3f(0,35,0));


    // Creación de enemigo Humanoide
	Humanoid* enemyHumanoid = GEInstance->createEnemyHumanoid();
	enemyHumanoid->setPosition(dwe::vec3f(0,24,-70));



	//BOX2D
	cout << "YES ";
    createPlayer(world,vector2d<s32>(0,0), device);
	cout << "YES \n";

	//

	while(GEInstance->isRunning())
	{
//	    if (GEInstance->isWindowActive())
//        {
            dwe::vec3f m(0.0f);
            m = mainPlayer->getPosition();

            dwe::vec3f r(0.0f);
            r = mainPlayer->getRotation();

            if(appReceiver->isKeyDown(KEY_ESCAPE))
            {
                GEInstance->close();
                return 0;
            }
            else
            {
                if(appReceiver->isKeyDown(KEY_RIGHT))
                {
                    m.z -= speed;
                    r.y = 90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_LEFT))
                {
                    m.z += speed;
                    r.y = -90.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_UP))
                {
                    m.x += speed;
                    r.y = 0.f;

                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else if(appReceiver->isKeyDown(KEY_DOWN))
                {
                    m.x -= speed;
                    r.y = 180.f;
                    mainPlayer->setAnimation(dwe::eAnimRun);
                }
                else
                {
                    mainPlayer->setAnimation(dwe::eAnimStand);
                }
            }

            mainPlayer->setPosition(m);
            mainPlayer->setRotation(r);

            GEInstance->draw();
//        }
//        else
//        {
//            GEInstance->yield();
//        }

        NetInstance->update();
	}

	NetInstance->close();

	return 0;
}


