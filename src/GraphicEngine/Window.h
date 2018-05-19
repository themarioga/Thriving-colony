#ifndef WINDOW_H
#define WINDOW_H

#include <irrlicht/irrlicht.h>
#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>

#include <Types.h>
#include <MathEngine/Vector2.h>

using namespace irr;

class Window {
    public:
        static Window* Instance();

		void Init(i32, i32);

        void setEventReceiver(IEventReceiver *receiver);
        void handleGUIEvents();

        void setGUI();

        void beginScene();
        void endScene(bool b);

        void close();

        bool isOpen();
        
        void onClose();

		void setResizeCallback(std::function<void()>);

		void triggerResizeCallback();

        IrrlichtDevice* getDevice();
        video::IVideoDriver* getVideoDriver();
        scene::ISceneManager* getSceneManager();
        nanogui::Screen* getGUIEnvironment();

        i32 getWindowWidth();
        i32 getWindowHeight();

        f32 getDeltaTime() const;
        f32 getLastDeltaTime() const;
        f32 getDeltaTimeVariance() const;
        
        GLFWwindow *getWindow() {
            return window;
        }

        /**
         * @brief calculates the framerate of the window. It is important to call
         * this function after the game logic has fully executed to see how long it
         * took to get through it, otherwise results won't be correct.
         * 
         */
        void calculateFramerate();

        /**
         * @brief returns the current framerate
         * 
         * @return i32 framerate
         */
        i32 getFrameRate();
        
        i32 windowWidth;
        i32 windowHeight;
    protected:
        Window();
        virtual ~Window();
        Window(const Window & );
        Window &operator = (const Window & );
    private:
        void setGLAttributes();
		
        static Window* pinstance;

        GLFWwindow* window;

        bool closeWindow;

        IrrlichtDevice* device;
        video::IVideoDriver* driver;
        scene::ISceneManager* scene;
        nanogui::Screen* gui;
        
        double dtThen;
        double deltaTime;
        double lastDeltaTime;

        i32 framerate;

		std::function<void()> resizeCallback;
};

#endif