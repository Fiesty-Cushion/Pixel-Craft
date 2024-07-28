#pragma once

#include "Globals.h"
#include "Rectangle.hpp"
#include "Tool.h"
#include "Window.hpp"
#include <array>
#include <memory>
#include <string>

class ToolSelect
{
public:
  raylib::Rectangle ReturnIconBasedOnIndex(int n);
  ToolSelect(raylib::Window *win);
  void Init();
  void Draw();
  void HandleEvents();

  enum Tools
  {
    TOOL_SELECT_BOX,
    TOOL_TEXT_INPUT,
    TOOL_ERASER,
    TOOL_FILL,
    TOOL_EYE_DROPPER,
    TOOL_MAGNIFIER,
    TOOL_PENCIL,
    TOOL_BRUSH,
    TOOL_LINE,
    TOOL_CURVE,
    TOOL_SQUARE,
    TOOL_RECTANGLE,
    TOOL_CIRCLE,
    TOOL_ELLIPSE,
    TOOL_TRIANGLE,
    TOOL_COLOR_PALETTE,
  };

  void selectTool(Tools tool);
  Tool *getSelectedTool();

  float brushSize = 20.0f;

private:
  raylib::Window *window;
  raylib::Rectangle layout;

  std::array<std::string, TOOL_BOX_ICONS_COUNT> toolBoxIcons = {"#227#", "#31#", "#28#", "#29#", "#226#", "#42#", "#23#", "#24#", "#220#", "#224#", "#230#", "#231#", "#229#", "#232#", "#228#", "#225#"};
  raylib::Rectangle toolBoxes[TOOL_BOX_ICONS_COUNT] = {0};

  std::unique_ptr<Tool> currentTool;
  Tools selectedTool;
};
