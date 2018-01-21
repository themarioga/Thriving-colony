#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include "IOEngine/EventSystem.h"

#include <IOEngine/InputManager.h>
#include <GraphicEngine/Window.h>

#include "SoundEngine/SoundSystem.h"
class Game {
    public:
        static Game* Instance();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

        Window *getWindow();
        InputManager *getIO();
        Mouse *getCursor();
        EventSystem *getEvents();
		MenuState *getMenuState();
		GameState *getGameState();
        
    protected:
        Game();
        virtual ~Game();
        Game(const Game & );
        Game &operator = (const Game & );

    private:
        static Game* pinstance;
        State *state;
        Window *window;

        MenuState *menu;
        GameState *game;

        InputManager *io;

        EventSystem *events;
        
        Mouse *cursor;
        SoundSystem *soundSystem;
};

#endif