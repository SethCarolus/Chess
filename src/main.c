#include <inttypes.h>
#include "raylib.h"
#include "board.h"

#define WIDTH 850
#define HEIGHT 850

int main() {
  InitWindow(WIDTH , HEIGHT, "chess");
  board_t board = createBoard();

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    displayBoard(&board);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
