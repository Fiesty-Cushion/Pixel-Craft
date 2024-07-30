#include "Canvas.h"

#include "Globals.h"
#include "RectangleTool.h"
#include "RenderTexture.hpp"
#include "SelectBoxTool.h"
#include "ToolSelect.h"
#include "Vector2.hpp"
#include "raygui.h"
#include "raylib.h"

Canvas::Canvas(ToolSelect *ts) : toolSelect(ts) {
}

void Canvas::Init() {
    target = raylib::RenderTexture2D(GetScreenWidth(), GetScreenHeight());

    target.BeginMode();
    ClearBackground(RAYWHITE);
    target.EndMode();
}

void Canvas::HandleEvents() {
    if (toolSelect->getSelectedTool() == nullptr)
        return;
    toolSelect->getSelectedTool()->HandleEvents();
}

void Canvas::Draw() {
    if (toolSelect->getSelectedTool() == nullptr)
        return;

    target.BeginMode();
    toolSelect->getSelectedTool()->Draw();
    target.EndMode();

    // Render texture must be y-flipped due to default OpenGL coordinates
    DrawTextureRec(
        target.texture,
        {0, 0, (float)target.texture.width, -(float)target.texture.height},
        {0, 0}, WHITE);

    // If Mouse is inside the Canvas, draw appropriate Mouse Indicator
    if (mousePos.y < 50)
        return;

    // Draw UI Preview for Tool
    toolSelect->getSelectedTool()->Preview();
}

void Canvas::ShutDown() {
    target.Unload();
}
