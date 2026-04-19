#include "raylib.h"

int main() {
  InitWindow(800, 800, "Chess");
  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
