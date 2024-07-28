#pragma once
#include <iostream>
#include "stdlib.h"
#include "raylib.h"
#include "Globals.h"
#include "Tool.h"

class RectangleTool : public Tool
{
private:
  raylib::Vector2 rectSize;
  bool isMouseDraged = false;

  raylib::Vector2 startPos = {0, 0};
  raylib::Vector2 endPos = {0, 0};
  raylib::Vector2 tempMousePos;

public:
  void SetMousePos(raylib::Vector2 pos)
  {
    tempMousePos.x = pos.x;
    tempMousePos.y = pos.y;
  }
  void Draw() override
  {
    if (GetMouseY() < 50 && GetMouseX() < 140)
      return;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {

      if (startPos.x > endPos.x || startPos.y > endPos.y)
      {
        DrawRectangleLines(endPos.x, endPos.y, abs(endPos.x - startPos.x), abs(endPos.y - startPos.y), colors[colorSelected]);
      }
      else
      {
        DrawRectangleLines(startPos.x, startPos.y, abs(endPos.x - startPos.x), abs(endPos.y - startPos.y), colors[colorSelected]);
      }
    }
  }

  void HandleEvents() override
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      isMouseDraged = true;

      startPos = GetMousePosition();
    }
    if (isMouseDraged && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {

      endPos = GetMousePosition();
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      isMouseDraged = false;
    }
  }
};