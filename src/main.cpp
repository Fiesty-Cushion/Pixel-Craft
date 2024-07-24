#define RAYGUI_IMPLEMENTATION
#include "MainWindowGUI.h"
#include "raygui.h"

int main() {
  MainWindowGUI mGUI;
  mGUI.Init();
  mGUI.StartLoop();
  mGUI.ShutDown();
  return 0;
}
