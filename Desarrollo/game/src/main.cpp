#include <iostream>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GraphicsEngine.h>
#include <irrKlang.h>
#include <vector>
#include <time.h>
#include <typeinfo>
#include <unistd.h>  //para sleep

#include "WorldInstance.h"

#include "Game.h"
#include "GSMainMenu.h"

#include "NetGame.h"
#include "Player.h"
#include "Bat.h"
#include "Mother.h"
#include "Guardian.h"
#include "Legless.h"

#include "SpeedBoost.h"
#include "Medkit.h"

#include "CShotgun.h"
#include "AmmoGun.h"

#include "Selector.h"
#include "Sequence.h"

#include "Pathplanning.h"
#include "Perception.h"

#include "CheckIfDoorIsOpenTask.h"
#include "ApproachDoorTask.h"
#include "OpenDoorTask.h"
#include "WalkThroughDoorTask.h"
#include "CloseDoorTask.h"
#include "PathplanningTask.h"
#include "PerceptionTask.h"
#include "PatrolTask.h"

#include "EntityPhysics.h"
#include "ScenaryElement.h"





///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());

    GEInstance->init();

    Game::getInstance()->Run();
    /*********************************************************************/
    /**                                                                 **/
    /**                           GAME RUNNING                          **/
    /**                                                                 **/
    /*********************************************************************/


    //delete bjoint;

    NetInstance->close();

	return 0;
}


