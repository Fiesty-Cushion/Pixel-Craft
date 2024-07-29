#include "Canvas.h"

#include "BrushTool.h"
#include "CircleTool.h"
#include "CurveTool.h"
#include "EllipseTool.h"
#include "EraserTool.h"
#include "Globals.h"
#include "PencilTool.h"
#include "RectangleTool.h"
#include "RenderTexture.hpp"
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
        pencilToolPtr->Preview();

    } else if (BrushTool *brushToolPtr =
                   dynamic_cast<BrushTool *>(toolSelect->getSelectedTool())) {
        brushToolPtr->Preview();

    } else if (CircleTool *circleToolPtr =
                   dynamic_cast<CircleTool *>(toolSelect->getSelectedTool())) {
        circleToolPtr->Preview();

    } else if (EraserTool *eraserToolPtr =
                   dynamic_cast<EraserTool *>(toolSelect->getSelectedTool())) {
        eraserToolPtr->Preview();

    } else if (RectangleTool *rectangleToolPtr = dynamic_cast<RectangleTool *>(
                   toolSelect->getSelectedTool())) {
        rectangleToolPtr->Preview();

    } else if (CurveTool *curveToolPtr =
                   dynamic_cast<CurveTool *>(toolSelect->getSelectedTool())) {
        curveToolPtr->Preview();
    } else if (EllipseTool *ellipseTool =
                   dynamic_cast<EllipseTool *>(toolSelect->getSelectedTool())) {
        ellipseTool->Preview();
    }
}

void Canvas::ShutDown() {
    target.Unload();
}
