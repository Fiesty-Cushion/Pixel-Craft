#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "MainWindowGUI.h"

int main()
{
  MainWindowGUI mGUI;
  mGUI.Init();
  mGUI.StartLoop();
  mGUI.ShutDown();
  return 0;
}
