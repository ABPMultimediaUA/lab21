#ifndef GAME_H
#define GAME_H

#include "GState.h"

class Game {
public:
    Game();
    ~Game();
    void Run();
    void ChangeState(GState *newState);
    static Game* getInstance();
    const bool isRunning(){ return running; };
    void setRunning(bool mRunning);
    bool getRunning();

private:
    void Quit();
    void HandleEvents();
    void Update();
    void Render();
    GState *CurrentState;
    bool running;

};

#endif /* GAME_H */
