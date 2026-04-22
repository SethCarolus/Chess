#include "board.h"

#include "stdio.h"

#include <math.h>
#include <stdint.h>
#include <malloc.h>

#include "asset_manager.h"

Board createBoard() {
  Board board;

  board.texture = getBoardTexture();

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
