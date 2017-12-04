#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <GraphicEngine/Camera.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Terrain.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

class CameraController {
    
    public:
        CameraController();
        ~CameraController();

        void Update(Terrain *terrain, float deltaTime);

        void Move(InputManager *receiver, Mouse *cursor);
        void RotateAndInclinate(InputManager *receiver, Mouse *cursor);
        void Zoom(InputManager *receiver);

        Camera *getCamera();
    private:
        //Camera
        Camera *camera;
        //Camera modes
        bool movementMode;
        bool rotationOrInclinationMode;
        bool zoomMode;

        // Helpers
        float recipsqrt2;
		Vector2<float> vector0;
        Vector3<float> camPos, tarPos;

        // Camera movement variables
        int screenMarginV, screenMarginH;
        int direction;
        float camSpeed;
        Vector2<float> camIncr;

        // Camera rotation, inclination and cursor optimizacion variables
        float rotSpeed;
        float inclSpeed;
		Vector2<float> delta;
        float minInclination, maxInclination;

        int centerMargin;
        Vector2<int> cursorPosSaved;

        //Camera zoom variables
        int minZoom, maxZoom;
        float camHeight, currentHeight;

        //ToDo: Esto no va aqui
        int mapMarginLeft, mapMarginRight, mapMarginTop, mapMarginBottom; //
        Vector2<int> screenCenter; //
};
#endif