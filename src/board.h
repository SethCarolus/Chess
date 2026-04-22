#pragma once

#include "piece.h"

typedef struct Board {
  Piece data[board_rows][board_columns];
  Texture* texture;
  int selectedColumn;
  int selectedRow;
  bool isWhiteTurn;
} Board;

Board createBoard();
