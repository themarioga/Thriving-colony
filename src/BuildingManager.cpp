#include "BuildingManager.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include "GraphicEngine/Window.h"

BuildingManager::BuildingManager(Enumeration::Team t, Enumeration::BreedType b) {
	team = t;
	breed = b;

	nextBuildingId = 0;
    gridAlignment =-100;
    buildingMode = false;

	buildingLayer = new SceneNode();
	currentCollision = nullptr;
	buildings = new std::map<i32, Building*>();
	tempBuilding = nullptr;

	for (i32 i = 0; i < Enumeration::BuildingType::BuildingsSize; i++){
		buildingAmounts[i] = 0;
	}
}

BuildingManager::~BuildingManager() {
	delete tempBuilding;
	delete buildingLayer;
	for (std::map<i32,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		delete it -> second;
    }
	buildings -> clear();
	delete buildings;
}

void BuildingManager::testRaycastCollisions() {
	if (!buildingMode) {
		currentCollision = buildingLayer -> getNodeCollision(IO::Instance() -> getMouse());
	}
}

bool BuildingManager::setBuildingMode(Enumeration::BuildingType type) {
	if (checkCanPay(type)) {
		if (!buildingMode) {
			buildingMode = true;
			tempBuilding = new Building(buildingLayer, 0, team, breed, type);
			recalculateHitbox(); //ToDo: quizas algo guarro pero menos que lo otro
			return true;
		}
	}
	return false;
}
/* ToDo: optimize, to much shit inside */
void BuildingManager::drawBuilding() {
    if (buildingMode && tempBuilding != nullptr) {
        // ToDo: Aqui tenemos que hacer que cuando se haya apretado el boton de nueva ventana,
        // tambien se cree una caja en las coordenadas actuales del cursor del raton.

		//Get position where the cursor is pointing to the terrain
        Vector3<f32> xyzPointCollision = Map::Instance() -> getTerrain() -> getPointCollision(IO::Instance() -> getMouse());
		Vector3<f32> f = Box3D<f32>(tempBuilding -> getModel() -> getModel() -> getTransformedBoundingBox()).getSize(); //ToDo: fachada
	// Change 2nd parameter
		bool collision = false;
		Vector3<f32> dummy2;
		Vector2<f32> dummy = WorldGeometry::Instance()->correctBuildingPosition(xyzPointCollision.toVector2(), tempBuilding);
		dummy2.x = dummy.x;
		dummy2.z = dummy.y;
		dummy2.y = Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.y);
		//irr::core::matrix4 tmat;
		//Window::Instance() -> getVideoDriver() -> setMaterial(irr::video::SMaterial());
      	//indow::Instance() -> getVideoDriver() -> setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
		//Window::Instance() -> getVideoDriver() -> draw3DLine(irr::core::vector3df(7000, -100, 7000), irr::core::vector3df(7200, 500, 8000), irr::video::SColor(255,255,0,0));
		//Window::Instance() -> getVideoDriver() -> draw3DLine(irr::core::vector3df(7005, -100, 7000), irr::core::vector3df(7205, 500, 8000), irr::video::SColor(255,255,0,0));
		//Window::Instance() -> getVideoDriver() -> draw3DLine(irr::core::vector3df(7010, -100, 7000), irr::core::vector3df(7210, 500, 8000), irr::video::SColor(255,255,0,0));
		//Window::Instance() -> getVideoDriver() -> draw3DLine(irr::core::vector3df(7015, -100, 7000), irr::core::vector3df(7215, 500, 8000), irr::video::SColor(255,255,0,0));
		//Window::Instance() -> getVideoDriver() -> draw3DLine(irr::core::vector3df(7020, -100, 7000), irr::core::vector3df(7220, 500, 8000), irr::video::SColor(255,255,0,0));
		tempBuilding -> setPosition (dummy2);
		if(team == Enumeration::Team::Human){
			Vector2<f32> tmp = Human::Instance()->getHallPosition().toVector2();
			f32 distance = std::sqrt(std::pow(tmp.x - dummy.x, 2) + std::pow(tmp.y - dummy.y, 2));
			if(Human::Instance()->getBuildingRadious() < distance){
				collision = true;
			}
			else{
				collision = WorldGeometry::Instance()->checkBuildingSpace(tempBuilding);
			}
		}
		//std::cout << "Position: " << dummy.x << "," << dummy.y << "," << dummy.z << "\n";
		//Pressing the right mouse button cancels the building
		if (IO::Instance() -> getMouse() -> rightMouseDown()){
			buildingMode = false;
			delete tempBuilding;		
			tempBuilding = nullptr;
			return;
		}
		
		if (collision) {
			tempBuilding->setColor(video::SColor(20, 255, 0, 0));
		} else {
			tempBuilding->setColor(video::SColor(20, 0, 255, 125));
			//If there is no collision and the player press left button of the mouse, build the building
			if (IO::Instance() -> getMouse() -> leftMouseDown()) {
				buildingMode = false;
				buildBuilding(dummy2, tempBuilding -> getType());
			}
		}
    }
}
 
