#include "Canvas.h"
#include "BrushTool.h"
#include "PencilTool.h"
#include "RenderTexture.hpp"
#include "ToolSelect.h"
#include "raylib.h"

Canvas::Canvas(ToolSelect *ts) : toolSelect(ts) {}

void Canvas::Init() {
  target = raylib::RenderTexture2D(GetScreenWidth(), GetScreenHeight());

  target.BeginMode();
  ClearBackground(RAYWHITE);
  target.EndMode();
}

void Canvas::HandleEvents() {
  if (toolSelect->getSelectedTool() == nullptr)
    return;
  toolSelect->getSelectedTool()->HandleEvents();
}

void Canvas::Draw() {
  if (toolSelect->getSelectedTool() == nullptr)
    return;

  target.BeginMode();
  toolSelect->getSelectedTool()->Draw();
  target.EndMode();

  // Render texture must be y-flipped due to default OpenGL coordinates
  DrawTextureRec(target.texture,
                 (Rectangle){0, 0, (float)target.texture.width,
                             (float)-target.texture.height},
                 (Vector2){0, 0}, WHITE);

  if (PencilTool *pencilToolPtr =
          dynamic_cast<PencilTool *>(toolSelect->getSelectedTool())) {
    if (mousePos.y > 50) {
      if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        DrawCircleLines((int)mousePos.x, (int)mousePos.y, 10.0f, GRAY);
      else
        DrawCircle(GetMouseX(), GetMouseY(), 10.0f, colors[colorSelected]);
    }
  } else if (BrushTool *brushToolPtr =
                 dynamic_cast<BrushTool *>(toolSelect->getSelectedTool())) {
    if (mousePos.y > 50) {
      if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        DrawCircleLines((int)mousePos.x, (int)mousePos.y,
                        brushToolPtr->getBrushSize(), GRAY);
      else
        DrawCircle(GetMouseX(), GetMouseY(), brushToolPtr->getBrushSize(),
                   colors[colorSelected]);
    }
  }
}

void Canvas::ShutDown() { target.Unload(); }
