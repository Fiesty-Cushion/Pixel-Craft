#include "Globals.h"
#include "Rectangle.hpp"
#include "Tool.h"
#include "raylib.h"
#include "stdlib.h"

class RectangleTool : public Tool {
private:
    raylib::Vector2 rectSize;
    bool isMouseDraged = false;

    raylib::Vector2 startPos = {0, 0};
    raylib::Vector2 endPos = {0, 0};
    raylib::Vector2 tempMousePos;

public:
    raylib::Rectangle getRect() {
        return raylib::Rectangle{
            fmin(startPos.x, endPos.x), fmin(startPos.y, endPos.y),
            abs(startPos.x - endPos.x), abs(startPos.y - endPos.y)};
    };

    void Draw() override {
        if (GetMouseY() < 50 && GetMouseX() < 140)
            return;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            raylib::Rectangle rect = getRect();
            DrawRectangleLines(rect.x, rect.y, rect.width, rect.height,
                               colors[colorSelected]);
        }
    }

    void HandleEvents() override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isMouseDraged = true;
            startPos = GetMousePosition();
        }

        if (isMouseDraged && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            endPos = GetMousePosition();
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isMouseDraged = false;
        }
    }
    void Preview() override {
        DrawRectangleLines(this->getRect().x, this->getRect().y,
                           this->getRect().width, this->getRect().height,
                           colors[colorSelected]);
    }
};
