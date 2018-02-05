#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>
#include <sstream>

using namespace irr;

//warningText = 0;//new Text(Rect2D<int>(200, 60, 50, 20), L"Edificio construido", true);

Hud::Hud() {
    updateTimer = 0.5;
    deleteTextTimer = 0;

    buttons = new std::vector<Button*>();

    // Building buttons panel
    buildingsPanel = new Panel("Buildings");
    buildingsPanel->setPosition(Vector2<int>(575, 546).getFixed());

    // General
    generalPanel = new Panel(buildingsPanel, "General functions");
    generalPanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonExpandTerrain = new Button(generalPanel, "Expand terrain");

    buttonOpenPanel = new Button(generalPanel, "Open Panel");
    buttonOpenPanel->setPosition(Vector2<int>(100, 20));

    generalPanel -> setVerticalAlignment();

    // Resources
    resourcePanel = new Panel(buildingsPanel, "Resource buildings");
    resourcePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonHome = new Button(resourcePanel, "Home");
    buttonSiderurgy = new Button(resourcePanel, "Siderurgy");
    buttonQuarry = new Button(resourcePanel, "Quarry");

    resourcePanel ->setVerticalAlignment();

    // Services
    servicePanel = new Panel(buildingsPanel, "Service buildings");
    servicePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonSchool = new Button(servicePanel, "School");
    buttonMarket = new Button(servicePanel, "Market");
    buttonHospital = new Button(servicePanel, "Hospital");

    servicePanel -> setVerticalAlignment();

    // Military
    militaryPanel = new Panel(buildingsPanel, "Military buildings");
    militaryPanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonBarrack = new Button(militaryPanel, "Barrack");
    buttonBarn = new Button(militaryPanel, "Barn");
    buttonWorkshop = new Button(militaryPanel, "Workshop");

    militaryPanel -> setVerticalAlignment();

    // Defense
    defensePanel = new Panel(buildingsPanel, "Defensive buildings");
    defensePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonTower = new Button(defensePanel, "Tower");
    buttonWall = new Button(defensePanel, "Wall");

    defensePanel -> setVerticalAlignment();

    buttonBarn->setTooltip("Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarrack->setTooltip("Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonHome->setTooltip("Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHospital->setTooltip("Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonMarket->setTooltip("Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonQuarry->setTooltip("Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonSchool->setTooltip("Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSiderurgy->setTooltip("Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonTower->setTooltip("Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonWall->setTooltip("Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWorkshop->setTooltip("Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonExpandTerrain->setTooltip("Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");
    buttonOpenPanel->setTooltip("Open your panel to manage your city.");

    // Solo de debug
    resourceText = new Label("");
    iaResourceText = new Label("");

    warningText = new TextBox("Edificio construido");

    backgroundText = new TextBox("");
    backgroundText -> setPosition(Vector2<int>(0,0));
    backgroundText -> setSize(Vector2<int>(950,35));

    resourceText->setPosition(Vector2<int>(0,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(0,20).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

    resourceText -> setSize(Vector2<int>(1000,100));
    iaResourceText -> setSize(Vector2<int>(1000,100));

    deleteWarning();
    
    tabContainer = new Panel("Building viewer");
        tabContainer -> setSize(Vector2<int>(350, 250));
        tabContainer -> setGroupLayout();
        tabContainer -> center();
        tabs = new TabPanel(tabContainer);
        //MainBuildingTab
        {
            mainBuildingTab = tabs->createTab("Main Building", 0);

            Button *b = new Button(mainBuildingTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                tabContainer -> hide();
            });
            buttons -> push_back(b);

            hallTroopList = new ComboBox(mainBuildingTab, {});

            b = new Button(mainBuildingTab, "Deploy selected troop");
            b -> setTooltip("Deploy your selected unit onto the map");
            b -> setCallback([&]{
                int index = hallTroopList -> getSelectedOption();
                if (index >= 0) {
                    hallTroopList -> removeOption(index);
                    Human::getInstance() -> getUnitManager() -> startDeployingTroop(index);
                    Window::Instance()->getGUIEnvironment()->performLayout();
                }
            });
            buttons -> push_back(b);

            b = new Button(mainBuildingTab, "Deploy all troops");
            b -> setTooltip("Deploy all your units onto the map");
            b -> setCallback([&]{
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsHuman);
            });
            buttons -> push_back(b);

            b = new Button(mainBuildingTab, "Retract all troops");
            b -> setTooltip("Retract your units back into your town hall");
            b -> setCallback([&]{
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::RetractTroopsHuman);
            });
            buttons -> push_back(b);
        }
        //BarrackTab
        {
            barrackTab = tabs->createTab("Barrack", 1);

            Button *b = new Button(barrackTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                tabContainer -> hide();
            });
            buttons -> push_back(b);

            b = new Button(barrackTab, "Create melee footman");
            b -> setTooltip("Create a melee unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardM);
                hallTroopList -> addOption("Melee footman");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(barrackTab, "Create ranged footman");
            b -> setTooltip("Create a ranged unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardR);
                hallTroopList -> addOption("Ranged footman");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            barrackTab -> hide();
        }
        //BarnTab
        {
            barnTab = tabs->createTab("Barn", 2);

            Button *b = new Button(barnTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                tabContainer -> hide();
            });
            buttons -> push_back(b);

            b = new Button(barnTab, "Create mounted melee unit");
            b -> setTooltip("Create a melee unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedM);
                hallTroopList -> addOption("Mounted melee unit");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(barnTab, "Create mounted ranged unit");
            b -> setTooltip("Create a ranged unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedR);
                hallTroopList -> addOption("Mounted ranged unit");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);

            b = new Button(barnTab, "Create monster");
            b -> setTooltip("Create a overwhelmingly powerful creature to destroy your enemies\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Idol);
                hallTroopList -> addOption("Create monster");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            barnTab -> hide();
        }
        //Workshop tab
        {
            workshopTab = tabs->createTab("Workshop", 3);

            Button *b = new Button(workshopTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                tabContainer -> hide();
            });
            buttons -> push_back(b);

            b = new Button(workshopTab, "Create ram");
            b -> setTooltip("Create a ram that specializes in destroying buildings\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Desintegrator);
                hallTroopList -> addOption("Ram");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(workshopTab, "Create catapult");
            b -> setTooltip("Create a catapult that heavy area of damage\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Launcher);
                hallTroopList -> addOption("Catapult");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            workshopTab -> hide();
        }
        tabs->changeActiveTab(0);
    tabContainer->hide();

    setHUDEvents();
}

Hud::~Hud() {
    delete buildingsPanel;
    delete generalPanel;
    delete resourcePanel;
    delete servicePanel;
    delete militaryPanel;
    delete defensePanel;

    //Le botone iniciale
    delete buttonOpenPanel;

    //Los botones edificios
    delete buttonSchool;
    delete buttonMarket;
    delete buttonHospital;
    delete buttonSiderurgy;
    delete buttonQuarry;
    delete buttonHome;
    delete buttonBarrack;
    delete buttonBarn;
    delete buttonWorkshop;
    delete buttonWall;
    delete buttonTower;
    delete buttonExpandTerrain;

    //Moar
    delete backgroundText;
    delete resourceText;
    delete iaResourceText;

    delete hallTroopList;

    delete tabContainer;
    delete tabs;

    //ToDo: Es estatico asi que no se yo...
    delete warningText; 
}

void Hud::enableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackTab->show();
        break;
        case Enumeration::BuildingType::Barn:
            barnTab->show();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopTab->show();
        break;
        default: break;
    }
}

void Hud::disableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackTab->hide();
        break;
        case Enumeration::BuildingType::Barn:
            barnTab->hide();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopTab->hide();
        break;
        default: break;
    }
}

void Hud::showPopup(){
    tabContainer -> show();
}

void Hud::showPopup(Enumeration::BuildingType t){
    switch(t){
        case Enumeration::BuildingType::MainBuilding:
            tabs -> changeActiveTab(0);
        break;
        case Enumeration::BuildingType::Barrack:
            tabs -> changeActiveTab(1);
        break;
        case Enumeration::BuildingType::Barn:
            tabs -> changeActiveTab(2);
        break;
        case Enumeration::BuildingType::Workshop:
            tabs -> changeActiveTab(3);
        break;
        default: break;
    }
}

void Hud::hidePopup(){
    tabContainer -> hide();
}

void Hud::setHUDEvents(){
    buttonOpenPanel->setCallback([]{
        Game::Instance()->getGameState()->getHud()->showPopup();
    });

    buttonBarn->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
    });

    buttonBarrack->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
    });

    buttonHome->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
    });

    buttonHospital->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
    });

    buttonMarket->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
    });

    buttonQuarry->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
    });

    buttonSchool->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
    });

    buttonSiderurgy->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
    });

    buttonTower->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
    });

    buttonWall->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
    });

    buttonWorkshop->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
    });

    buttonExpandTerrain->setCallback([]{
        //ToDo: hacer que se expanda el terreno edificable y que el susodicho exista
    });

}

