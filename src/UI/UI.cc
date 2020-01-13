
#include "UI.hh"

void UI::setup() {
    // load fonts and images here
}

void UI::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    g.rect(50, 50, 100, 100);
}