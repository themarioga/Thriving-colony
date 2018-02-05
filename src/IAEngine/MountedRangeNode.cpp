#include "MountedRangeNode.h"
#include "BarnNode.h"
#include "../IA.h"

MountedRangeNode::MountedRangeNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
    /*
    children = new Node*[1];
    children[0] = new BarnNode(this);
    */
}

MountedRangeNode::~MountedRangeNode() {
    delete father;
    //delete[] children;
}

void MountedRangeNode::question() {

    IA::getInstance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedRanged);
    if (IA::getInstance() -> getBuildingManager() -> getAmount(Enumeration::BuildingType::Barn) > 0) {
        //std::cout << "Genero un soldado montado de rango" << std::endl;
        if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost, Enumeration::Team::IA)) {
            // Unit type
            Enumeration::UnitType unitData = Enumeration::UnitType::StandardR; 
            IA::getInstance() -> getUnitManager() -> createTroop(unitData);
        }
    } else {
        IA::getInstance() -> getTree() -> setRequireBarn(true);
        //children[0] -> question();
    }
}