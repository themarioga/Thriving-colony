#ifndef RETRACT_TROOPS_NODE_H
#define RETRACT_TROOPS_NODE_H

#include "Node.h"

class RetractTroopsNode : public Node {

    public:
        RetractTroopsNode(Node*);
        virtual ~RetractTroopsNode();

        virtual void question();
        
    private:
};

#endif