#pragma once

#include "Globals.h"
#include "Tool.h"
#include "raylib.h"

class PencilTool : public Tool {
public:
  void Draw() override {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) ||
        (GetGestureDetected() == GESTURE_DRAG)) {
      if (mousePos.y > 50)
        DrawCircle((int)mousePos.x, (int)mousePos.y, 10.0f,
                   colors[colorSelected]);
    }
  }

  void HandleEvents() override { return; };
};
