#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <sstream>
#include "State.h"
#include "CameraController.h"
#include "Hud.h"
#include "PauseMenu.h"
#include "IA.h"
#include "Human.h"
#include "BuildingManager.h"
#include "BattleManager.h"

#include <IAEngine/RootNode.h>

#include <SoundEngine/SoundSystem.h>

#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>
#include <Types.h>

/**
 * @class GameState
 * @brief Tiene herencia publica de State y crea un objeto tipo GameState
 */
class GameState : public State {
    
    public:
        /**
		 * @brief Constructor de GameState
		 */
        GameState();
        /**
		 * @brief Destructor
		 */
        virtual ~GameState();

         /**
		 * @brief Inicializa GameState
		 */
        void Init();
        /**
		 * @brief Recoge las entradas de teclado y raton
		 */
        void Input();
        /**
		 * @brief Actualiza
		 */
        void Update();
        /**
		 * @brief Renderiza
		 */
        void Render();
        /**
		 * @brief Constructor
		 */
        void CleanUp();
        /**
        * @brief Devuelve el mapa
        * @return objeto de tipo Terrain
        */
        Terrain* getTerrain();
         /**
        * @brief Devuelve la interfaz
        * @return objeto de tipo Hud
        */
        Hud* getHud();
         /**
        * @brief Devuelve el manejador de batalla
        * @return objeto de tipo BattleManager
        */
        BattleManager* getBattleManager();

        void cleanGamePaused();
        
    private:
        Light *light;
        CameraController *camera;
        Terrain *map;
        Hud * hud;
        BattleManager *battleManager;

        // This is for pausing, in a future it will be a gamestate different?
        bool gamePaused;
        PauseMenu *pauseMenu;

        i32 prevWindowWidth, prevWindowHeight;
};

#endif