void Hud::update() {
    float dt = Game::Instance()  -> getWindow() -> getDeltaTime();
    if (updateTimer <= 0) {
        int melees = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        int ranges = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        int sieges = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream os;
        os << "Player resources: " << 
        "Metal: " << std::to_string(Human::getInstance() -> getMetalAmount()) << " " <<
        "Crystal: " << std::to_string(Human::getInstance() -> getCrystalAmount()) << " " <<
        "Citizens: " << std::to_string(Human::getInstance() -> getCitizens()) << " " <<
        "Happiness: " << std::to_string(Human::getInstance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(Human::getInstance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(Human::getInstance() -> getArmySize()) << " " <<
        "- Melees: " << std::to_string(melees) <<  " " <<
        "- Ranged: " << std::to_string(ranges) << " " <<
        "- Siege: " << std::to_string(sieges);
        resourceText -> setLabel(os.str());

        melees = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        ranges = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        sieges = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream iaos;
        iaos << "IA resources:" << 
        "Metal: " << std::to_string(IA::getInstance() -> getMetalAmount()) <<  " " <<
        "Crystal: " << std::to_string(IA::getInstance() -> getCrystalAmount()) <<  " " <<
        "Citizens: " << std::to_string(IA::getInstance() -> getCitizens()) <<  " " <<
        "Happiness: " << std::to_string(IA::getInstance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(IA::getInstance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(IA::getInstance() -> getArmySize()) <<  " " <<
        " - Melees: " << std::to_string(melees) <<  " " <<
        " - Ranged: " << std::to_string(ranges) <<  " " <<
        " - Siege: " << std::to_string(sieges) <<  " " <<
        "Next choice: " << IA::getInstance() -> getNextChoice() <<  " " <<
        "Behaviour: " << IA::getInstance() -> getChosenBehaviour();

        iaResourceText -> setLabel(iaos.str());

        updateTimer = 0.5;

        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DisableText);
    } else {
        updateTimer -= dt;
    }
}


void Hud::updatePositions() {
    buttonOpenPanel -> setPosition(Vector2<int>(100,20).getFixed());

    buildingsPanel->setPosition(Vector2<int>(20, 640).getFixed());

    resourceText->setPosition(Vector2<int>(1000,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(1150,0).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

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

/*hospitalMenu = tabs -> addTab(L"Hospital", Enumeration::BuildingType::Hospital);
hospitalMenu -> addChild(buttonCloseTab3);
homeMenu = tabs -> addTab(L"Home", Enumeration::BuildingType::House);
homeMenu -> addChild(buttonCloseTab4);
marketMenu = tabs -> addTab(L"Market", Enumeration::BuildingType::Market);
marketMenu -> addChild(buttonCloseTab5);
quarryMenu = tabs -> addTab(L"Quarry", Enumeration::BuildingType::Quarry);
quarryMenu -> addChild(buttonCloseTab6);
siderurgyMenu = tabs -> addTab(L"Siderurgy", Enumeration::BuildingType::Siderurgy);
siderurgyMenu -> addChild(buttonCloseTab7);
schoolMenu = tabs -> addTab(L"School", Enumeration::BuildingType::School);
schoolMenu -> addChild(buttonCloseTab8);
towerMenu = tabs -> addTab(L"Tower", Enumeration::BuildingType::Tower);
towerMenu -> addChild(buttonCloseTab9);
wallMenu = tabs -> addTab(L"Wall", Enumeration::BuildingType::Wall); 
wallMenu -> addChild(buttonCloseTab10);
buttonCloseTab3 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab4 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab5 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab6 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab7 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab8 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab9 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab10 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab11 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
*/


    /*Game *g = Game::Instance();
    int id = g -> getIO() -> getGUIClickedID();

    switch(id) {
        //Los botones de cada tab
        case Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardM;
                
                //unitData.unitClass = Enumeration::UnitType::Class::Melee;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa melee a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa rango a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedM;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa melee en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa rango en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Ente");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Launcher;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Maquina de guerra 1");
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON:
            {
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_ALL_TROOPS_BUTTON:
            {
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsHuman);
                hallTroopList -> removeAllItems();
            }
        break;
        case Enumeration::idGUI::GUI_ID_RETRACT_ALL_TROOPS_BUTTON:
            {
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::RetractTroopsHuman);
            }
        break;
    }*/