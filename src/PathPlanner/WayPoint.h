#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "../GraphicEngine/Vector2.h"
#include <Types.h>

#define INVALID_WP -1

class LWayPoint;
class NavNode{
    protected:
        i32 m_index;
        
    public:
        NavNode():m_index(INVALID_WP){}
        NavNode(i32 idx):m_index(idx){}
        ~NavNode();

    // Get / setters
        i32 getIndex();
        void setIndex(i32 newIndex);
};
class LWayPoint : public NavNode{
    protected:
        Vector2<f32> m_vPosition;
        i32 cellIndex;
    public:
        LWayPoint(Vector2<f32> position);
        virtual ~LWayPoint();
    // Get / setters
        Vector2<f32> getPosition();
        void setPosition(Vector2<f32> position);

        i32 getCellIndex();
        void setCellIndex(i32 index);
        
};
#endif /* WAYPOINT_H */