void BuildingManager::buildBuilding(Vector3<f32> pos, Enumeration::BuildingType _type, bool instabuild) {
	if (team == Enumeration::Team::IA || tempBuilding == nullptr) {
		tempBuilding = new Building(buildingLayer, 0, team, breed, _type);
		tempBuilding -> setPosition(pos);
		//if(WorldGeometry::Instance()->checkBuildingSpace(tempBuilding)){
		//	buildingMode = false;
		//	delete tempBuilding;
		//	tempBuilding = nullptr;
		//	return;
		//	//Cell* tmp = WorldGeometry::getValidCell();
		//}
	}
	/* Establece su color original */
	tempBuilding->setColor(tempBuilding -> getBaseColor());
	/* Estable su posicion */
	tempBuilding -> setPosition(pos);
    //Establece la ID inicial del edificio
	tempBuilding -> setID(nextBuildingId);
    //Establece el color inicial del edificio
    tempBuilding -> setColor(video::SColor(255, 0, 0, 0)); //ToDo: reemplazar color por material

	tempBuilding -> setFinishedCallback([&](Building *b){
		//Tax the player when building is finished
		b->posTaxPlayer();
		b->setColor(b->getBaseColor()); //ToDo: cambiar por material

		buildingAmounts[(i32)b->getType()]++;

		//Cuando te ataquen y paren
		//returnToOriginalColor(); 
		
		if (team == Enumeration::Team::Human){
			if (buildingAmounts[(i32)b->getType()] == 1){
				switch (b->getType()){
					case Enumeration::BuildingType::Barrack:
						Hud::Instance() -> enableTab(b->getType());
					break;
					case Enumeration::BuildingType::Barn:
						Hud::Instance() -> enableTab(b->getType());
					break;
					case Enumeration::BuildingType::Workshop:
						Hud::Instance() -> enableTab(b->getType());
					break;
					default: break;
				}
			}
    		if (!instabuild) IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::showBuiltText);  
		}
	});

	buildings -> insert(std::pair<i32,Building*>(nextBuildingId, tempBuilding));
	
	// Tax the player when placing the building
	if (!instabuild) tempBuilding -> preTaxPlayer();

	if (instabuild) tempBuilding -> triggerFinishedCallback();    
	
	WorldGeometry::Instance()->build(tempBuilding);
	tempBuilding = NULL;
	nextBuildingId++;
}

//Checks if the player, either the human or the AI can afford to build a specific building 
bool BuildingManager::isSolvent(i32 metalCost, i32 crystalCost) {
	i32 metalAmt = 0;
	i32 crystalAmt = 0;
	if (team == Enumeration::Team::Human) {
		metalAmt = Human::Instance() -> getMetalAmount();
		crystalAmt = Human::Instance() -> getCrystalAmount();
	} else {
		metalAmt = IA::Instance() -> getMetalAmount();
		crystalAmt = IA::Instance() -> getCrystalAmount();
	}
	bool canPayMetal = metalAmt >= metalCost;
	bool canPayCrystal = crystalAmt >= crystalCost;
    
    return (canPayMetal && canPayCrystal);
}

