#include "Game.h"
#include "GSMainMenu.h"
#include "NetGame.h"
#include "GSIngame.h"
//#include "Hud.h"

int main()
{
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    GEInstance->init();
    Game::getInstance()->Run();
    //NetInstance->close();

	return 0;

	/******************/
	//Hud* hud = new Hud();
	//hud->draw();
	/*****************/
}
