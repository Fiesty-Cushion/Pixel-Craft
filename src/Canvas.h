#pragma once

#include "ToolSelect.h"
#include "Window.hpp"

class Canvas {
private:
    raylib::Window *window;
    ToolSelect *toolSelect;

public:
    Canvas(ToolSelect *ts);
    void Init();
    void Draw();
    void HandleEvents();
    void ShutDown();
};
