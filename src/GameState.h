#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include "CameraController.h"
#include "BuildingManager.h"
#include "Hud.h"
#include "IAEngine/RootNode.h"

class GameState : public State {
    
    public:
        GameState();
        ~GameState();

        void Init();
        void Input();
        void Update();
        void Render();
        void CleanUp();

        Terrain* getMap();
        
    private:
        CameraController *camera;
        Terrain *map;
        Hud * hud;
        RootNode *nodeRootIA;
};

#endif