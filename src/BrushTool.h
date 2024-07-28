#pragma once

#include "Globals.h"
#include "Tool.h"
#include "raylib.h"

class BrushTool : public Tool
{
private:
    float brushSize = 20.0f;

public:
    void Draw() override {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) ||
            (GetGestureDetected() == GESTURE_DRAG)) {
            if (mousePos.y > 50)
                DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize,
                           colors[colorSelected]);
        }
    }

    void HandleEvents() override {
        // Change brush size
        brushSize += GetMouseWheelMove() * 5;
        if (brushSize < 2)
            brushSize = 2;
        if (brushSize > 50)
            brushSize = 50;
    };

    float getBrushSize() {
        return this->brushSize;
    }
};
