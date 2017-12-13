#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "GraphicEngine/Vector3.h"
//#include "Battle.h"

class Unit : public Entity {
    
    public:
        Unit(int, Vector3<float>*, int, int, int, int, int, bool, Box3D<float>*, Model*);
        virtual ~Unit();

        //Getters
        Entity *getTarget();

        //Setters
        void setMoving(bool);
        void setAttacking(bool);

        /////////////////////////
        void attack();
        void updateTarget();
        //void assignBattle(Battle*);

    protected:
        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        int attackRange;
        int viewRange;

        bool moving;
        bool attacking;

        Entity* target;

        //Battle* battleInvolved;

    private:
        
};

#endif