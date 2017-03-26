#include "Game.h"
#include "GSMainMenu.h"

int main()
{
    Game::getInstance()->ChangeState(GSMainMenu::getInstance());
    GEInstance->init();
    Game::getInstance()->Run();

    return 0;
}
