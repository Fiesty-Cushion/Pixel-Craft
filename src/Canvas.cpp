#include "Canvas.h"
#include "BrushTool.h"
#include "raygui.h"
#include "Globals.h"
#include "EraserTool.h"
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
  DrawTextureRec(
      target.texture,
      {0, 0, (float)target.texture.width, -(float)target.texture.height},
      {0, 0}, WHITE);

  // If Mouse is inside the Canvas, draw appropriate Mouse Indicator
  if (mousePos.y < 50)
    return;
  if (PencilTool *pencilToolPtr =
          dynamic_cast<PencilTool *>(toolSelect->getSelectedTool())) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
      DrawCircleLines((int)mousePos.x, (int)mousePos.y, 10.0f, GRAY);
    else
      DrawCircle(GetMouseX(), GetMouseY(), 10.0f, colors[colorSelected]);
  } else if (BrushTool *brushToolPtr =
                 dynamic_cast<BrushTool *>(toolSelect->getSelectedTool())) {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
      DrawCircleLines((int)mousePos.x, (int)mousePos.y,
                      brushToolPtr->getBrushSize(), GRAY);
    else
      DrawCircle(GetMouseX(), GetMouseY(), brushToolPtr->getBrushSize(),
                 colors[colorSelected]);
  }
  else if(EraserTool* eraserToolPtr= dynamic_cast<EraserTool*>(toolSelect->getSelectedTool())){
    // GuiDrawIcon(28,(GetMousePosition().x)-250,(GetMousePosition().y)-(eraserToolPtr->GetEraserSize())/2,5,GREEN);
    DrawRectangleLinesEx({(float)GetMouseX(),(float)GetMouseY(),20,20},10.0f,RAYWHITE);
  }
}

void Canvas::ShutDown() { target.Unload(); }
