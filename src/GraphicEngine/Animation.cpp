#include "Animation.h"
#include "Window.h"
#include <cmath>
#include "../Map.h"

using namespace irr;
#define PI 3.14159265
Animation::Animation(std::map< std::string, std::vector < std::string > > * paths) {
    currentFrame = 0;
    currentClip = 0;
    startingFrame = 0;
    finalFrame = 0;
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    scene::IMeshSceneNode* meshNode;

    frames = new std::map<std::string, std::vector<scene::IMeshSceneNode*>*>();

    // RECORRER MAPA
    for (std::map<std::string,std::vector < std::string > >::iterator it = paths -> begin(); it != paths -> end(); ++it) {
		//COSAS PARA METER AL MAPA
        std::string name = it->first;
        std::vector<scene::IMeshSceneNode*>* vector = new std::vector<scene::IMeshSceneNode*>(); 
        // RECORRER VECTOR
        for (int j = 0; j < it ->second.size(); j++) {
            const char* c = it->second.at(j) .c_str();
            std::wstringstream o;
            o << c;
            //HACER NODOS Y METERLOS EN EL VECTOR
            meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(o.str().c_str()));
            meshNode -> setVisible(false);
            if (!meshNode) {
                std::cout << "ERROR: no se puede cargar el modelo: " << c << std::endl;
                exit(0);
            }
            vector->push_back(meshNode);
        }

        // HACER SELECTOR Y METERSELO IGUAL A TODOS LOS MESHESH
        selector = smgr -> createTriangleSelectorFromBoundingBox(frames->at(0)->at(0));
        frames->at(0)->at(0)->setVisible(true);
        if (selector) {
            for (int i = 0; i < it ->second.size(); i++) {
                    vector->at(i)->setTriangleSelector(selector);
                }
            
            selector -> drop(); // We're done with this selector, so drop it now.
        }
        // METER LA PAREJA EN EL MAPA 
        frames->insert(std::pair< std::string, std::vector<scene::IMeshSceneNode*>*>(name, vector));

    }    
}

Animation::Animation(SceneNode *parent, i32 id, std::string path) {
    /*const char* c = path.c_str();
    std::wstringstream o;
    o << c;

    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    meshNode = smgr -> addMeshSceneNode(smgr -> getMesh(o.str().c_str()));
    if (!meshNode) {
        std::cout << "ERROR: no se puede cargar el modelo: " << path << std::endl;
        exit(0);
    }
    meshNode -> setID(id);

    selector = smgr -> createTriangleSelectorFromBoundingBox(meshNode);
    if (selector) {
        meshNode -> setTriangleSelector(selector);
        selector -> drop(); // We're done with this selector, so drop it now.
    }
    
    parent -> getSceneNode() -> addChild(meshNode);*/
}

Animation::~Animation() {
    //meshNode -> getParent() -> removeChild(meshNode);
}


void Animation::setPosition(Vector3<f32> pos) {
    frames->at(0)->at(0) -> setPosition(core::vector3df(pos.x, pos.y, pos.z));
    
}

void Animation::setScale(Vector3<f32> s) {
    //meshNode -> setScale(core::vector3df(s.x, s.y, s.z)); 
}

void Animation::rotate(f32 x, f32 y){
    //double param = atan(y / x) * 180 / PI;
    //if(x < 0 && y < 0)
    //    param += 180;
    //else if(x < 0)
    //    param += 90;
    //else if(y < 0)
    //    param += 270;
    //meshNode->setRotation(core::vector3df(0, param, 0));
}
void Animation::setActive(bool a) {
    //meshNode -> setVisible(a);
}

void Animation::setMaterial(Material *m){
    //meshNode->getMaterial(0) = *m->getMaterial();
}

Vector3<f32> Animation::getPosition() {
    //return Vector3<f32>(frames[currentClip][currentFrame] -> getPosition().X, frames[currentClip][currentFrame] -> getPosition().Y, frames[currentClip][currentFrame] -> getPosition().Z);
}


scene::IMeshSceneNode *Animation::getModel() {
	//return meshNode;
}

void Animation::update() {
    if (currentFrame == 0) {
        frames -> at(0) ->at(0)-> setVisible(false);
        currentFrame = 1;
    } else {
        currentFrame = 0;
    }

}


void Animation::setFrames(i32 i, i32 f) {
}