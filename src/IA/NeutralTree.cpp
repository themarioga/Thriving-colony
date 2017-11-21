#include "NeutralTree.h"

NeutralTree::NeutralTree(IA* iaPnt) : BehaviourTree(iaPnt) {
    happinessThreshold = 80;
    quarryMilestone = 50;
    mountedCreatureMilestone = 80;
    wallMilestone = 70;
    towerMilestone = 90;
    barnMilestone = 60;
    workshopMilestone = 65;
    creatureMilestone = 100;

    metalThreshold = 1.5;
    crystalThreshold = 1.2;
    citizensThreshold = 2.5;
    armyThreshold = 0.1;
    meleeThreshold = 0.5;
    rangeThreshold = 0.45;
    siegeThreshold = 0.05;
}

NeutralTree::~NeutralTree() {
    
}

void NeutralTree::developCity() { //Es asi?
    //First branch: Resources
    if (needResourcesInvestment()) {
        resourcesBranch();
    } else {
        //Second branch: Homes
        if (calculateCitizensRate() < citizensThreshold) {
            //ToDo: Construir viviendas
        } else {
            //Third branch: Services
            if (ia->getHappiness() < happinessThreshold) {
                serviceBranch();
            } else {
                //Fourth branch: Army
                if (needArmyInvestment()) {
                    armyBranch();
                }
            }
        }
    }
}

/**
 * Determines wheter or not you are ready to attack
 */
bool NeutralTree::readyToAttack() {
    //ToDo: Determinar cuando se esta listo
    return false;
}