#ifndef MELEE_ATTACK_NODE_H
#define MELEE_ATTACK_NODE_H

#include "Node.h"

class MeleeAttackNode : public Node {

    public:
        MeleeAttackNode(Node *);
        virtual ~MeleeAttackNode();

        virtual void question();
        
    private:
};

#endif