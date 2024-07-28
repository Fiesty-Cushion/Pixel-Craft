#pragma once

#include "RenderTexture.hpp"
#include "ToolSelect.h"
#include "Window.hpp"

class Canvas
{
private:
    raylib::Window *window;
    raylib::RenderTexture2D target;

    ToolSelect *toolSelect;

public:
    Canvas(ToolSelect *ts);
    void Init();
    void Draw();
    void HandleEvents();
    void ShutDown();
};