/**
 * This method is responsible for managing calls to isSolvent() for the human, registering the type
 * of the desired building and sending the aforementhioned method the prices. It has its own method
 * to avoid cluttering the setBuildingMode() method, as it used to be there in the first place.
 */
bool BuildingManager::checkCanPay(Enumeration::BuildingType type) {
	//Esto esta aqui para no hacer clutter arriba
	bool canPay = false;

	//CHECK IF YOU CAN PAY THE BUILDING
	switch(type) {
        case Enumeration::BuildingType::School:
			canPay = isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost);
        break;
        case Enumeration::BuildingType::Market:
			canPay = isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost);
        break;
        case Enumeration::BuildingType::Hospital:
			canPay = isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost);
        break;
        case Enumeration::BuildingType::Siderurgy:
			canPay = isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost);
        break;
        case Enumeration::BuildingType::Quarry:
			canPay = isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost);
        break;
        case Enumeration::BuildingType::House:
			canPay = isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost);
        break;
        case Enumeration::BuildingType::Barrack:
			canPay = isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost);
        break;
        case Enumeration::BuildingType::Barn:
			canPay = isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost);
        break;
        case Enumeration::BuildingType::Workshop:
			canPay = isSolvent(Enumeration::BuildingCost::WorkshopMetalCost, Enumeration::BuildingCost::WorkshopCrystalCost);
        break;
        case Enumeration::BuildingType::Wall:
			canPay = isSolvent(Enumeration::BuildingCost::WallMetalCost, Enumeration::BuildingCost::WallCrystalCost);
        break;
        case Enumeration::BuildingType::Tower:
			canPay = isSolvent(Enumeration::BuildingCost::TowerMetalCost, Enumeration::BuildingCost::TowerCrystalCost);
        break;
		default: break;
	}
	return canPay;
}

void BuildingManager::recalculateHitbox(){
	for (std::map<i32,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		it -> second -> refreshHitbox();
	}
}

void BuildingManager::updateBuildingManager() {
	for (std::map<i32,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
		it -> second -> update();
	}
}

bool BuildingManager::checkFinished(i32 _id) {	
	return (buildings -> find(_id) -> second -> getFinished());	
}

i32 BuildingManager::getAmount(Enumeration::BuildingType t){
	return buildingAmounts[(i32)t];
}

i32 BuildingManager::getCollisionID() {
	if (currentCollision != nullptr && currentCollision -> getSceneNode() != nullptr) {
		return currentCollision -> getSceneNode() -> getID();
	}
	return -1;
}

std::string BuildingManager::getCollisionName() {
	if (currentCollision != nullptr && currentCollision -> getSceneNode() != nullptr) {
		return currentCollision -> getSceneNode() -> getName();
	}
	return nullptr;
}

std::map<i32, Building*>* BuildingManager::getBuildings() {
	return buildings;
}

SceneNode* BuildingManager::getBuildingLayer() {
	return buildingLayer;
}

void BuildingManager::deleteBuilding(i32 id) {
	if (buildings -> find(id) -> second -> getTeam() == Enumeration::Team::Human) {
		Human::Instance() -> decreaseHappiness(buildings -> find(id) -> second -> getHappiness());
	} else {
		IA::Instance() -> decreaseHappiness(buildings -> find(id) -> second -> getHappiness());
	}
	buildingAmounts[(i32)buildings -> find(id) -> second -> getType()]--;
	delete buildings -> find(id) -> second;
	buildings -> erase(id);
} 

Building *BuildingManager::getBuilding(i32 id){
  	std::map<i32,Building*>::iterator it;
	it = buildings->find(id);
  	if (it != buildings->end())
		return it->second;
	else 
		return nullptr;
}
