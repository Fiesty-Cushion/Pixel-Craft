#include "MainWindowGUI.h"

#include "Canvas.h"
#include "Globals.h"
#include "ToolSelect.h"
#include "Window.hpp"
#include "raygui.h"
#include "raylib.h"

void MainWindowGUI::Init() {
    const int screenWidth = 1200;
    const int screenHeight = 720;

    window = new raylib::Window(screenWidth, screenHeight, "Pixel-Craft");
    SetTargetFPS(120);

    GuiLoadIcons("./res/iconset.rgi", 0);
    GuiLoadStyle("./res/Bluish.rgs");
    GuiSetIconScale(2);

    colorsPanel = new ColorSelect(window);
    toolSelect = new ToolSelect(window);
    canvas = new Canvas(toolSelect);

    colorsPanel->Init();
    toolSelect->Init();
    canvas->Init();
}

void MainWindowGUI::StartLoop() {
    while (!window->ShouldClose()) {
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
        toolSelect->Draw();
    }
    EndDrawing();
}

void MainWindowGUI::HandleEvents() {
    mousePos = GetMousePosition();

    canvas->HandleEvents();
    colorsPanel->HandleEvents();
    toolSelect->HandleEvents();
}

void MainWindowGUI::ShutDown() {
    canvas->ShutDown();
    delete window;
}
