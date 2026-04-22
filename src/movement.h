#pragma once

#include "board.h"

typedef struct BoardPosition {
  int row;
  int column;
} BoardPosition;

void handleVerHozMovement(uint8_t currentRow, uint8_t currentColumn, Board* board, uint8_t* count, BoardPosition* moves);
BoardPosition* getPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, uint8_t* count);
void handleMovement(Board* board);
