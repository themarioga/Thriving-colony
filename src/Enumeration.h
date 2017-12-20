#ifndef ENUMERATION_H
#define ENUMERATION_H

class Enumeration {
    
    public:
        enum BuildingType {
            Barn,
            Barrack,
            Hospital,
            House,
            MainBuilding,
            Market,
            Quarry,
            Siderurgy,
            School,
            Tower,
            Wall,
            Workshop
        };

        enum Race {
            Drorania,
            Kaonov
        };

        enum Team {
            Human,
            IA
        };

        enum EventType {
            Attacking,
            BeingAttacked,
            DeployTroops,
            RetractTroops,
            StopBeingAttack
        }; 

        enum idGUI {
            ID0,
            GUI_ID_BUILDING_BUTTON,

            GUI_ID_BUILD_SCHOOL_BUTTON,
            GUI_ID_BUILD_MARKET_BUTTON,
            GUI_ID_BUILD_HOSPITAL_BUTTON,
            GUI_ID_BUILD_SIDERURGY_BUTTON,
            GUI_ID_BUILD_QUARRY_BUTTON,
            GUI_ID_BUILD_HOME_BUTTON,
            GUI_ID_BUILD_BARRACK_BUTTON,
            GUI_ID_BUILD_BARN_BUTTON,
            GUI_ID_BUILD_WORKSHOP_BUTTON,
            GUI_ID_BUILD_WALL_BUTTON,
            GUI_ID_BUILD_TOWER_BUTTON,

            GUI_ID_QUIT_BUTTON,
            GUI_ID_CLOSE_PANEL_BUTTON,
            
            GUI_ID_CREATE_TROOP_1_BUTTON,
            GUI_ID_CREATE_TROOP_2_BUTTON,
            GUI_ID_CREATE_TROOP_3_BUTTON
        };

        //Special type, used to pass info to the UnitManager
        //in order to control which unit is created
        struct UnitType{
            enum Class{
                Ranged,
                Melee
            };
            enum SubClass
            {
                StandardR,
                AdvancedR,
                Launcher,
                Desintegrator,
                StandardM,
                AdvancedM,
                Idol
            };
            Class unitClass;
            SubClass unitSubClass;
        };

    private:
        
};

#endif