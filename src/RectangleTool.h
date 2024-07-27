#pragma once
#include "raylib.h"
#include "Globals.h"
#include "Tool.h"


class RectangleTool: public Tool {
  private: 
  raylib::Vector2 rectSize ;
 bool isMouseDraged =false;

 raylib::Vector2 startPos= {0,0};
 raylib::Vector2 endPos=   {0,0};
  raylib::Vector2 tempMousePos;
public:
   void SetMousePos(raylib::Vector2 pos){
    tempMousePos.x =pos.x;
    tempMousePos.y = pos.y;
   }
  void Draw() override {

      if(isMouseDraged){
        // if(GetGestureDetected==)
        

      }



  }
    
     
 
      //   SetMousePos(mousePos);
      // // DrawRectangle(150,150,100,100,BLACK);
      // DrawText("TExtt aayo hai",150,150,12,BLACK);
      // // if(mousePos.y >50){
      //  DrawRectangleLines(tempMousePos.x,tempMousePos.y,(tempMousePos.x-GetMousePosition().x),(tempMousePos.y-GetMousePosition().y),colors[colorSelected]);
       
     
    
     
   
   

  void HandleEvents() override {
     if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      startPos = GetMousePosition();
      if(GetGestureDetected()==GESTURE_DRAG){
      isMouseDraged= true;
      endPos = GetMousePosition();
      }
      isMouseDraged= false;
     }
  }
};