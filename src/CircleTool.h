#pragma once

#include <cmath>

#include "Globals.h"
#include "Tool.h"
#include "Vector2.hpp"
#include "iostream"
#include "raylib.h"

class CircleTool : public Tool {
private:
    float posX;
    float posY;
    bool isDragging = false;
    raylib::Vector2 initialPosition;
    raylib::Vector2 finalPosition;
    float radius;

public:
    void DrawCircleMid(raylib::Vector2 center, raylib::Color color) {
        posX = GetMouseX();
        posY = GetMouseY() + radius;
        float decisionParameter = 5 / 4 - radius;
        float nextDecisionParameter;
        // DrawPixel(posX, posY, color);
        for (int i = 0; i <= 7; i++) {
            if (decisionParameter < 0) {
                posX = posX + 1;

                DrawPixel(posX, posY, color);
                DrawPixel(-posX, posY, color);
                DrawPixel(posX, -posY, color);
                DrawPixel(-posX, -posY, color);
                decisionParameter = decisionParameter + 2 * (posX) + 1;
            } else if (decisionParameter >= 0) {
                posX = posX + 1;
                posY = posY - 1;

                DrawPixel(posX, posY, color);
                DrawPixel(-posX, posY, color);
                DrawPixel(posX, -posY, color);
                DrawPixel(-posX, -posY, color);
                decisionParameter = decisionParameter + 2 * (posX)-2 * posY + 1;
            }
        }
    };

    raylib::Vector2 getCenter() {
        return initialPosition;
    }

    float getRadius() {
        return radius;
    }

    void Draw() override {
        if (GetMouseX() < 140 || GetMouseY() < 50)
            return;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            DrawCircleMid(GetMousePosition(), colors[colorSelected]);

            // DrawPixel(posX,posY,colors[colorSelected]);
            // DrawCircle(50,50,30,PINK);
            //  DrawCircleLinesV(getCenter(),
            //              finalPosition.Distance(this->initialPosition),
            //              colors[colorSelected]);
        }
    }

    void HandleEvents() override {
        if (GetMouseY() < 50 && GetMouseX() < 140)
            return;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDragging = true;
            initialPosition = GetMousePosition();
        }

        if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            finalPosition = GetMousePosition();
            radius = finalPosition.Distance(this->initialPosition);
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isDragging = false;
        }
    }
};