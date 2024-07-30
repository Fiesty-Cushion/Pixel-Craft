#pragma once

#include <cmath>

#include "Globals.h"
#include "Tool.h"
#include "Vector2.hpp"
#include "raylib.h"

class HypnotiserTool : public Tool {
private:
    float posX;
    float posY;
    bool isDragging = false;
    raylib::Vector2 initialPosition;
    raylib::Vector2 finalPosition;
    float radius;

public:
    void DrawCircleMid(raylib::Vector2 center, raylib::Color color) {
        posX = 0;
        posY = radius;

        float decisionParameter = 1 - radius;
        float nextDecisionParameter;
        DrawPixel(center.x + posX, center.y + posY, color);
        DrawPixel(center.x - posX, center.y + posY, color);
        DrawPixel(center.x + posX, center.y - posY, color);
        DrawPixel(center.x - posX, center.y - posY, color);
        DrawPixel(center.x + posY, center.y + posX, color);
        DrawPixel(center.x - posY, center.y + posX, color);
        DrawPixel(center.x + posY, center.y - posX, color);
        DrawPixel(center.x - posY, center.y - posX, color);
        DrawPixel(center.x, center.y + posY, color);
        while (posX < posY) {
            posX = posX + 1;
            if (decisionParameter < 0) {
                decisionParameter = decisionParameter + 2 * (posX) + 1;
            } else {
                posY = posY - 1;
                decisionParameter = decisionParameter + 2 * (posX - posY) + 1;
            }
            DrawPixel(center.x + posX, center.y + posY, color);
            DrawPixel(center.x - posX, center.y + posY, color);
            DrawPixel(center.x + posX, center.y - posY, color);
            DrawPixel(center.x - posX, center.y - posY, color);
            DrawPixel(center.x + posY, center.y + posX, color);
            DrawPixel(center.x - posY, center.y + posX, color);
            DrawPixel(center.x + posY, center.y - posX, color);
            DrawPixel(center.x - posY, center.y - posX, color);
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

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            DrawCircleMid(initialPosition, colors[colorSelected]);
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
    void Preview() override {
        this->DrawCircleMid(this->getCenter(), colors[colorSelected]);
    }
};
