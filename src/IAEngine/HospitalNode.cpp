#include "HospitalNode.h"
#include "../IA.h"

HospitalNode::HospitalNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

HospitalNode::~HospitalNode() {
    delete father;
}

void HospitalNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::BuildHospital);
    if (IA::getInstance() -> getQuarryAmount() == 0) {
        IA::getInstance() -> getTree() -> setRequireCrystal(true);
    } else {
        //std::cout << "Contruyo un hospital" << std::endl;
        if (IA::getInstance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost, Enumeration::Team::IA)) {
            Vector3<float> v = IA::getInstance() -> determinatePositionBuilding();
            IA::getInstance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, Enumeration::Team::IA);
        }
    }
}