#include "Canvas.h"

#include "BrushTool.h"
#include "CircleTool.h"
#include "CurveTool.h"
#include "EraserTool.h"
#include "Globals.h"
#include "PencilTool.h"
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
    if (PencilTool *pencilToolPtr =
            dynamic_cast<PencilTool *>(toolSelect->getSelectedTool())) {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            DrawCircleLines((int)mousePos.x, (int)mousePos.y, 10.0f, GRAY);
        else
            DrawCircle(GetMouseX(), GetMouseY(), 10.0f, colors[colorSelected]);
    } else if (BrushTool *brushToolPtr =
                   dynamic_cast<BrushTool *>(toolSelect->getSelectedTool())) {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            DrawCircleLines((int)mousePos.x, (int)mousePos.y,
                            brushToolPtr->getBrushSize(), GRAY);
        else
            DrawCircle(GetMouseX(), GetMouseY(), brushToolPtr->getBrushSize(),
                       colors[colorSelected]);
    } else if (CircleTool *circleToolPtr =
                   dynamic_cast<CircleTool *>(toolSelect->getSelectedTool())) {
        DrawCircleLinesV(circleToolPtr->getCenter(), circleToolPtr->getRadius(),
                         colors[colorSelected]);
    } else if (EraserTool *eraserToolPtr =
                   dynamic_cast<EraserTool *>(toolSelect->getSelectedTool())) {
        DrawRectangleLinesEx(
            {(float)GetMouseX() - (float)eraserToolPtr->GetEraserSize() / 2 - 2,
             (float)GetMouseY() - (float)eraserToolPtr->GetEraserSize() / 2 - 2,
             (float)eraserToolPtr->GetEraserSize() + 4,
             (float)eraserToolPtr->GetEraserSize() + 4},
            2.0f, GRAY);
        DrawRectangle(
            (float)GetMouseX() - (float)eraserToolPtr->GetEraserSize() / 2,
            (float)GetMouseY() - (float)eraserToolPtr->GetEraserSize() / 2,
            (float)eraserToolPtr->GetEraserSize(),
            (float)eraserToolPtr->GetEraserSize(), WHITE);
    } else if (RectangleTool *rectangleToolPtr = dynamic_cast<RectangleTool *>(
                   toolSelect->getSelectedTool())) {
        DrawRectangleLines(
            rectangleToolPtr->getRect().x, rectangleToolPtr->getRect().y,
            rectangleToolPtr->getRect().width,
            rectangleToolPtr->getRect().height, colors[colorSelected]);
    } else if (CurveTool *curveToolPtr =
                   dynamic_cast<CurveTool *>(toolSelect->getSelectedTool())) {
        if (curveToolPtr->getEnterKeyStatus())
            return;
        for (const auto &point : curveToolPtr->getControlPoints()) {
            DrawCircle(point.x, point.y, 8.0f, RED);
        }

        for (const auto &point : curveToolPtr->getCurvePoints()) {
            DrawPixelV(point, colors[colorSelected]);
        }
    } else if (SelectBoxTool *selectBoxToolPtr = dynamic_cast<SelectBoxTool *>(
                   toolSelect->getSelectedTool())) {
        selectBoxToolPtr->Preview();
    }
}

void Canvas::ShutDown() {
    target.Unload();
}
