#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
#include "../Entity.h"
#include "../GraphicEngine/Vector2.h"
#include "../GraphicEngine/Box2D.h"
#include <irrlicht.h>
#include <vector>
#include <list>
#include <Types.h>

class CellSpacePartition;
struct Cell{
// All the entities inhabiting this cell
    std::list< Entity* > entities;
// Cell bounding box
    Box2D BBox;
// Bool block
    bool blocked = false;
// Constructor
    Cell(Vector2<f32> topLeft,
         Vector2<f32> botRight):BBox(topLeft, botRight)
    {}
// Destructor
    ~Cell();
};
class CellSpacePartition{
    private:
    // CellSpace instance
        static CellSpacePartition* pinstance;
    // Width and height
        //f32 spaceWidth;
        //f32 spaceHeight;
    // Number of cells the space is going to be divided into
        f32 cellSizeX;
        f32 cellSizeY;
    // Required number of cells
        std::vector< Cell > mCells;
    // Stores valid neighbors 
        std::vector< Entity* > mNeighbors;
    // Iterator used by methods next and begin
        std::vector< Entity* >::iterator mCurNeighbor;
    // Returns an index from a position 
        i32 positionToIndex(Vector2<f32> position);
    public:
    // Constructor
        static CellSpacePartition* Instance();
        CellSpacePartition();
    // Destructor
        ~CellSpacePartition();
    // Add entities to the proper cell
        void addEntity(Entity* ent);
    // Removes a entity from a cell
        void removeEntity(Entity* ent, Vector2<f32> position);
    // Calculate neighbors and add them in the neighbor vector
        std::vector< Entity* > calculateNeighbors(Vector2<f32> targetPos);
    // Updates a entity's cell, calling this from the entity update method
        void updateEntity(Entity* ent, Vector2<f32> oldPos);
    // Updates a cell
        void updateCell(Entity *object);
    // Clears the cells
        void clearCells();
    // Returns the correct position where the building is built
        Vector3<f32> correctPosition(Vector3<f32> targetPos, Entity *object, bool &collision);
    // Check collisions between an agent and a position
        bool checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition);
    // Checks if the cell is blocked
        bool isBlocked(Vector2<f32> targetPos);
    
};
#endif /* CELLSPACEPARTITION_H */