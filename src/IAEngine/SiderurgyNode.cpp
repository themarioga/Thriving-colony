#include "SiderurgyNode.h"
#include "../IA.h"

SiderurgyNode::SiderurgyNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SiderurgyNode::~SiderurgyNode() {
    delete father;
}

void SiderurgyNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildSiderurgy);
    //std::cout << "Construyo una siderurgia" << std::endl;
    if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost)) {
        Vector3<f32> v = IA::getInstance() -> determinatePositionBuilding();
        IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, true);
    }
}