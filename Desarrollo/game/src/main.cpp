#include "Game.h"
#include "GSMainMenu.h"

int main()
{
    Game* game = Game::getInstance();  // Necesario asi pq game en el constructor llama a GraphicsEngine init
    game->ChangeState(GSMainMenu::getInstance());
    game->Run();
	return 0;
}
