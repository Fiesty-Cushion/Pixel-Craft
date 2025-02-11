#include "ToolSelect.h"

#include <iostream>
#include <memory>

#include "BrushTool.h"
#include "CircleTool.h"
#include "CurveTool.h"
#include "EllipseTool.h"
#include "EraserTool.h"
#include "Globals.h"
#include "HypnotiserTool.h"
#include "LineTool.h"
#include "PencilTool.h"
#include "Rectangle.hpp"
#include "RectangleTool.h"
#include "SelectBoxTool.h"
#include "SquareTool.h"
#include "Window.hpp"
#include "raygui.h"
#include "raylib.h"

ToolSelect::ToolSelect(raylib::Window *win) : window(win) {
}

void ToolSelect::Init() {
    layout = raylib::Rectangle(0, 0, 140, GetScreenHeight());

    for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
        toolBoxes[i].x = 20 + (60 * (i % 2));
        toolBoxes[i].y = 100 + (60 * (int)(i / 2));
        toolBoxes[i].width = 40;
        toolBoxes[i].height = 40;
    }
}
raylib::Rectangle ToolSelect::ReturnIconBasedOnIndex(int n) {
    return toolBoxes[n];
}
void ToolSelect::HandleEvents() {
    for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
        if (CheckCollisionPointRec(GetMousePosition(), toolBoxes[i]) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            std::cout << "Debug: Selecting Tool - " << static_cast<Tools>(i)
                      << std::endl;
            selectTool(static_cast<Tools>(i));
        }
    }
}

void ToolSelect::Draw() {
    // Draw Side Panel
    layout.Draw(RAYWHITE);
    DrawLine(140, 0, 140, GetScreenHeight(), LIGHTGRAY);

    for (int i = 0; i < TOOL_BOX_ICONS_COUNT; i++) {
        GuiButton(toolBoxes[i], toolBoxIcons[i].c_str());

        if (selectedTool == static_cast<Tools>(i)) {
            DrawRectangleLinesEx(toolBoxes[i], 2.0f, RED);
        }
    }
}

void ToolSelect::selectTool(Tools tool) {
    std::cout << "Debug: Selecting Tool - " << tool << static_cast<Tools>(3)
              << std::endl;
    selectedTool = tool;
    switch (tool) {
        case TOOL_PENCIL:
            currentTool = std::make_unique<PencilTool>();
            break;

        case TOOL_BRUSH:
            currentTool = std::make_unique<BrushTool>();
            break;
        case TOOL_ERASER:
            currentTool = std::make_unique<EraserTool>();
            break;
        case TOOL_SQUARE:
            currentTool = std::make_unique<SquareTool>();
            break;
        case TOOL_RECTANGLE:
            currentTool = std::make_unique<RectangleTool>();
            break;
        case TOOL_CIRCLE:
            currentTool = std::make_unique<CircleTool>();
            break;
        case TOOL_CURVE:
            currentTool = std::make_unique<CurveTool>();
            break;
        case TOOL_SELECT_BOX:
            currentTool = std::make_unique<SelectBoxTool>();
            break;
        case TOOL_LINE:
            currentTool = std::make_unique<LineTool>();
            break;
        case TOOL_HYPNOTISER:
            currentTool = std::make_unique<HypnotiserTool>();
            break;
        case TOOL_ELLIPSE:
            currentTool = std::make_unique<EllipseTool>();
        case TOOL_TEXT_INPUT:
            break;
        case TOOL_FILL:
            break;
        case TOOL_EYE_DROPPER:
            break;
        case TOOL_MAGNIFIER:
            break;
        case TOOL_TRIANGLE:
            break;
    }
}

Tool *ToolSelect::getSelectedTool() {
    return currentTool.get();
}
