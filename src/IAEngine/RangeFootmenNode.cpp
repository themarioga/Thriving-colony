#include "RangeFootmenNode.h"
#include "../IA.h"

RangeFootmenNode::RangeFootmenNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

RangeFootmenNode::~RangeFootmenNode(){
    delete father;
}

void RangeFootmenNode::question() {
    //std::cout << "Genero un soldado a pie de rango" << std::endl;
    //ToDo: Generar soldado a pie de rango
    //IA::getInstance()-> increaseRangeAmount();
    if (IA::getInstance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost, Enumeration::Team::IA)) {
        // Unit type
        Enumeration::UnitType unitData; 
        unitData.unitClass = Enumeration::UnitType::Class::Ranged; 
        unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
        // WTF?
        //Vector3<float>* vectorData = new Vector3<float>();

        IA::getInstance() -> getUnitManager() -> createTroop(unitData);
    }
}