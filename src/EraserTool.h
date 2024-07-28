#pragma once
#include "Globals.h"
#include "Tool.h"
#include "ToolSelect.h"
#include "raylib.h"

class EraserTool : public Tool {
private:
    int eraserSize;

public:
    EraserTool() {
        eraserSize = 20.0f;
    }

    int GetEraserSize() {
        return eraserSize;
    };
    void Draw() override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
            (GetGestureDetected() == GESTURE_DRAG))
            if (mousePos.y > 50) {
                // DrawCircle(mousePos.x,mousePos.y, eraserSize,RAYWHITE);
                DrawRectangle(mousePos.x, mousePos.y, eraserSize, eraserSize,
                              RAYWHITE);
            }
    }
    void HandleEvents() override {
        eraserSize += GetMouseWheelMove() * 5;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        };
    }
};
