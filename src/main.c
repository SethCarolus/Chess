#include <inttypes.h>

#include "raylib.h"
#include "board.h"
#include "renderer.h"
#include "movement.h"
#include "asset_manager.h"

#define WIDTH 850
#define HEIGHT 850

int main() {
  InitWindow(WIDTH , HEIGHT, "Chess");
  InitAudioDevice();
  loadAssets();
  Board board = createBoard();

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    displayBoard(&board);
    handleMovement(&board);
    EndDrawing();
  }
  unloadAssets();
  CloseWindow();
  return 0;
}
