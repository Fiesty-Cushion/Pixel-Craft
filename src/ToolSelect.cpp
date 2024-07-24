#include "ToolSelect.h"
#include "BrushTool.h"
#include "Globals.h"
#include "PencilTool.h"
#include "Rectangle.hpp"
#include "Window.hpp"
#include "raygui.h"
#include "raylib.h"
#include <iostream>
#include <memory>

ToolSelect::ToolSelect(raylib::Window *win) : window(win) {}

void ToolSelect::Init() {
  layout = raylib::Rectangle(0, 0, 140, GetScreenHeight());

  for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
    toolBoxes[i].x = 20 + (60 * (i % 2));
    toolBoxes[i].y = 100 + (60 * (int)(i / 2));
    toolBoxes[i].width = 40;
    toolBoxes[i].height = 40;
  }
}

void ToolSelect::HandleEvents() {
  for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
    if (CheckCollisionPointRec(GetMousePosition(), toolBoxes[i]) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      std::cout << "Debug: Selecting Tool - " << static_cast<Tools>(i)
                << std::endl;
      selectTool(static_cast<Tools>(i));
    }
  }
}

void ToolSelect::Draw() {
  // Draw Side Panel
  layout.Draw(RAYWHITE);
  DrawLine(140, 0, 140, GetScreenHeight(), LIGHTGRAY);

  for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
    GuiButton(toolBoxes[i], toolBoxIcons[i].c_str());

    if (selectedTool == static_cast<Tools>(i)) {
      DrawRectangleLinesEx(toolBoxes[i], 2.0f, RED);
    }
  }
}

void ToolSelect::selectTool(Tools tool) {
  selectedTool = tool;
  switch (tool) {
  case TOOL_PENCIL:
    currentTool = std::make_unique<PencilTool>();
    break;

  case TOOL_BRUSH:
    currentTool = std::make_unique<BrushTool>();
    break;
  }
}

Tool *ToolSelect::getSelectedTool() { return currentTool.get(); }
