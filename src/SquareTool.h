#include "Globals.h"
#include "Rectangle.hpp"
#include "Tool.h"
#include "raylib.h"
#include "stdlib.h"

class SquareTool : public Tool {
private:
    bool isMouseDraged = false;

    raylib::Vector2 startPos = {0, 0};
    raylib::Vector2 endPos = {0, 0};

public:
    raylib::Rectangle getSquare() {
        return raylib::Rectangle{
            fmin(startPos.x, endPos.x), fmin(startPos.y, endPos.y),
            abs(startPos.x - endPos.x), abs(startPos.x - endPos.x)};
    };

    void Draw() override {
        if (GetMouseY() < 50 && GetMouseX() < 140)
            return;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            raylib::Rectangle square = getSquare();
            DrawRectangleLines(square.x, square.y, square.width, square.height,
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
        DrawRectangleLines(this->getSquare().x, this->getSquare().y,
                           this->getSquare().width, this->getSquare().height,
                           colors[colorSelected]);
    }
};
