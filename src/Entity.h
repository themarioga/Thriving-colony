#ifndef ENTITY_H
#define ENTITY_H

#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Window.h>
#include "Enumeration.h"
//#include "Battle.h"


class Entity {

    public:
        //The consctructor is empty because the object it's constructed in the child
        Entity(SceneNode *layer, int id, int size);
        Entity(SceneNode *layer, int id, const wchar_t *path);
        virtual ~Entity();

        int getHP();
        int getID();
        void setID(int);
        void takeDamage(int);
        void die();

        void setPosition(Vector3<float> vectorData);

        Enumeration::Team getTeam();
        Enumeration::EntityType getEntityType();
        Vector3<float> *getPosition();
        Box3D<float> *getHitbox();
        Model *getModel();
        void updateTarget(Entity*);

        int getAttackRange();
        void changeRedTint();

        virtual void taxPlayer(Enumeration::Team) = 0;

        int getViewRadius();
        
    protected:
        Entity* target;
        
        Model* model;
        Vector3<float> *position;
        Box3D<float>* hitbox;

        int ID;

        int hpMax;
        int hp;
        int viewRadius;

        irr::video::SColor baseColor;

        // Values, costs, etc
        int happiness;
        int cityLevel;
        int metalCost;
        int crystalCost;

        int attackRange;
        
        Enumeration::Team team;
        Enumeration::EntityType entityType;

        float tookDamageTimer;
        float tookDamageCountdown;

        bool finished;

      private:
};

#endif