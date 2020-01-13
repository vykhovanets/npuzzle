#pragma once

#include <piksel/baseapp.hpp>

class UI : public piksel::BaseApp {
public:
    UI() : piksel::BaseApp(640, 480) {}
    void setup();
    void draw(piksel::Graphics& g);
};
