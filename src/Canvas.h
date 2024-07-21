#pragma once

#include "RenderTexture.hpp"
#include "Window.hpp"


class Canvas {
private:
  raylib::Window* window;
  float brushSize = 20.0f;
  raylib::RenderTexture2D target;

public:
  Canvas(raylib::Window* win);
  void Init();
  void Draw();
  void HandleEvents();
  void ShutDown();
};
