#include "Canvas.h"
#include "BrushTool.h"
#include "raygui.h"
#include "CircleTool.h"
#include "Globals.h"
#include "EraserTool.h"
#include "PencilTool.h"
#include "RenderTexture.hpp"
#include "ToolSelect.h"
#include "Vector2.hpp"
#include "raylib.h"

Canvas::Canvas(ToolSelect *ts) : toolSelect(ts) {}

void Canvas::Init()
{
  target = raylib::RenderTexture2D(GetScreenWidth(), GetScreenHeight());

  target.BeginMode();
  ClearBackground(RAYWHITE);
  target.EndMode();
}

void Canvas::HandleEvents()
{
  if (toolSelect->getSelectedTool() == nullptr)
    return;
  toolSelect->getSelectedTool()->HandleEvents();
}

void Canvas::Draw()
{
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
          dynamic_cast<PencilTool *>(toolSelect->getSelectedTool()))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
      DrawCircleLines((int)mousePos.x, (int)mousePos.y, 10.0f, GRAY);
    else
      DrawCircle(GetMouseX(), GetMouseY(), 10.0f, colors[colorSelected]);
  }
  else if (BrushTool *brushToolPtr =
               dynamic_cast<BrushTool *>(toolSelect->getSelectedTool()))
  {
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
      DrawCircleLines((int)mousePos.x, (int)mousePos.y,
                      brushToolPtr->getBrushSize(), GRAY);
    else
      DrawCircle(GetMouseX(), GetMouseY(), brushToolPtr->getBrushSize(),
                 colors[colorSelected]);
  }
  else if (CircleTool *circleToolPtr =
               dynamic_cast<CircleTool *>(toolSelect->getSelectedTool()))
  {
  //   DrawCircleLinesV(circleToolPtr->getCenter(), circleToolPtr->getRadius(), colors[colorSelected]);
  }
  else if (EraserTool *eraserTool = dynamic_cast<EraserTool *>(toolSelect->getSelectedTool()))
  {
    DrawRectangle((float)GetMouseX(), (float)GetMouseY(), (float)eraserTool->GetEraserSize(), (float)eraserTool->GetEraserSize(), WHITE);
  }
}

void Canvas::ShutDown() { target.Unload(); }
