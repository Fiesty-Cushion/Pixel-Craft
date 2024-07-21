#include "Globals.h"
#include "Canvas.h"
#include "RenderTexture.hpp"
#include "Window.hpp"
#include "raylib.h"


Canvas::Canvas(raylib::Window* win): window(win) {}

void Canvas::Init() {
  target = raylib::RenderTexture2D(GetScreenWidth(), GetScreenHeight());

  target.BeginMode();
  ClearBackground(RAYWHITE);
  target.EndMode();
}

void Canvas::HandleEvents() {
  // Change brush size
  brushSize += GetMouseWheelMove()*5;
  if (brushSize < 2) brushSize = 2;
  if (brushSize > 50) brushSize = 50;

}

void Canvas::Draw() {
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || (GetGestureDetected() == GESTURE_DRAG))
  { 
    // Paint circle into render texture
    // NOTE: To avoid discontinuous circles, we could store
    // previous-next mouse points and just draw a line using brush size
    target.BeginMode();
    if (mousePos.y > 50) DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorSelected]);
    target.EndMode();
  }

  // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
  DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);

  // Draw drawing circle for reference
  if (mousePos.y > 50)
  {
      if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) DrawCircleLines((int)mousePos.x, (int)mousePos.y, brushSize, GRAY);
      else DrawCircle(GetMouseX(), GetMouseY(), brushSize, colors[colorSelected]);
  } 
}

void Canvas::ShutDown() {
  target.Unload();
}
