#include "Globals.h"
#include "ColorSelect.h"
#include "Rectangle.hpp"
#include "Window.hpp"
#include "raygui.h"
#include <array>


ColorSelect::ColorSelect(raylib::Window* win): window(win) {}

void ColorSelect::Init() {
  std::array<raylib::Color, MAX_COLORS_COUNT> tempColors = {
    RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
    SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
    LIGHTGRAY, GRAY, DARKGRAY, BLACK
  };

  for (size_t i = 0; i < MAX_COLORS_COUNT; ++i) {
      colors[i] = tempColors[i];
  }

  colorSelected = 0;
  btnSaveRec = raylib::Rectangle(950, 5, 40, 40); 
  for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        colorsRecs[i].x = 210 + 30.0f*i + 2*i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }
}

void ColorSelect::HandleEvents() {
  // Move between colors with keys
    if (IsKeyPressed(KEY_RIGHT)) colorSelected++;
    else if (IsKeyPressed(KEY_LEFT)) colorSelected--;

    if (colorSelected >= MAX_COLORS_COUNT) colorSelected = MAX_COLORS_COUNT - 1;
    else if (colorSelected < 0) colorSelected = 0;

    // Choose color with mouse
    for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        if (CheckCollisionPointRec(mousePos, colorsRecs[i]))
        {
            colorMouseHover = i;
            break;
        }
        else colorMouseHover = -1;
    }

    if ((colorMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        colorSelected = colorMouseHover;
        colorSelectedPrev = colorSelected;
    }

    // Check mouse hover save button
    if (CheckCollisionPointRec(mousePos, btnSaveRec)) btnSaveMouseHover = true;
    else btnSaveMouseHover = false;

    // Image saving logic
    // NOTE: Saving painted texture to a default named image
    // if ((btnSaveMouseHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_S))
    // {
    //     raylib::Image image(target.texture);
    //     image.FlipVertical().Export("my_amazing_texture_painting.png");
    //     image.Unload();
    //     showSaveMessage = true;
    // }
    //
    // if (showSaveMessage)
    // {
    //     // On saving, show a full screen message for 2 seconds
    //     saveMessageCounter++;
    //     if (saveMessageCounter > 240)
    //     {
    //         showSaveMessage = false;
    //         saveMessageCounter = 0;
    //     }
    // }
}

void ColorSelect::Draw() {
  DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
  DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY); 

  for (int i = 0; i < MAX_COLORS_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);
  DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

  if (colorMouseHover >= 0) DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));

  DrawRectangleLinesEx((Rectangle){ colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
                       colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4 }, 2, BLACK);

  // DrawRectangleLinesEx(btnSaveRec, 2, btnSaveMouseHover ? RED : BLACK);
  // DrawText("SAVE!", 955, 20, 10, btnSaveMouseHover ? RED : BLACK);
  GuiButton(btnSaveRec, "#02#");

  if (showSaveMessage)
  {
      DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
      DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
      DrawText("IMAGE SAVED:  my_amazing_texture_painting.png", 150, 180, 20, RAYWHITE);
  }
}
