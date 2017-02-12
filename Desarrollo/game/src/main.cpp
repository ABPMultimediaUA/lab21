#include "Game.h"
#include "GSMainMenu.h"
#include "NetGame.h"

int main()
{
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    GEInstance->init();
    Game::getInstance()->Run();
    NetInstance->close();

	return 0;
}
