#include <irrlicht.h>

using namespace irr;
using namespace std;

int main() {
	// create device with full flexibility over creation parameters
	// you can add more parameters if desired, check irr::SIrrlichtCreationParameters
	irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.WindowSize=core::dimension2d<u32>(640, 480);
	IrrlichtDevice* device = createDeviceEx(params);

	if (device == 0) return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	// add camera
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);

	camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
	camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
	camera->setFarValue(42000.0f);

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

    //Draw terrain
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"terrain-heightmap.bmp",
		0,					// parent node
		-1,					// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
	);

	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0, driver->getTexture("terrain-texture.jpg"));
	terrain->setMaterialTexture(1, driver->getTexture("detailmap3.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f, 20.0f);

	int lastFPS = -1;

	while(device->run()) {
        if (device->isWindowActive()) {
            driver->beginScene(true, true, 0 );

            smgr->drawAll();
            env->drawAll();

            driver->endScene();

            // display frames per second in window title
            int fps = driver->getFPS();
            if (lastFPS != fps) {
                core::stringw str = L"Terrain Renderer - Irrlicht Engine [";
                str += driver->getName();
                str += "] FPS:";
                str += fps;
                // Also print terrain height of current camera position
                // We can use camera position because terrain is located at coordinate origin
                str += " Height: ";
                str += terrain->getHeight(camera->getAbsolutePosition().X,
                        camera->getAbsolutePosition().Z);

                device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
        }
    }

	device->drop();
	
	return 0;
}