#include <cmath>
#include <iostream>

#include "Globals.h"
#include "Rectangle.hpp"
#include "RenderTexture.hpp"
#include "Tool.h"
#include "raylib.h"
#include "stdlib.h"

class SelectBoxTool : public Tool {
private:
    raylib::Rectangle rectSize;
    bool isMouseDraged = false;
    bool selected = false;

    raylib::Vector2 startPos = {0, 0};
    raylib::Vector2 endPos = {0, 0};

    raylib::RenderTexture2D selectedTexture;
    raylib::Rectangle selectedRect = {0, 0, 0, 0};

public:
    void drawDashedRectangle(raylib::Rectangle rect) {
        for (int i = 0; i < rect.width; i += 8) {
            for (int j = 0; j < 4; j++) {
                if (i + j < rect.width) {
                    DrawPixel(rect.x + i + j, rect.y, BLACK);
                    DrawPixel(rect.x + i + j, rect.y + rect.height - 1, BLACK);
                }
            }
        }

        for (int i = 0; i < rect.height; i += 8) {
            for (int j = 0; j < 4; j++) {
                if (i + j < rect.height) {
                    DrawPixel(rect.x, rect.y + i + j, BLACK);
                    DrawPixel(rect.x + rect.width - 1, rect.y + i + j, BLACK);
                }
            }
        }
    }

    raylib::Rectangle getRect() {
        return raylib::Rectangle(
            fmin(startPos.x, endPos.x), fmin(startPos.y, endPos.y),
            fabs(startPos.x - endPos.x), fabs(startPos.y - endPos.y));
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
            rectSize = getRect();

            if (rectSize.width > 0 && rectSize.height > 0) {
                selectedTexture =
                    raylib::RenderTexture2D(rectSize.width, rectSize.height);
                selectedTexture.BeginMode();
                ClearBackground(BLANK);
                std::cout << "Debug: Texture Size: " << rectSize.x << ", "
                          << rectSize.y << ", " << rectSize.width << ", "
                          << rectSize.height << std::endl;
                std::cout << "Debug: Mouse Position: " << mousePos.x << ", "
                          << mousePos.y << std::endl;

                DrawTextureRec(target.texture,
                               {rectSize.x, rectSize.y + rectSize.height,
                                rectSize.width, rectSize.height},
                               {0, 0}, WHITE);

                selectedTexture.EndMode();

                selected = true;
                selectedRect = (Rectangle){rectSize.x, rectSize.y,
                                           rectSize.width, rectSize.height};
                std::cout << "Debug: Render Texture: " << selectedRect.x << ", "
                          << selectedRect.y << ", " << selectedRect.width
                          << ", " << selectedRect.height << std::endl;
                target.BeginMode();
                DrawRectangleRec(rectSize, BLANK);
                target.EndMode();

                drawDashedRectangle(getRect());
            }
        }

        if (selected && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            isMouseDraged = false;
            Vector2 mousePos = GetMousePosition();
            selectedRect.x = mousePos.x - selectedRect.width / 2;
            selectedRect.y = mousePos.y - selectedRect.height / 2;
        }
    }

    void Draw() override {
        if (isMouseDraged) {
            std::cout << "Selecting" << std::endl;
            // raylib::Rectangle rect = getRect();
            // drawDashedRectangle(rect);
        }

        if (selected && IsKeyPressed(KEY_ENTER)) {
            DrawTexture(selectedTexture.texture, selectedRect.x, selectedRect.y,
                        WHITE);
        }
    }

    void Preview() {
        drawDashedRectangle(getRect());
        if (selected) {
            DrawTexture(selectedTexture.texture, selectedRect.x, selectedRect.y,
                        WHITE);
            drawDashedRectangle(getRect());
        }
    }
};
