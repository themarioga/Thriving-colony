#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <Types.h>
#include "SceneNode.h"
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include <OBDEngine/OBDBillboard.h>

class Billboard {
    public:
        Billboard(SceneNode* parent, Vector3<f32> pos, Vector2<f32> size, Color top, Color bot);
        ~Billboard();

        void setColor(Color top, Color bot);
        void setColor(Color totalColor);
        void setSize(glm::vec3);
        void setPosition(Vector3<f32> pos);
        void setActive(bool a);

        Vector3<f32> getPosition();
    private:
        OBDBillboard* billboard;
};

#endif