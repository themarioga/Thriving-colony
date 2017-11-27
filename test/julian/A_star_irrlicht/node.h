#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <irrlicht.h>
class node{
    private:
        int posX;
        int posY;
        bool visited;
        bool block;
        bool frontier;
        bool counted;
        int weight;
        int priority;
        
        node* cameFrom;
        //sf::RectangleShape *rectangle;
        irr::scene::ISceneManager *smgr;
        irr::scene::IMeshSceneNode *cube;

      public:
        node(int x, int y, irr::scene::ISceneManager *smgrData);
        node(const node& orig);
        virtual ~node();

        void swapColor(irr::video::SColor colorData);
        int getX();
        int getY();
        bool itsBlock();
        void setBlock(bool blockData);
        bool itsVisited();
        void setVisited(bool visitedData);
        bool itsFrontier();
        void setFrontier(bool frontierData);
        int getWeight();
        void setWeight(int weightData);
        bool itsCounted();
        void setCounted(bool countedData);
        node* getCameFrom();
        void setCameFrom(node* cameFromData);
        irr::scene::IMeshSceneNode *getCube();
        int getPriority();
        void setPriority(int priorityData);
};
#endif /* NODE_H */