#include "ToolSelect.h"
#include "Globals.h"
#include "Rectangle.hpp"
#include "Window.hpp"
#include "raylib.h"
#include "raygui.h"


ToolSelect::ToolSelect(raylib::Window* win): window(win) {}

void ToolSelect::Init() {
  layout = raylib::Rectangle(0, 0, 140, GetScreenHeight());
  
  lineIcon = raylib::Rectangle(10, 50, 40, 40);
  for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
    toolBoxes[i].x = 20 + (60 * (i%2));
    toolBoxes[i].y = 100 + (60 * (int)(i/2));
    toolBoxes[i].width = 40;
    toolBoxes[i].height = 40;
  }
}

void ToolSelect::HandleEvents() {

}

void ToolSelect::Draw() {
  // Draw Side Panel
  layout.Draw(RAYWHITE); 
  DrawLine(140, 0, 140, GetScreenHeight(), LIGHTGRAY);

  for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
    GuiButton(toolBoxes[i], toolBoxIcons[i].c_str()); 
  }
}
