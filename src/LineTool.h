#pragma once

#include "Globals.h"
#include "Tool.h"
#include "raylib.h"

class LineTool : public Tool {
private:
    int test = 0;
    float slope;
    bool isDragged;
    raylib::Vector2 initalPos;
    raylib::Vector2 finalPos;

public:
    // float slopeCalulator(raylib::Vector2 initalPos, raylib::Vector2 finalPos)
    // {
    //     slope = (finalPos.y - initalPos.y) / (finalPos.x - initalPos.x);
    //     return slope;
    // }
    void drawLine(raylib::Vector2 p0, raylib::Vector2 pf) {
        test++;
        float posX = p0.x;
        float posY = p0.y;
        float dy = pf.y - p0.y;
        float dx = pf.x - p0.x;

        // Handle vertical line case separately
        if (dx == 0) {
            if (dy > 0) {
                for (float y = p0.y; y <= pf.y; y++) {
                    DrawPixel(posX, y, colors[colorSelected]);
                }
            } else {
                for (float y = p0.y; y >= pf.y; y--) {
                    DrawPixel(posX, y, colors[colorSelected]);
                }
            }
            DrawText("slopeInfinite", 150 + 20 * test, 150, 10.f, BLACK);
            return;
        }

        float slope = dy / dx;
        float decisionParameter;

        DrawText("Drawing Line", 300 + 2 * test, 300 + 2 * test, 10.0f, BLACK);
        DrawPixel(posX, posY, colors[colorSelected]);

        if (abs(slope) <= 1) {
            decisionParameter = 2 * dy - dx;
            if (dx > 0) {
                while (posX < pf.x) {
                    posX++;
                    if (decisionParameter > 0) {
                        posY++;
                        decisionParameter += 2 * (dy - dx);
                    } else {
                        decisionParameter += 2 * dy;
                    }
                    DrawPixel(posX, posY, colors[colorSelected]);
                    DrawText("slopeSmaller", 100 + 2 * test, 100 + 2 * test,
                             10.0f, BLACK);
                }
            } else {
                while (posX > pf.x) {
                    posX--;
                    if (decisionParameter > 0) {
                        posY--;
                        decisionParameter += 2 * (dy - dx);
                    } else {
                        decisionParameter += 2 * dy;
                    }
                    DrawPixel(posX, posY, colors[colorSelected]);
                    DrawText("slopeSmaller", 100 + 2 * test, 100 + 2 * test,
                             10.0f, BLACK);
                }
            }
        }

        if (abs(slope) > 1) {
            decisionParameter = 2 * dx - dy;
            if (dy > 0) {
                while (posY < pf.y) {
                    posY++;
                    if (decisionParameter > 0) {
                        posX++;
                        decisionParameter += 2 * (dx - dy);
                    } else {
                        decisionParameter += 2 * dx;
                    }
                    DrawPixel(posX, posY, colors[colorSelected]);
                    DrawText("slopeBigger", 100 + 2 * test, 100 + 2 * test,
                             10.0f, BLACK);
                }
            } else {
                while (posY > pf.y) {
                    posY--;
                    if (decisionParameter > 0) {
                        posX--;
                        decisionParameter += 2 * (dx - dy);
                    } else {
                        decisionParameter += 2 * dx;
                    }
                    DrawPixel(posX, posY, colors[colorSelected]);
                    DrawText("slopeBigger", 100 + 2 * test, 100 + 2 * test,
                             10.0f, BLACK);
                }
            }
        }
    }

    void Draw() override {
        if (mousePos.y < 50) {
            return;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            if (initalPos.x > finalPos.x) {
                drawLine(finalPos, initalPos);
            } else {
                drawLine(initalPos, finalPos);
            }
        }
    }
    void HandleEvents() override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDragged = true;
            initalPos = GetMousePosition();
        }
        if (isDragged && IsMouseButtonDown(MOUSE_BUTTON_LEFT))

            finalPos = GetMousePosition();
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragged = false;
        }
    }
    void Preview() override {
        return;
    }
};
