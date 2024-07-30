#include <cmath>

#include "Tool.h"
#include "Vector2.hpp"
#include "raylib.h"
#include "stdlib.h"

class LineTool : public Tool {
private:
    bool isMouseDraged = false;

    raylib::Vector2 startPos = {0, 0};
    raylib::Vector2 endPos = {0, 0};

    void drawBresenhamLine() {
        raylib::Vector2 start = startPos;
        raylib::Vector2 end = endPos;

        if (start.x > end.x) {
            start = endPos;
            end = startPos;
        }

        int dx, dy, Po;
        int xk = start.x, yk = start.y;
        dx = end.x - start.x;
        dy = end.y - start.y;

        if (dy <= dx && dy > 0) {
            // Case 1: 0 <= slope <= 1
            dx = abs(dx);
            dy = abs(dy);
            Po = (2 * dy) - dx;

            for (int k = start.x; k < end.x; k++) {
                if (Po < 0) {
                    Po = Po + (2 * dy);
                    xk++;
                } else {
                    Po = Po + (2 * dy) - (2 * dx);
                    xk++;
                    yk++;
                }
                DrawPixel(xk, yk, BLACK);
            }
        } else if (dy > dx && dy > 0) {
            // Case 2: slope > 1
            dx = abs(dx);
            dy = abs(dy);
            Po = (2 * dx) - dy;

            for (int k = start.y; k < end.y; k++) {
                if (Po < 0) {
                    Po = Po + (2 * dx);
                    yk++;
                } else {
                    Po = Po + (2 * dx) - (2 * dy);
                    xk++;
                    yk++;
                }

                DrawPixel(xk, yk, BLACK);
            }
        } else if (dy >= -dx) {
            // Case 3: -1 <= slope < 0
            dx = abs(dx);
            dy = abs(dy);
            Po = (2 * dy) - dx;

            for (int k = start.x; k < end.x; k++) {
                if (Po < 0) {
                    Po = Po + (2 * dy);
                    xk++;
                } else {
                    Po = Po + (2 * dy) - (2 * dx);
                    xk++;
                    yk--;
                }
                DrawPixel(xk, yk, BLACK);
            }
        } else if (dy < -dx) {
            // Case 4: slope < -1
            dx = abs(dx);
            dy = abs(dy);
            Po = (2 * dx) - dy;

            for (int k = start.y; k > end.y; k--) {
                if (Po < 0) {
                    Po = Po + (2 * dx);
                    yk--;
                } else {
                    Po = Po + (2 * dx) - (2 * dy);
                    xk++;
                    yk--;
                }
                DrawPixel(xk, yk, BLACK);
            }
        }
    }

public:
    void Draw() override {
        if (GetMouseY() < 50 && GetMouseX() < 140)
            return;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            drawBresenhamLine();
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
        drawBresenhamLine();
    }
};
