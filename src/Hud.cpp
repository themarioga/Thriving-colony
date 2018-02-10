#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>
#include <sstream>

using namespace irr;

//warningText = 0;//new Text(Rect2D<i32>(200, 60, 50, 20), L"Edificio construido", true);

Hud::Hud() {
    updateTimer = 0.5;
    deleteTextTimer = 0;

    popUpOpen = false;
}

Hud::~Hud() {
    delete buildingsPanel;

    //Moar
    delete backgroundText;
    delete resourceText;
    delete iaResourceText;

    delete tabContainer;

    //ToDo: Es estatico asi que no se yo...
    delete warningText; 
}

void Hud::Init(){
    // Building buttons panel
    buildingsPanel = new Panel("Buildings");
    buildingsPanel->setPosition(Vector2<i32>(575, 546).getFixed());

    // General
    Panel *generalPanel = new Panel(buildingsPanel, "General functions");
    generalPanel->setPosition(Vector2<i32>(20, 640).getFixed());

    Button *buttonExpandTerrain = new Button(generalPanel, "Expand terrain");

    buttonOpenPanel = new Button(generalPanel, "Open Panel");
    buttonOpenPanel->setPosition(Vector2<i32>(100, 20));

    generalPanel -> setVerticalAlignment();

    // Resources
    Panel *resourcePanel = new Panel(buildingsPanel, "Resource buildings");
    resourcePanel->setPosition(Vector2<i32>(20, 640).getFixed());

    Button *buttonHome = new Button(resourcePanel, "House");
    Button *buttonSiderurgy = new Button(resourcePanel, "Siderurgy");
    Button *buttonQuarry = new Button(resourcePanel, "Quarry");

    resourcePanel ->setVerticalAlignment();

    // Services
    Panel *servicePanel = new Panel(buildingsPanel, "Service buildings");
    servicePanel->setPosition(Vector2<i32>(20, 640).getFixed());

    Button *buttonSchool = new Button(servicePanel, "School");
    Button *buttonMarket = new Button(servicePanel, "Market");
    Button *buttonHospital = new Button(servicePanel, "Hospital");

    servicePanel -> setVerticalAlignment();

    // Military
    Panel *militaryPanel = new Panel(buildingsPanel, "Military buildings");
    militaryPanel->setPosition(Vector2<i32>(20, 640).getFixed());

    Button *buttonBarrack = new Button(militaryPanel, "Barrack");
    Button *buttonBarn = new Button(militaryPanel, "Barn");
    Button *buttonWorkshop = new Button(militaryPanel, "Workshop");

    militaryPanel -> setVerticalAlignment();

    // Defense
    Panel *defensePanel = new Panel(buildingsPanel, "Defensive buildings");
    defensePanel->setPosition(Vector2<i32>(20, 640).getFixed());

    Button *buttonTower = new Button(defensePanel, "Tower");
    Button *buttonWall = new Button(defensePanel, "Wall");

    defensePanel -> setVerticalAlignment();

    buttonBarn->setTooltip("Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarn->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
    });

    buttonBarrack->setTooltip("Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonBarrack->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
    });

    buttonHome->setTooltip("Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHome->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
    });

    buttonHospital->setTooltip("Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonHospital->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
    });

    buttonMarket->setTooltip("Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonMarket->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
    });

    buttonQuarry->setTooltip("Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonQuarry->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
    });

    buttonSchool->setTooltip("Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSchool->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
    });

    buttonSiderurgy->setTooltip("Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonSiderurgy->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
    });

    buttonTower->setTooltip("Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonTower->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
    });

    buttonWall->setTooltip("Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWall->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
    });

    buttonWorkshop->setTooltip("Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonWorkshop->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
    });

    buttonExpandTerrain->setTooltip("Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");
    buttonExpandTerrain->setCallback([]{
        //ToDo: hacer que se expanda el terreno edificable y que el susodicho exista
    });

    buttonOpenPanel->setTooltip("Open your panel to manage your city.");

    buttonOpenPanel->setCallback([&]{
        if (!tabContainer->isVisible()){
            showPopup();
        } else {
            hidePopup();
        }
    });

    // Solo de debug
    resourceText = new Label("");
    iaResourceText = new Label("");

    warningText = new TextBox("Edificio construido");

    backgroundText = new TextBox("");
    backgroundText -> setPosition(Vector2<i32>(0,0));
    backgroundText -> setSize(Vector2<i32>(950,35));

    resourceText->setPosition(Vector2<i32>(0,0).getFixed());
    iaResourceText->setPosition(Vector2<i32>(0,20).getFixed());
    warningText->setPosition(Vector2<i32>(1000,650).getFixed());

    resourceText -> setSize(Vector2<i32>(1000,100));
    iaResourceText -> setSize(Vector2<i32>(1000,100));

    deleteWarning();
    
    tabContainer = new Panel("Building viewer");
        tabContainer -> setSize(Vector2<i32>(350, 280));
        tabContainer -> setGroupLayout();
        tabs = new TabPanel(tabContainer);
        Tab *mainBuildingTab = tabs->createTab("Main Building");
        Tab *barrackTab = tabs->createTab("Barrack");
        Tab *barnTab = tabs->createTab("Barn");
        Tab *workshopTab = tabs->createTab("Workshop");

        //MainBuildingTab
        {
            Button *b = new Button(mainBuildingTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            hallTroopList = new ComboBox(mainBuildingTab, {});

            b = new Button(mainBuildingTab, "Deploy selected troop");
            b -> setTooltip("Deploy your selected unit onto the map");
            b -> setCallback([&]{
                i32 index = hallTroopList -> getSelectedOption();
                if (index >= 0) {
                    i32 id = troopsInHallIDs . at(index);
                    Human::Instance() -> getUnitManager() -> startDeployingTroop(id);
                }
                hidePopup();
            });

            b = new Button(mainBuildingTab, "Deploy all troops");
            b -> setTooltip("Deploy all your units onto the map");
            b -> setCallback([&]{
                Human::Instance() -> getUnitManager() -> startDeployingAllTroops();
                hidePopup();
            });

            b = new Button(mainBuildingTab, "Retract all troops");
            b -> setTooltip("Retract your units back into your town hall");
            b -> setCallback([&]{
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::RetractTroopsHuman);
            });

            mainBuildingTab->hide();
        }
        //BarrackTab
        {
            Button *b = new Button(barrackTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            barrackEmpty = new Panel(barrackTab, "");
            new Label(barrackEmpty, "Este edificio no esta activo aun");

            barrackContent = new Panel(barrackTab, "");
            barrackContent -> setGroupLayout();

            b = new Button(barrackContent, "Create melee footman");
            b -> setTooltip("Create a melee unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardM);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(barrackContent, "Create ranged footman");
            b -> setTooltip("Create a ranged unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardR);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *barrackScroll = new ScrollPanel(barrackContent);
            barrackScroll -> setSize(Vector2<i32>(250, 50));
            barrackTroopQueueWidget = new Widget(barrackScroll);
            barrackTroopQueueWidget -> setSize(Vector2<i32>(250, 50));
            barrackTroopQueueWidget -> setVerticalAlignment();

            barrackContent -> hide();
        }
        //BarnTab
        {
            Button *b = new Button(barnTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            barnEmpty = new Panel(barnTab, "");
            new Label(barnEmpty, "Este edificio no esta activo aun");

            barnContent = new Panel(barnTab, "");
            barnContent -> setGroupLayout();

            b = new Button(barnContent, "Create mounted melee unit");
            b -> setTooltip("Create a melee unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedM);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(barnContent, "Create mounted ranged unit");
            b -> setTooltip("Create a ranged unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedR);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            b = new Button(barnContent, "Create monster");
            b -> setTooltip("Create a overwhelmingly powerful creature to destroy your enemies\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Idol);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *barnScroll = new ScrollPanel(barnContent);
            barnScroll -> setSize(Vector2<i32>(250, 50));
            barnTroopQueueWidget = new Widget(barnScroll);
            barnTroopQueueWidget -> setVerticalAlignment();

            barnContent -> hide();
        }
        //Workshop tab
        {
            Button *b = new Button(workshopTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            workshopEmpty = new Panel(workshopTab, "");
            new Label(workshopEmpty, "Este edificio no esta activo aun");

            workshopContent = new Panel(workshopTab, "");
            workshopContent -> setGroupLayout();

            b = new Button(workshopContent, "Create ram");
            b -> setTooltip("Create a ram that specializes in destroying buildings\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Desintegrator);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(workshopContent, "Create catapult");
            b -> setTooltip("Create a catapult that heavy area of damage\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Launcher);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *workshopScroll = new ScrollPanel(workshopContent);
            workshopScroll -> setSize(Vector2<i32>(250, 50));
            workshopTroopQueueWidget = new Widget(workshopScroll);
            workshopTroopQueueWidget -> setVerticalAlignment();

            workshopContent -> hide();
        }
        tabs->changeActiveTab(0);
    tabContainer->refreshLayout();
    tabContainer->center();
    tabContainer->hide();

    Game::Instance() -> getWindow() -> setGUI();
}

void Hud::Update() {
    f32 dt = Game::Instance()  -> getWindow() -> getDeltaTime();
    if (updateTimer <= 0) {
        i32 melees = 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        i32 ranges = 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        i32 sieges = 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream os;
        os << "Player resources: " << 
        "Metal: " << std::to_string(Human::Instance() -> getMetalAmount()) << " " <<
        "Crystal: " << std::to_string(Human::Instance() -> getCrystalAmount()) << " " <<
        "Citizens: " << std::to_string(Human::Instance() -> getCitizens()) << " " <<
        "Happiness: " << std::to_string(Human::Instance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(Human::Instance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(Human::Instance() -> getArmySize()) << " " <<
        "- Melees: " << std::to_string(melees) <<  " " <<
        "- Ranged: " << std::to_string(ranges) << " " <<
        "- Siege: " << std::to_string(sieges);
        resourceText -> setLabel(os.str());

        melees = 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        ranges = 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        sieges = 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream iaos;
        iaos << "IA resources:" << 
        "Metal: " << std::to_string(IA::Instance() -> getMetalAmount()) <<  " " <<
        "Crystal: " << std::to_string(IA::Instance() -> getCrystalAmount()) <<  " " <<
        "Citizens: " << std::to_string(IA::Instance() -> getCitizens()) <<  " " <<
        "Happiness: " << std::to_string(IA::Instance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(IA::Instance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(IA::Instance() -> getArmySize()) <<  " " <<
        " - Melees: " << std::to_string(melees) <<  " " <<
        " - Ranged: " << std::to_string(ranges) <<  " " <<
        " - Siege: " << std::to_string(sieges) <<  " " <<
        "Next choice: " << IA::Instance() -> getNextChoice() <<  " " <<
        "Behaviour: " << IA::Instance() -> getChosenBehaviour();

        iaResourceText -> setLabel(iaos.str());

        updateTimer = 0.5;

        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DisableText);
    } else {
        updateTimer -= dt;
    }
}

void Hud::enableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackEmpty->hide();
            barrackContent->show();
        break;
        case Enumeration::BuildingType::Barn:
            barnEmpty->hide();
            barnContent->show();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopEmpty->hide();
            workshopContent->show();
        break;
        default: break;
    }
    tabContainer->refreshLayout();
}

void Hud::disableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackEmpty->show();
            barrackContent->hide();
        break;
        case Enumeration::BuildingType::Barn:
            barnEmpty->show();
            barnContent->hide();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopEmpty->show();
            workshopContent->hide();
        break;
        default: break;
    }
    tabContainer->refreshLayout();
}

void Hud::showPopup(){
    tabContainer -> show();
    buttonOpenPanel -> setText("Close Panel");
    popUpOpen = true;
}

void Hud::showPopup(Enumeration::BuildingType t){
    bool show = false;
    switch(t){
        case Enumeration::BuildingType::MainBuilding:
            show = true;
            tabs -> changeActiveTab(0);
        break;
        case Enumeration::BuildingType::Barrack:
            show = true;
            tabs -> changeActiveTab(1);
        break;
        case Enumeration::BuildingType::Barn:
            show = true;
            tabs -> changeActiveTab(2);
        break;
        case Enumeration::BuildingType::Workshop:
            show = true;
            tabs -> changeActiveTab(3);
        break;
        default: break;
    }
    if (show) {
        tabContainer -> show();
        buttonOpenPanel -> setText("Close Panel");
        popUpOpen = true;
    }
}

void Hud::hidePopup(){
    tabContainer -> hide();
    buttonOpenPanel -> setText("Open Panel");
    popUpOpen = false;
}

void Hud::addTroopToHall(i32 idTroop, Enumeration::UnitType t){
    switch(t){
        case Enumeration::UnitType::StandardM:
            hallTroopList -> addOption("Melee footman");
        break;
        case Enumeration::UnitType::StandardR:
            hallTroopList -> addOption("Ranged footman");
        break;
        case Enumeration::UnitType::AdvancedM:
            hallTroopList -> addOption("Mounted melee unit");
        break;
        case Enumeration::UnitType::AdvancedR:
            hallTroopList -> addOption("Mounted ranged unit");
        break;
        case Enumeration::UnitType::Idol:
            hallTroopList -> addOption("Create idol");
        break;
        case Enumeration::UnitType::Launcher:
            hallTroopList -> addOption("Catapult");
        break;
        case Enumeration::UnitType::Desintegrator:
            hallTroopList -> addOption("Ram");
        break;
        default: break;
    }
    troopsInHallIDs . push_back(idTroop);
    Window::Instance()->getGUIEnvironment()->performLayout();
}

void Hud::removeTroopFromHall(i32 idTroop){
   std::vector<i32>::iterator it = find(troopsInHallIDs.begin(), troopsInHallIDs.end(), idTroop);
   if (it != troopsInHallIDs.end()) {
        i32 nPosition = std::distance(troopsInHallIDs.begin(), it);
        hallTroopList -> removeOption(nPosition);
        troopsInHallIDs . erase(it);
        Window::Instance()->getGUIEnvironment()->performLayout();
   }
}

void Hud::addTroopToQueue(i32 idTroop, Enumeration::UnitType t){
    switch(t){
        case Enumeration::UnitType::StandardM:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Melee footman");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::StandardR:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Ranged footman");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::AdvancedM:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Mounted melee unit");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::AdvancedR:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Mounted ranged unit");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Idol:
        {
            Widget *p = new Widget(barnTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Create idol");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Launcher:
        {
            Widget *p = new Widget(workshopTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Catapult");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Desintegrator:
        {
            Widget *p = new Widget(workshopTroopQueueWidget);
            p->setVerticalAlignment();
            new Label(p, "Ram");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        default: break;
    }
    Window::Instance()->getGUIEnvironment()->performLayout();
}

void Hud::modifyTroopFromQueue(i32 idTroop, f32 newValue){
   std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
   if (it != troopQueueProgressBars.end()) {
       it->second->setValue(newValue);
   }
    Window::Instance()->getGUIEnvironment()->performLayout();
}

void Hud::removeTroopFromQueue(i32 idTroop){
   std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
   if (it != troopQueueProgressBars.end()) {
        troopQueueProgressBars . erase(it);
   }
   std::map<i32, Widget*>::iterator it2 = troopQueueList . find(idTroop);
   if (it2 != troopQueueList.end()) {
        delete it2->second;
        troopQueueList . erase(it2);
        Window::Instance()->getGUIEnvironment()->performLayout();
   }
}

void Hud::updatePositions() {
    buttonOpenPanel -> setPosition(Vector2<i32>(100,20).getFixed());

    buildingsPanel->setPosition(Vector2<i32>(20, 640).getFixed());

    resourceText->setPosition(Vector2<i32>(1000,0).getFixed());
    iaResourceText->setPosition(Vector2<i32>(1150,0).getFixed());
    warningText->setPosition(Vector2<i32>(1000,650).getFixed());

    tabContainer->center();
}

void Hud::drawWarning() {
    //¡Se ha construido un edificio!
    warningText -> show();
}

void Hud::deleteWarning() {
    //¡Se ha borrado un texto que dice que se ha dibujado un texto!
    warningText -> hide();
}

bool Hud::getPopUpOpen() {
    return popUpOpen;
}