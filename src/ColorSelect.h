#pragma once

#include "Rectangle.hpp"
#include "Globals.h"
#include "Window.hpp"

class ColorSelect
{
private:
  raylib::Window *window;

  raylib::Rectangle colorsRecs[MAX_COLORS_COUNT] = {0};
  raylib::Rectangle btnSaveRec;

  int colorSelectedPrev = colorSelected;
  int colorMouseHover = 0;
  bool mouseWasPressed = false;

  bool btnSaveMouseHover = false;
  bool showSaveMessage = false;
  int saveMessageCounter = 0;

public:
  ColorSelect(raylib::Window *win);
  void Init();
  void Draw();
  void HandleEvents();
};
