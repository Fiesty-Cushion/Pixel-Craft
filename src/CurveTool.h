#pragma once

#include <cmath>
#include <vector>

#include "Globals.h"
#include "Tool.h"
#include "Vector2.hpp"
#include "raylib.h"

class CurveTool : public Tool {
private:
    std::vector<raylib::Vector2> controlPoints;
    std::vector<raylib::Vector2> curvePoints;

    bool isEnterPressed = false;
    bool isChangingControlPoint = false;
    int changingPointIndex = -1;

    raylib::Vector2 bezierPoint(
        const std::vector<raylib::Vector2>& controlPoints, double t) {
        int n = controlPoints.size();
        raylib::Vector2 point(0, 0);

        for (int i = 0; i < n; i++) {
            double binCoeff = nCr(n - 1, i);
            double term = binCoeff * pow(1 - t, n - 1 - i) * pow(t, i);
            point.x += term * controlPoints[i].x;
            point.y += term * controlPoints[i].y;
        }

        return point;
    }

    raylib::Vector2 deCasteljau(std::vector<raylib::Vector2>& controlPoints,
                                double t) {
        if (controlPoints.size() == 1) {
            return controlPoints[0];
        }
        std::vector<raylib::Vector2> newPoints;
        for (size_t i = 0; i < controlPoints.size() - 1; ++i) {
            double x =
                (1 - t) * controlPoints[i].x + t * controlPoints[i + 1].x;
            double y =
                (1 - t) * controlPoints[i].y + t * controlPoints[i + 1].y;
            newPoints.push_back(raylib::Vector2(x, y));
        }
        return deCasteljau(newPoints, t);
    }

    std::vector<raylib::Vector2> computeBezierCurve(
        std::vector<raylib::Vector2>& controlPoints) {
        std::vector<raylib::Vector2> curvePoints;
        for (double i = 0.0; i <= 1.0; i += 0.0001) {
            curvePoints.push_back(bezierPoint(controlPoints, i));
        }
        return curvePoints;
    }

public:
    // Returns the Enter Key Press Status
    bool getEnterKeyStatus() {
        return isEnterPressed;
    }

    // Return Control Points
    std::vector<raylib::Vector2> getControlPoints() {
        return controlPoints;
    }

    // Return Curve Points
    std::vector<raylib::Vector2> getCurvePoints() {
        return curvePoints;
    }

    void Draw() override {
        // Draw the Curve to Canvas only when Enter Key is Pressed
        if (isEnterPressed) {
            for (const auto& point : curvePoints) {
                DrawPixelV(point, colors[colorSelected]);
            }

            controlPoints.clear();
            curvePoints.clear();
            isEnterPressed = false;
        }
    }

    void HandleEvents() override {
        if (mousePos.x < 140 || mousePos.y < 50)
            return;

        // Used to Change Mouse Cursor on Hover
        bool isHoveringControlPoint = false;

        // Loops over all Control Point and detects which Control Point is been
        // changed
        for (int i = 0; i < controlPoints.size(); i++) {
            auto& point = controlPoints[i];
            if (CheckCollisionPointRec(mousePos,
                                       {point.x - 4, point.y - 4, 8, 8})) {
                isHoveringControlPoint = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isChangingControlPoint = true;
                    changingPointIndex = i;
                    break;
                }
            }
        }

        // Change Mouse Cursor on Hover over Control Point
        if (isHoveringControlPoint) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        } else {
            SetMouseCursor(MOUSE_CURSOR_ARROW);
        }

        // Update Control Point to Mouse Position
        if (isChangingControlPoint && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            controlPoints[changingPointIndex] = GetMousePosition();
            curvePoints = computeBezierCurve(controlPoints);
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isChangingControlPoint = false;
            changingPointIndex = -1;
        }

        // Add Control Point on Click
        if (!isChangingControlPoint &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            controlPoints.push_back(GetMousePosition());
            curvePoints = computeBezierCurve(controlPoints);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            isEnterPressed = true;
        }
    }
};
