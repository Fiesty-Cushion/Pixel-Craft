#pragma once
#include "raylib.h"
#include "Globals.h"
#include "Tool.h"


class RectangleTool: public Tool {
public:
  void Draw() override {
     if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || GetGestureDetected()==GESTURE_DRAG)
     {
      if(mousePos.y >50){
      DrawRectangle(mousePos.x,mousePos.y, (mousePos.x- GetMousePosition().x),(mousePos.y- GetMousePosition().y),colors[colorSelected]);
       
     }
     
      } }
 
  void HandleEvents() override {
    return;
  }
};