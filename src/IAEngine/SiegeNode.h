#ifndef SIEGE_NODE_H
#define SIEGE_NODE_H

#include "Node.h"

class SiegeNode : public Node {

    public:
        SiegeNode(Node *);
        virtual ~SiegeNode();

    private:
        virtual void question();
};

#endif