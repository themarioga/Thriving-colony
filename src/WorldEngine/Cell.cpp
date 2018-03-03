#include "Cell.h"
#include <MathEngine/Box2D.h>
#include <MathEngine/Vector2.h>
#include <Building.h>
#include <Unit.h>
Cell::Cell(Vector2<f32> vectorPosition, Box2D hitboxData, i32 idx){
    position = vectorPosition;
    hitBox = hitboxData;
    index = idx;
    inhabitingBuilding = NULL;
    inhabitingUnits = std::vector<Unit*>();
    neighbors = std::vector<Cell*>();
    blocked = false;
}
Cell::~Cell(){
    inhabitingBuilding = NULL;
    inhabitingUnits.clear();
    neighbors.clear();
}
void Cell::setInhabitingBuilding(Building* buildingPtr){
    inhabitingBuilding = buildingPtr;
}
void Cell::clearInhabitingBuilding(){
    inhabitingBuilding = NULL;
}
void Cell::setInhabitingUnit(Unit* unitPtr){
    inhabitingUnits.push_back(unitPtr);
}
void Cell::clearInhabitingUnit(Unit* unitPtr){
    for(i32 i = 0; i < inhabitingUnits.size(); i++){
        if(inhabitingUnits[i] == unitPtr){
            inhabitingUnits.erase(inhabitingUnits.begin() + i);
            break;
        }
    }
}
void Cell::setNeighbor(Cell* cellPtr){
    neighbors.push_back(cellPtr);
}
void Cell::setBlocked(bool data){
    blocked = data;
}
void Cell::Clear(){
    inhabitingBuilding = NULL;
    inhabitingUnits.clear();
    neighbors.clear();
}
Box2D Cell::getHitbox(){
    return hitBox;
}
Vector2<f32> Cell::getPosition(){
    return position;
}
Building* Cell::getInhabitingBuilding(){
    return inhabitingBuilding;
}
const std::vector<Unit*>& Cell::getInhabitingUnits(){
    return inhabitingUnits;
}
const std::vector<Cell*>& Cell::getNeighbors(){
    return neighbors;
}
i32 Cell::getIndex(){
    return index;
}
bool Cell::isBlocked(){
    return blocked;
}
bool Cell::collides(Box2D& otherHitbox){
    return hitBox.isOverlappedWith(otherHitbox);
}