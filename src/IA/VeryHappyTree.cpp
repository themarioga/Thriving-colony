#include "VeryHappyTree.h"
#include "../IA.h"
#include <iostream>

VeryHappyTree::VeryHappyTree() : BehaviourTree() {
    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 0.6;
    crystalThreshold = 0.4;
    citizensThreshold = 0.3;
    armyThreshold = 0.2;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;
}

VeryHappyTree::~VeryHappyTree() {

}
///TODO quitar IA de los arboles

void VeryHappyTree::developCity() {

    //First branch: Services
    if (IA::getInstance()->getHappiness() < happinessThreshold) {
        std::cout << "Voy a invertir en felicidad" << std::endl;
        serviceBranch();
    } else {
        //Second branch: Resources
        if (needResourcesInvestment()) {
            std::cout << "Voy a invertir en recursos" << std::endl;
            resourcesBranch();
        } else {
            //Third branch: Homes
            if (calculateCitizensRate() < citizensThreshold) {
                std::cout << "Voy a invertir en casas" << std::endl;
                IA::getInstance() ->increaseCitizens();
                //ToDo: Construir viviendas
            } else {
                //Fourth branch: Army
                if (needArmyInvestment()) {
                    std::cout << "Voy a invertir en ejercito" << std::endl;
                    armyBranch();
                } else {
                    std::cout << "No hago nada" << std::endl;
                    IA::getInstance() ->increaseCitizens();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool VeryHappyTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}