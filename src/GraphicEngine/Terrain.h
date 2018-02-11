#ifndef TERRAIN_H
#define TERRAIN_H

#include <irrlicht.h>
#include <Types.h>
#include <IOEngine/Mouse.h>
#include <GraphicEngine/Texture.h>
#include <MathEngine/Vector3.h>

using namespace irr;

class Terrain{
    public:
        Terrain(const char* heightMap);
        ~Terrain();

        void setTexture(Texture* terrainTexture, Texture* detailTexture);

        Vector3<f32> getPointCollision(Mouse *cursor);

        scene::ITerrainSceneNode* getTerrain();

        f32 getY(f32, f32);
    private:
        scene::ITerrainSceneNode* terrain;
        scene::ITriangleSelector* selector;
        scene::ISceneCollisionManager* collisionManager;
        //scene::ISceneNode* sphere;
};

#endif