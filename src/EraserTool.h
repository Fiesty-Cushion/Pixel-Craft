#pragma once
#include "Globals.h"
#include "raylib.h"
#include "Tool.h"



class EraserTool: public Tool {
  private: 
 int brushSize;
public:
  EraserTool(){
    brushSize= 20.0f;
  }
int IncreaseBrushSize(){

  return brushSize*3;
}
int GetBrushSize(){
  return brushSize;
};
  void Draw() override {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (GetGestureDetected()==GESTURE_DRAG))
    if(mousePos.y>50){
      DrawCircle(mousePos.x,mousePos.y,brushSize,RAYWHITE);
    }

  }
  void HandleEvents() override {
    if(GetGestureDetected()==GESTURE_PINCH_OUT){
     IncreaseBrushSize();
      
    };
  }
};
