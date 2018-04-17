#include "DefendNode.h"
#include "DeployTroopsNode.h"
#include "MeleeFootmenNode.h"
#include "BarrackNode.h"
#include <IA.h>

DefendNode::DefendNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[3];
    children[0] = new DeployTroopsNode(this);
    children[1] = new MeleeFootmenNode(this);
    children[2] = new BarrackNode(this);
}

DefendNode::~DefendNode() {
    delete father;
    delete[] children;
}

void DefendNode::question() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        children[0] -> question();
    } else {
        if (IA::Instance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barrack) > 0) {
            children[1] -> question();
        } else {
            children[2] -> question();
        }
    }
}