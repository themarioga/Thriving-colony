#include "ScrollPanel.h"
#include <GraphicEngine/Window.h>

ScrollPanel::ScrollPanel() {
    spanel = Window::Instance() -> getGUIEnvironment() -> add<nanogui::VScrollPanel>();
}

ScrollPanel::ScrollPanel(GUIElement *parent) {
    spanel = parent -> getGUIElement() -> add<nanogui::VScrollPanel>();
}

ScrollPanel::~ScrollPanel() {
    //ToDo: borrar Label
    hide();
}

void ScrollPanel::setPosition(Vector2<int> position){
    spanel -> setPosition(Eigen::Vector2i(position.x, position.y));
}

void ScrollPanel::setTooltip(std::string t){
    spanel -> setTooltip(t);
}

void ScrollPanel::show(){
    spanel -> setVisible(true);
}
 
void ScrollPanel::hide(){
    spanel -> setVisible(false);
}

bool ScrollPanel::isVisible(){
    return spanel -> visible();
}

void ScrollPanel::setSize(Vector2<int> size) {
    spanel -> setFixedSize(Eigen::Vector2i(size.x, size.y));
}

nanogui::Widget *ScrollPanel::getGUIElement(){
    return spanel;
}