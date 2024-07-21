#pragma once

#include "Globals.h"
#include "Rectangle.hpp"
#include "Window.hpp"
#include <array>
#include <string>


class ToolSelect {
private:
  raylib::Window* window;
  raylib::Rectangle layout;

  std::array<std::string, TOOL_BOX_ICONS_COUNT> toolBoxIcons = {"#227#", "#31#", "#28#", "#29#", "#226#", "#42#", "#23#", "#24#", "#220#", "#224#", "#230#", "#231#", "#229#", "#232#", "#228#", "#225#"};
  raylib::Rectangle toolBoxes[TOOL_BOX_ICONS_COUNT] = {0};
  raylib::Rectangle lineIcon;

public:
  ToolSelect(raylib::Window* win);
  void Init();
  void Draw();
  void HandleEvents();
};
