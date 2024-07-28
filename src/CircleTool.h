#pragma once

#include "Globals.h"
#include "Tool.h"
#include "Vector2.hpp"
#include "raylib.h"
#include <cmath>

class CircleTool : public Tool
{
private:
  bool isDragging = false;
  raylib::Vector2 initialPosition;
  raylib::Vector2 finalPosition;
  float radius;

public:
  raylib::Vector2 getCenter() { return initialPosition; }

  float getRadius() { return radius; }

  void Draw() override
  {
    if (GetMouseX() < 140 || GetMouseY() < 50)
      return;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      // DrawCircle(50,50,30,PINK);
      DrawCircleLinesV(getCenter(),
                       finalPosition.Distance(this->initialPosition), colors[colorSelected]);
    }
  }

  void HandleEvents() override
  {
    if (GetMouseY() < 50 && GetMouseX() < 140)
      return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      isDragging = true;
      initialPosition = GetMousePosition();
    }

    if (isDragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
      finalPosition = GetMousePosition();
      radius = finalPosition.Distance(this->initialPosition);
    }
    else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
      isDragging = false;
    }
  }
};
