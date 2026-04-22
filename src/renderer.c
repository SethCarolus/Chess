#include "renderer.h"

void displayBoard(Board* board) {
  if (board == NULL) {
    return;
  }
  DrawTexture(board->texture, 0, 0, WHITE);
  for (size_t i = 0; i < board_rows; i++) {
    for (size_t j = 0; j < board_columns; j++) {
      if (i == board->selectedRow && j == board->selectedColumn) {
        DrawRectangle(j * GetScreenWidth() / board_rows,i * GetScreenHeight() / board_columns, GetScreenWidth() / board_columns,GetScreenHeight() / board_rows, ColorFromHSV(0, 0, 0.2));
      }
      DrawTexture(board->data[i][j].texture,j * GetScreenWidth() / board_rows,i * GetScreenHeight() / board_columns, WHITE);
    }
  }
}
