#pragma once

#include "Canvas.h"
#include "ColorSelect.h"
#include "ToolSelect.h"
#include "Window.hpp"

class MainWindowGUI {
private:
    raylib::Window *window;
    ColorSelect *colorsPanel;
    ToolSelect *toolSelect;
    Canvas *canvas;

public:
    void Init();
    void StartLoop();
    void Draw();
    void HandleEvents();
    void ShutDown();
};
