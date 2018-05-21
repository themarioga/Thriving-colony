#include "Window.h"

Window* Window::pinstance = 0;

Window* Window::Instance() {
    if (pinstance == 0) {
        pinstance = new Window();
    }
    return pinstance;
}

Window::Window() {
    closeWindow = false;
    
    if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(0);
	}

    // Init last delta time
    lastDeltaTime = 0.014;
}

Window::~Window() {
    //ToDo: destructor
}

void Window::Init(i32 width, i32 height) {
    windowWidth = width;
    windowHeight = height;
    screenCenter = Vector2<i32>(windowWidth/2, windowHeight/2);

    glfwSetTime(0);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create an application window with the following settings:
    window = glfwCreateWindow(windowWidth, windowHeight, "Thriving Colony", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    std::cout << "Using OpenGL version: " <<  glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR) << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << std::endl;

    glfwMakeContextCurrent(window);

    e = new OBDEngine();
	e -> Init(windowWidth, windowHeight);
	e -> InitVideoSystem();
	e -> createShaderProgram("defaultProgram", "media/shaders/vertexShader.glsl", "media/shaders/fragmentShader.glsl");
	e -> setCurrentShaderProgram("defaultProgram");
   
    // create gui manager    
    gui = new nanogui::Screen();
    gui -> initialize(window, true);

    glfwSetWindowUserPointer(window, gui);

    glfwSetCharCallback(window,
        [](GLFWwindow *w, u32 codepoint) {
            Window::Instance() -> getGUIEnvironment() -> charCallbackEvent(codepoint);
        }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *w, i32 width, i32 height) {
			Window::Instance() -> getEngine() -> setWindowSize(width, height);
            Window::Instance() -> getGUIEnvironment() -> resizeCallbackEvent(width, height);
			Window::Instance() -> windowWidth = width;
			Window::Instance() -> windowHeight = height;
    		Window::Instance() -> screenCenter.set(width/2, height/2);
			Window::Instance() -> triggerResizeCallback(width, height);
        }
    );

    dtThen = glfwGetTime();

    billboardLayer = e -> createShaderedSceneNode("billboardShader", "media/shaders/vertexShaderBillboards.glsl", "media/shaders/fragmentShaderBillboards.glsl");
	billboardProgram = e -> getRegisteredShaderProgram("billboardShader");

    videoLayer = e -> createShaderedSceneNode("videoShader", "media/shaders/vertexShaderVideo.glsl", "media/shaders/fragmentShaderVideo.glsl");
	videoProgram = e -> getRegisteredShaderProgram("videoShader");
}

void Window::setGUI() { 
    gui -> setVisible(true);
    gui -> performLayout();
}

void Window::beginScene() {
    f64 now = glfwGetTime();
    lastDeltaTime = deltaTime;
    deltaTime = (f64)(now - dtThen); // Time in seconds
    dtThen = now;
}

void Window::endScene() {
	e->draw();
    gui -> drawWidgets();
    glEnable(GL_DEPTH_TEST);
	glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::close() {
    closeWindow = true;
}

bool Window::isOpen() {
    return (!glfwWindowShouldClose(window) && !closeWindow);
}

void Window::onClose() {
    glfwTerminate();
}

OBDEngine *Window::getEngine() {
	return e;
}

void Window::setResizeCallback(std::function<void(i32, i32)> f) {
	resizeCallback = f;
}

void Window::triggerResizeCallback(i32 width, i32 height) {
	if (resizeCallback) resizeCallback(width, height);
}

nanogui::Screen* Window::getGUIEnvironment() {
    return gui;
}

i32 Window::getWindowWidth() {
    return windowWidth;
}

i32 Window::getWindowHeight() {
    return windowHeight;
}

f32 Window::getDeltaTime() const{
    return deltaTime;
}

f32 Window::getLastDeltaTime() const{
    return lastDeltaTime;
}

f32 Window::getDeltaTimeVariance() const{
    return deltaTime / 0.016f;
}

void Window::calculateFramerate() {
    framerate = floor(1.0 / deltaTime);
}

i32 Window::getFrameRate() {
    return framerate;
}

OBDShaderProgram* Window::getBillboardProgram() {
    return billboardProgram;
}

OBDSceneNode* Window::getBillboardLayer() {
    return billboardLayer;
}

OBDShaderProgram* Window::getVideoProgram(){
	return videoProgram;
}

OBDSceneNode* Window::getVideoLayer(){
	return videoLayer;
}