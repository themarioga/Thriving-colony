#include "Window.h"

using namespace irr;

Window* Window::pinstance = 0;

Window* Window::Instance(){
    
    if(pinstance == 0){
        pinstance = new Window(1280, 720);
    }
    
    return pinstance;
}

Window::Window(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(width, height);
    //params.EventReceiver=Game::Instance()->get;
    device = createDeviceEx(params);
    
    if (device == 0) exit(0); 

	// disable mouse cursor
	device->getCursorControl()->setVisible(true);

	driver = device->getVideoDriver();
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	scene = device->getSceneManager();
	gui = device->getGUIEnvironment();

    dtThen = device->getTimer()->getTime();
}

Window::~Window() {
    delete device;
    device = NULL; 
}

void Window::setEventReceiver(IEventReceiver *receiver){
    device->setEventReceiver(receiver);
}
 
void Window::beginScene(){
    float now = device->getTimer()->getTime();
    deltaTime = (float)(now - dtThen) / 1000.f; // Time in seconds
    dtThen = now;

    driver->beginScene(true, true, 0 );
}

void Window::endScene(){
    scene->drawAll();
    gui->drawAll();

    driver->endScene();
}

bool Window::isOpen(){
    return device->run();
}

bool Window::isReady(){
    return device->isWindowActive();
}

void Window::close(){
    device->drop();
}

IrrlichtDevice* Window::getDevice() {
    return device;
}

video::IVideoDriver* Window::getVideoDriver(){
    return driver;
}

scene::ISceneManager* Window::getSceneManager(){
    return scene;
}

gui::IGUIEnvironment* Window::getGUIEnvironment(){
    return gui;
}

int Window::getScreenWidth(){
    return screenWidth;
}

int Window::getScreenHeight(){
    return screenHeight;
}

float Window::getDeltaTime(){
    return deltaTime;
}