#pragma once
#include "Globals.h"
#include "Tool.h"
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
                DrawRectangle(mousePos.x - (float)eraserSize / 2,
                              mousePos.y - (float)eraserSize / 2, eraserSize,
                              eraserSize, RAYWHITE);
            }
    }

    void HandleEvents() override {
        eraserSize += GetMouseWheelMove() * 5;
        if (eraserSize < 20.0f)
            eraserSize = 20.0f;
        if (eraserSize > 80.0f)
            eraserSize = 80.0f;
    }
    void Preview() override {
        DrawRectangleLinesEx(
            {(float)GetMouseX() - (float)this->GetEraserSize() / 2 - 2,
             (float)GetMouseY() - (float)this->GetEraserSize() / 2 - 2,
             (float)this->GetEraserSize() + 4,
             (float)this->GetEraserSize() + 4},
            2.0f, GRAY);
        DrawRectangle((float)GetMouseX() - (float)this->GetEraserSize() / 2,
                      (float)GetMouseY() - (float)this->GetEraserSize() / 2,
                      (float)this->GetEraserSize(),
                      (float)this->GetEraserSize(), WHITE);
    }
};
