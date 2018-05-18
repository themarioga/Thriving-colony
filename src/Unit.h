#ifndef UNIT_H
#define UNIT_H


#include <string>
#include <list>
#include <Types.h>
#include <Entity.h>
#include <PathPlanner/PathManager.h>
#include <EntityData.h>
#include <Enumeration.h>

//class PathManager;
class UnitManager;
class Sensor;
class UnitFighter;
/**
 * @class Unit.
 * @brief Create a Unit type object. Public heritage from Entity class.
 */
class Unit : public Entity {
    
    public:
        /**
         * @brief Unit constructor.
         * 
         * @param SceneNode is the layer where the unit is going to be created.
         * @param i32 is the id number that will identify the unit.
         * @param Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA. 
         * @param UnitData is the data for this unit.
         */
        Unit(SceneNode* _layer, i32 _id, Enumeration::Team _team, UnitData baseData, UnitManager* _unitManager);
        
        /**
         * @brief Unit destructor.
         */
        virtual ~Unit();

        /**
         * @brief Decrease the metal and crystal cost of the unit to the player's mteal and crystal amount and increase player's happiness, citizens and army level depending of the values of the unit.
         */
        virtual void preTaxPlayer();

        /**
         * #brief Increase the palyer's army size.
         */
        virtual void posTaxPlayer();

        /**
         * @brief Update the troop depending of its state.
        */
        void update();

        /**
         * @brief Move the unit.
         */
        void moveTroop();

        /**
         * @brief Determinate if the target of the unit is in its range of attack.
         * @return True when the target is in the range of attack of the unit and false in other case. 
         */
        bool inRangeOfAttack();

        /**
         * @breif Switch the current state of the unit to the state passed by parameter.
         * @param Enumeration::UnitState is the new state of the unit.
         */
        void switchState(Enumeration::UnitState);

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Recruiting.
         */
        void recruitingState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Idle.
         */
        void idleState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Move.
         */
        void moveState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::AttackMove.
         */
        void attackMoveState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Attack.
         */
        void attackState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Chase.
         */
        void chaseState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Retract.
         */
        void retractState();

        /**
         * @brief Finish recruiting the unit.
         */
        void triggerRecruitedCallback();

        /**
         * @brief Finish retracting the unit.
         */
        void triggerRetractedCallback();

        /**
         * @brief 
         * 
         * @param
         */
        void setUnitCell(Vector2<f32>);

        /**
         * @brief Set the position of the unit.
         * 
         * @param The Vector2 is the position that is going to be assigned to the unit.
         */
        void setTroopPosition(Vector2<f32>);

        /**
         * @brief Set the position where the unit is going to walk to.
         * 
         * @param The Vector2 is the destination that is going to be assigned to the unit.
         */
        void setTroopDestination(Vector2<f32>);

        /**
         * @brief
         * 
         * @param
         */
        void setPath(std::list<Vector2<f32> >);

        /**
         * @brief
         * 
         * @param
         */
        void setPathToTarget(Vector2<f32>);

        /**
         * @brief
         * 
         * @param
         */
        void setRecruitedCallback(std::function<void(Unit*)>);

        /**
         * @brief
         * 
         * @param
         */
        void setRetractedCallback(std::function<void(Unit*)>);

        /**
         * @brief 
         * 
         * @return
         */
        std::string getAttackEvent();

        /**
         * @brief 
         * 
         * @return
         */
        std::string getMoveEvent();

        /**
         * @brief 
         * 
         * @return
         */
        std::string getSelectEvent();

        /**
         * @brief Get the destination of the unit.
         * 
         * @return Vector2 that will be the value of vectorDes variable.
         */
        Vector2<f32> getDestination();

        /**
         * @brief 
         * 
         * @return
         */
        std::list< Vector2<f32> > getPath();
        
        /**
         * @brief Get the type of unit of the troop.
         * 
         * @return std::string that will be the value of type variable.
         */
        std::string getType();

        /**
         * @brief Get the current state of the unit.
         * 
         * @return Enumeration::UnitState that will be the value of state variable.
         */
        Enumeration::UnitState getState();

        /**
         * @breif Get the army level that the unit provides to the player's city.
         * @return i32 that will be the value of the armyLevel variable.
         */
        i32 getArmyLevel();

        /* New */
        std::vector< Vector2<f32> > getTroopsPosition();        
        std::vector< UnitFighter* > getUnitFighters();
        void calculateDirection();
        bool hasArrived();
        void updateFlockingSensor();
        void takeDamage(i32 _damage);
        void updateUnitFighters();
        void setTarget(Entity *newTarget);
        
    private:
        /**
         * @brief Initialize the variables.
         */
        void Init();

        //Current state of the unit that will conditione its actions.
        Enumeration::UnitState state;

        //Type of the unit.
        const std::string type;

        //Speed with which the unit moves.
        const i32 moveSpeed;

        //Speed with which the unit attacks.
        const i32 attackSpeed;

        //Damage infliceted by the unit.
        i32 attackDamage;

        //True when the unit is moving and false in other case.
        bool moving;

        bool canAttack;
        //Amount of army level that provides to the player's city.
        const i32 armyLevel;

        //Timer that controls the time of training of the unit.
        Timer* recruitingTimer;
        Timer* enemySensorTimer;
        Timer* attackTimer;
        Timer* chaseTimer;

        //
        class PathManager* pathManager;

        //
        std::list< Vector2<f32> > pathFollow;

        //Method to finish the training of the unit.
        std::function<void(Unit*)> recruitedCallback;

        //Method to finish of retracting the unit.
        std::function<void(Unit*)> retractedCallback;

        //Destination of the unit.
        Vector2<f32> vectorDes;
        Vector2<f32> vectorSpd;
        Vector2<f32> vectorDir;

        //True when the unit is ready to get into the command center and false in other case.
        bool readyToEnter;

        //
        const std::string attackEvent;

        //
        const std::string moveEvent;

        //
        const std::string selectEvent;

        //
        std::vector< UnitFighter* > unitFighters;
        std::vector< UnitFighter* > nearUnitFighters;
        const f32 maxPositionDesviation;
        const i32 unitFighterHP;
        Sensor* unitSensor;
        UnitManager* unitManager;
};

#endif