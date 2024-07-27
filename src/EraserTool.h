#pragma once
#include "Globals.h"
#include "raylib.h"
#include "ToolSelect.h"
#include "Tool.h"



class EraserTool: public Tool {
  private: 
 int  eraserSize;
 
public:

  EraserTool(){
     eraserSize= 20.0f;
  }

int GetEraserSize(){
  return  eraserSize;
};
  void Draw() override {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (GetGestureDetected()==GESTURE_DRAG))
    if(mousePos.y>50){
      // DrawCircle(mousePos.x,mousePos.y, eraserSize,RAYWHITE);
      DrawRectangle(mousePos.x,mousePos.y,eraserSize,eraserSize,RAYWHITE);
    }

  }
  void HandleEvents() override {
  eraserSize += GetMouseWheelMove() * 5;
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        

    };
    
    // if(GetGestureDetected()==GESTURE_PINCH_OUT){
    //  DrawText("hello",150,150,12,BLUE);
    //  IncreaseEraserSize();
      
   
  }
};
