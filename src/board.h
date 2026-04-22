#pragma once

#include "piece.h"
#include "raylib.h"

typedef struct Board {
  Piece data[board_rows][board_columns];
  Texture texture;
  int selectedColumn;
  int selectedRow;
  bool isWhiteTurn;
  Sound moveSound;
  Sound captureSound;
} Board;

Board createBoard();
