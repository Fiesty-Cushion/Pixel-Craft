#pragma once

#include "Color.hpp"
#include "RenderTexture.hpp"
#include "Vector2.hpp"

#define MAX_COLORS_COUNT 23
#define TOOL_BOX_ICONS_COUNT 16

extern raylib::RenderTexture2D target;
extern raylib::Vector2 mousePos;
extern raylib::Color colors[MAX_COLORS_COUNT];
extern int colorSelected;

long nCr(int n, int r);
