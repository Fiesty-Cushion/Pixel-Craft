#include "MainWindowGUI.h"
#include "Canvas.h"
#include "ToolSelect.h"
#include "Window.hpp"
#include "raylib.h"
#include "raygui.h"
#include "Globals.h"

void MainWindowGUI::Init() {
  const int screenWidth = 1200;
  const int screenHeight = 720;

  window = new raylib::Window(screenWidth, screenHeight, "Pixel-Craft"); 
  SetTargetFPS(120);

  GuiLoadIcons("./res/iconset.rgi", 0);
  GuiLoadStyle("./res/Bluish.rgs");
  GuiSetIconScale(2);


  colorsPanel = new ColorSelect(window); 
  toolPanel = new ToolSelect(window);
  canvas = new Canvas(window);
  
  colorsPanel->Init();
  toolPanel->Init();
  canvas->Init();
}

void MainWindowGUI::StartLoop() {
  while(!window->ShouldClose()) {
    HandleEvents();
    Draw();
  }
}

void MainWindowGUI::Draw() {
  BeginDrawing();

  {
    window->ClearBackground(RAYWHITE);
    canvas->Draw();
    colorsPanel->Draw();
    toolPanel->Draw();
  }
  EndDrawing();
}

void MainWindowGUI::HandleEvents() {
  mousePos = GetMousePosition();

  colorsPanel->HandleEvents();
  toolPanel->HandleEvents();
  canvas->HandleEvents();
}

void MainWindowGUI::ShutDown() {
  canvas->ShutDown();  
  delete window;
}
