#pragma once

#include "Globals.h"
#include "Tool.h"
#include "raylib.h"

class EllipseTool : public Tool {
private:
    bool isDragging;
    raylib::Vector2 initalPos;
    raylib::Vector2 finalPos;

public:
    void drawEllipse(int xc, int yc, int rx, int ry) {
        int rx2 = rx * rx;
        int ry2 = ry * ry;
        int twoRx2 = 2 * rx2;
        int twoRy2 = 2 * ry2;

        int x = 0;
        int y = ry;
        int px = 0;
        int py = twoRx2 * y;

        // Region 1
        int p1 = ry2 - (rx2 * ry) + (0.25 * rx2);
        while (px < py) {
            x++;
            px += twoRy2;
            if (p1 < 0) {
                p1 += ry2 + px;
            } else {
                y--;
                py -= twoRx2;
                p1 += ry2 + px - py;
            }
            DrawPixel(xc + x, yc + y, colors[colorSelected]);
            DrawPixel(xc - x, yc + y, colors[colorSelected]);
            DrawPixel(xc + x, yc - y, colors[colorSelected]);
            DrawPixel(xc - x, yc - y, colors[colorSelected]);
        }

        // Region 2
        int p2 = (ry2 * (x + 0.5) * (x + 0.5)) + (rx2 * (y - 1) * (y - 1)) -
                 (rx2 * ry2);
        while (y > 0) {
            y--;
            py -= twoRx2;
            if (p2 > 0) {
                p2 += rx2 - py;
            } else {
                x++;
                px += twoRy2;
                p2 += rx2 - py + px;
            }
            DrawPixel(xc + x, yc + y, colors[colorSelected]);
            DrawPixel(xc - x, yc + y, colors[colorSelected]);
            DrawPixel(xc + x, yc - y, colors[colorSelected]);
            DrawPixel(xc - x, yc - y, colors[colorSelected]);
        }
    }

    void Draw() override {
        if (mousePos.y < 50) {
            return;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            int xc = (initalPos.x + finalPos.x) / 2;
            int yc = (initalPos.y + finalPos.y) / 2;
            int rx = abs(finalPos.x - initalPos.x) / 2;
            int ry = abs(finalPos.y - initalPos.y) / 2;
            drawEllipse(xc, yc, rx, ry);
        }
    }

    void
     HandleEvents() override {
        if (GetMouseY() < 50 && GetMouseX() < 140)
            return;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDragging = true;
            initalPos = GetMousePosition();
        }


        if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            finalPos = GetMousePosition();
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;
        }
    }
    void Preview() override {
        drawEllipse((initalPos.x + finalPos.x) / 2,
                    (initalPos.y + finalPos.y) / 2,
                    abs(finalPos.x - initalPos.x) / 2,
                    abs(finalPos.y - initalPos.y) / 2);
    }
};
