#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class bwBody
{
    public:
        bwBody(const b2PolygonShape& bShape, b2Body* const bBody, IrrlichtDevice* const bDevice)
        {
            shape = bShape;
            body = bBody;
            device = bDevice;
        }

        void update()
        {
            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();

            const b2Mat22 mat(angle);
            for(int i=0; i < shape.GetVertexCount(); i++)
            {
                //const b2Vec2 vec = body->GetWorldPoint(shape.GetVertex(i));
                const b2Vec2 vec = body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i)));

                device->getVideoDriver()->draw2DLine(position2d<s32>(vec.x,vec.y),
                    (i+1 != shape.GetVertexCount()) ?
                    position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).x, body->GetWorldPoint(b2Mul(mat,shape.GetVertex(i+1))).y):
                    position2d<s32>(body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).x,body->GetWorldPoint(b2Mul(mat,shape.GetVertex(0))).y),
                    SColor(255, 255, 255, 255));
            }
        }

    private:
        b2PolygonShape shape;
        b2Body* body;
        IrrlichtDevice* device;
};

irr::core::array<bwBody*> bodies;


void createRigidBox(b2World& world, const vector2d<s32>& pos, IrrlichtDevice* const device)
{
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

   bwBody* bww = new bwBody(dynamicBox, body, device);

   bodies.push_back(bww);
}

IrrlichtDevice *device = 0;

b2Vec2 gravity(0.0f, 10.0f);
bool doSleep = true;
b2World world(gravity, doSleep);

class MyEventReceiver : public IEventReceiver
{
public:
   virtual bool OnEvent(const SEvent& event)
   {
      // Remember the mouse state
      if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
      {
         switch(event.MouseInput.Event)
         {
         case EMIE_LMOUSE_LEFT_UP:
         {
            createRigidBox(world, vector2d<s32>(event.MouseInput.X, event.MouseInput.Y), device);
         }
            break;

         default:
            break;
         }
      }
   }


   MyEventReceiver()
   {
   }
};


int main()
{
    MyEventReceiver receiver;
   device = createDevice( video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

   if (!device)
      return 1;


   device->setWindowCaption(L"Irrlicht/Box2D Sample");


   IVideoDriver* driver = device->getVideoDriver();
   ISceneManager* smgr = device->getSceneManager();
   IGUIEnvironment* guienv = device->getGUIEnvironment();
   ITimer* timer = device->getTimer();


   guienv->addStaticText(L"Box2D integrated with Irrlicht",
      rect<s32>(10,10,130,22), true);


   smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

   /////////////////
   // Box2D Stuff //
   /////////////////

   // Define the ground body.
   b2BodyDef groundBodyDef;
   groundBodyDef.position.Set(290.0f, 250.0f);

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

   for(int i=0; i < 11; i++)
   {
        for(int j=0; j < 8; j++)
        {
            createRigidBox(world,vector2d<s32>(110+(i*45), 230-(j*20)), device);
        }
   }

   // Prepare for simulation. Typically we use a time step of 1/60 of a
   // second (60Hz) and 10 iterations. This provides a high quality simulation
   // in most game scenarios.
   float32 timeStep = 1.0f / 250.0f;
   int32 velocityIterations = 6;
   int32 positionIterations = 2;


    f32 TimeStamp = timer->getTime();
   f32 DeltaTime = timer->getTime() - TimeStamp;



   while(device->run())
   {
      driver->beginScene(true, true, SColor(255,100,101,140));

      DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();

      // Instruct the world to perform a single step of simulation.
      // It is generally best to keep the time step and iterations fixed.
      world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);

      // Clear applied body forces. We didn't apply any forces, but you
      // should know about this function.
      world.ClearForces();

      for(int i=0; i < bodies.size(); i++)
      {
          bodies[i]->update();
      }

      bww->update();

      smgr->drawAll();
      guienv->drawAll();

      driver->endScene();
   }

   for(int i=0; i < bodies.size(); i++)
    {
        delete bodies[i];
    }
    bodies.clear();

   delete bww;

   device->drop();

   return 0;
}
