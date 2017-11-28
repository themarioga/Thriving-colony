#ifndef SIDERURGY_NODE_H
#define SIDERURGY_NODE_H

#include "Node.h"

class SiderurgyNode : public Node {

    public:
        SiderurgyNode(Node *);
        virtual ~SiderurgyNode();

    private:
        virtual void question();
};

#endif