#include <inttypes.h>

#include "raylib.h"
#include "board.h"
#include "renderer.h"
#include "movement.h"

#define WIDTH 850
#define HEIGHT 850

int main() {
  InitWindow(WIDTH , HEIGHT, "Chess");
  InitAudioDevice();
  Board board = createBoard();

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    displayBoard(&board);
    handleMovement(&board);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
