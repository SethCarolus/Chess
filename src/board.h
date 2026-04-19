#pragma once

#include "piece.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>


typedef struct board {
  piece_t data[board_rows][board_columns];
  Texture texture;
  int selectedColumn;
  int selectedRow;
  bool isWhiteTurn;
} board_t;

board_t createBoard() {
  board_t board;

  Image boardImg = LoadImage("../resources/boards-png/rect-8x8.png");
  ImageResize(&boardImg, GetScreenWidth(), GetScreenHeight());
  board.texture = LoadTextureFromImage(boardImg);
  UnloadImage(boardImg);

  for (size_t i = 0; i < board_rows; i++) {
    for (size_t j = 0; j < board_columns; j++) {
      board.data[i][j] = createPiece(PC_BLACK, PT_VOID);
    }
  }

  board.data[0][0] = createPiece(PC_BLACK, PT_ROOK);
  board.data[0][1] = createPiece(PC_BLACK, PT_KNIGHT);
  board.data[0][2] = createPiece(PC_BLACK, PT_BISHOP);
  board.data[0][3] = createPiece(PC_BLACK, PT_QUEEN);
  board.data[0][4] = createPiece(PC_BLACK, PT_KING);
  board.data[0][5] = createPiece(PC_BLACK, PT_BISHOP);
  board.data[0][6] = createPiece(PC_BLACK, PT_KNIGHT);
  board.data[0][7] = createPiece(PC_BLACK, PT_ROOK);

  for (size_t i = 0; i < board_rows; i++) {
    board.data[1][i] = createPiece(PC_BLACK, PT_PAWN);
    board.data[board_rows - 2][i] = createPiece(PC_WHITE, PT_PAWN);
  }

  board.data[board_rows - 1][0] = createPiece(PC_WHITE, PT_ROOK);
  board.data[board_rows - 1][1] = createPiece(PC_WHITE, PT_KNIGHT);
  board.data[board_rows - 1][2] = createPiece(PC_WHITE, PT_BISHOP);
  board.data[board_rows - 1][3] = createPiece(PC_WHITE, PT_QUEEN);
  board.data[board_rows - 1][4] = createPiece(PC_WHITE, PT_KING);
  board.data[board_rows - 1][5] = createPiece(PC_WHITE, PT_BISHOP);
  board.data[board_rows - 1][6] = createPiece(PC_WHITE, PT_KNIGHT);
  board.data[board_rows - 1][7] = createPiece(PC_WHITE, PT_ROOK);

  board.selectedRow = -1;
  board.selectedColumn = -1;
  board.isWhiteTurn = true;
  return board;
}

void displayBoard(board_t* board) {
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

void handleMovement(board_t* board) {
  const Vector2 mousePos = GetMousePosition();
  uint8_t cell_width = GetScreenWidth() / board_columns;
  uint8_t cell_height = GetScreenHeight() / board_rows;

  uint8_t row = floor(mousePos.y / cell_height);
  uint8_t column = floor(mousePos.x  / cell_width);

  if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    return;
  }

  if (board->data[row][column].type != PT_VOID) {
    if (board->isWhiteTurn && board->data[row][column].color == PC_BLACK) return;
    if (!board->isWhiteTurn && board->data[row][column].color == PC_WHITE) return;

    board->selectedColumn = column;
    board->selectedRow = row;
    return;
  }

  if (board->selectedColumn == -1 || board->selectedRow == -1) return;

  printf("(%d, %d) to (%d, %d)\n", board->selectedRow, board->selectedColumn, row, column);
  board->data[row][column] = board->data[board->selectedRow][board->selectedColumn];
  board->data[board->selectedRow][board->selectedColumn] = createPiece(PC_BLACK, PT_VOID);
  board->selectedColumn = -1;
  board->selectedRow = -1;
  board->isWhiteTurn = !board->isWhiteTurn;
}
