#pragma once

#include "Color.hpp"
#include "Image.hpp"
#include "Vector2.hpp"

#define MAX_COLORS_COUNT 23
#define TOOL_BOX_ICONS_COUNT 16

extern raylib::Vector2 mousePos; 
extern raylib::Image image;
extern raylib::Color colors[MAX_COLORS_COUNT];
extern int colorSelected;
