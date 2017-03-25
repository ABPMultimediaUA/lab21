
#include "AStarAlgorithm.h"
#include "AStarHeuristics.h"
#include "Scene.h"
#include <cmath>

Humanoid::Humanoid()
{
    steps = 19;
    m_speed = 0.5;

    //set up state machine
    h_pStateMachine = new StateMachine<Humanoid>(this);

    h_pStateMachine->SetCurrentState(HPatrolState::Instance());

    //Creación fov
    //fovnode = GEInstance->createNode("media/fov");
    //fovnode->setMaterialFlag(EMF_WIREFRAME, true);
    //fovnode->setPosition(getPosition());
    //fovnode->setRotation(getRotation());
    percep = new Perception();
    pathp = new Pathplanning();
    /**** Special nodes ****/
    selector1 = new Selector;
    sequence1 = new Sequence;
    /**** Tasks ****/
    path = new PathplanningTask(pathp, this/*, fovnode*/);
    perc = new PerceptionTask(percep, this, /*fovnode,*/ path);
    patrol = new PatrolTask(this/*, fovnode*/);
    /**** Creating the tree ****/

    selector1->addChild(sequence1);
    selector1->addChild(patrol);

    sequence1->addChild(perc);
    sequence1->addChild(path);

    currentNode = nextNode = finalNode = 0;

}

void Humanoid::Update()
{
    steps--;
    h_pStateMachine->Update();
}

void Humanoid::update()
{
    int target = rand() % 8;

    //selector1->run();
    NavigationGraph& navGraph = Scene::Instance()->getNavGraph();

    if(currentNode == finalNode){
        Graph_SearchAStar a(navGraph, currentNode, target);
        route = a.GetPathToTarget();
        for (std::list<int>::iterator e = route.begin();
         e != route.end();
         ++e)
            std::cout<<"Iterator "<<*e<<std::endl;
        if(route.size()>1){
            nextNode = route.front();
            route.pop_front();
            finalNode = route.back();
        }
    }

    if(route.size()>0)
    if(currentNode == nextNode)
    {
        nextNode = route.front();
        route.pop_front();
        dwe::vec2f v1(navGraph.getNode(currentNode).getPosition());
        dwe::vec2f v2(navGraph.getNode(nextNode).getPosition());
        dwe::vec2f vec(v2.x - v1.x, v2.y - v1.y);
        float length = sqrt(vec.x * vec.x + vec.y * vec.y);

        float angle = (float)  (    acos(       ((double)1*vec.x + (double)0*vec.y)/length     )* 180/M_PI     );
        std::cout<<"Angle1 "<<angle<<std::endl;
        if(vec.y>0 && angle<180)
            angle+=180;
        setRotation(dwe::vec3f(0, angle, 0));
        std::cout<<"Angle2 "<<angle<<std::endl;

        vec.x /= length;
        vec.y /= length;

        movement = vec;
    }

    if(currentNode != finalNode)
    setPosition(dwe::vec3f(movement.x*m_speed, getPosition().y, movement.y*m_speed));

    if(abs(getPosition().x - navGraph.getNode(nextNode).getPosition().x) < m_speed && abs(getPosition().z - navGraph.getNode(nextNode).getPosition().y) < m_speed){
        std::cout <<"Llego al nodo "<<nextNode<<std::endl;
        currentNode = nextNode;
    }

}

StateMachine<Humanoid>* Humanoid::GetFSM()const
{
    return h_pStateMachine;
}

int Humanoid::getSteps ()
{
    return steps;
}

Humanoid::~Humanoid()
{
    delete h_pStateMachine;
    delete percep;
    delete pathp;
    delete selector1;
    delete sequence1;
    delete path;
    delete perc;
    delete patrol;
    //delete fovnode;
}
