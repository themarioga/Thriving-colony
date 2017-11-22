#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState : public State {
    
    public:
        GameState();
        ~GameState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

    private:
    
};

#endif