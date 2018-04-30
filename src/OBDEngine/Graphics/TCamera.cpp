#include "TCamera.h"

TCamera::TCamera(OBDEnums::CameraProjection projectionMode, f32 n, f32 f, f32 t, f32 b, f32 l, f32 r) : TEntity(){
    setNear(n);
    setFar(f);
    
    setTop(t);
    setBottom(b);
    setLeft(l);
    setRight(r);

    setProjection(projectionMode);

    calculateViewMatrix();

    beginDraw();
}

TCamera::~TCamera(){

}

void TCamera::beginDraw(){
    cache.setProjectionMatrix(pMat);
    cache.setViewMatrix(vMat);
}

void TCamera::endDraw(){

}

void TCamera::calculateViewMatrix() {
    vMat = glm::lookAt(
        cameraPosition,  
        targetPosition, 
        glm::vec3(0,1,0) 
    );
}

void TCamera::setTargetPosition(glm::vec3 p) {
    targetPosition = p;
    calculateViewMatrix();
}

glm::vec3 TCamera::getTargetPosition() {
    return targetPosition;
}

void TCamera::setCameraPosition(glm::vec3 p) {
    cameraPosition = p;
    calculateViewMatrix();
}

glm::vec3 TCamera::getCameraPosition() {
    return cameraPosition;
}

glm::vec3 TCamera::getWorldCoordinatesFromScreen(glm::vec3 world){
    return glm::unProject(world, vMat, pMat, glm::vec4(0.0f, 0.0f, float(bottom), float(right)));
}

glm::vec3 TCamera::getScreenCoordinatesFromWorld(glm::vec3 screen){
    screen.y = bottom - screen.y; //Invert y
    return glm::project(screen, vMat, pMat, glm::vec4(0.0f, 0.0f, float(bottom), float(right)));
}

void TCamera::setProjection(OBDEnums::CameraProjection cp){
    projection = cp;
    if (cp == OBDEnums::CameraProjection::ProjectionPerspective){
        // Calculate aspect ratio
        f32 width = right - left;
        f32 height = bottom - top;
        //ToDo: revisar parametro FOV
        pMat = glm::perspective(/*fov*/glm::radians(45.0f), width / height, near, far);
    } else {
        pMat = glm::ortho(left, right, bottom, top, near, far);
    }
}

OBDEnums::CameraProjection TCamera::getProjection(){
    return projection;
}

void TCamera::setFov(f32 f) {
    fov = f;
}

f32 TCamera::getFov() {
    return fov;
}

void TCamera::setNear(f32 n){
    near = n;
}

f32 TCamera::getNear(){
    return near;
}

void TCamera::setFar(f32 f){
    far = f;
}

f32 TCamera::getFar(){
    return far;
}

void TCamera::setTop(f32 t){
    top = t;
}

f32 TCamera::getTop(){
    return top;
}

void TCamera::setBottom(f32 b){
    bottom = b;
}

f32 TCamera::getBottom(){
    return bottom;
}

void TCamera::setLeft(f32 l){
    left = l;
}

f32 TCamera::getLeft(){
    return left;
}

void TCamera::setRight(f32 r){
    right = r;
}

f32 TCamera::getRight(){
    return right;
}