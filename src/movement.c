#include "movement.h"
#include "piece.h"
#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>
#include <math.h>

extern Sound moveSound;

typedef struct Move{
  int row;
  int column;
} Move;

void getVeriticalHorizontalPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, Move* moves, uint8_t* moves_count){
  for (size_t i = currentColumn - 1; i >= 0 ; i--) {
    if (board->data[currentRow][i].type != PT_VOID) break;
    moves[(*moves_count)++] = (Move) { .row = currentRow, .column = i };
  }
  for (size_t i = currentColumn + 1; i < board_columns; i++){
    if (board->data[currentRow][i].type != PT_VOID) break;
    moves[(*moves_count)++] = (Move) { .row = currentRow, .column = i };
  }

  for (size_t i = currentRow - 1; i >= 0; i-- ) {
    if (board->data[i][currentColumn].type != PT_VOID) break;
    moves[(*moves_count)++] = (Move) { .row = i, .column = currentColumn};
  }
  for (size_t i = currentRow + 1; i < board_columns; i++){
    if (board->data[i][currentColumn].type != PT_VOID) break;
    moves[(*moves_count)++] = (Move) { .row = i, .column = currentColumn};
  }
}
void getDiagonalPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, Move* moves, uint8_t* moves_count) {
  // LEFT
  // TOP
  // BOTTOM
  //
  for (size_t i = currentColumn - 1, j = currentRow - 1;i  >= 0 && j >= 0; i--, j--) {
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*moves_count)++] = (Move) { .row = j, .column = i};
  }

  for (size_t i = currentColumn - 1 , j = currentRow + 1;i >= 0 && j < board_rows; i--, j++){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*moves_count)++] = (Move) { .row = j, .column = i};
  }
  // RIGHT
  // TOP BOTTOM

  for (size_t i = currentColumn + 1, j = currentRow - 1 ; i < board_columns && j < board_rows; i++, j--){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*moves_count)++] = (Move) { .row = j, .column = i};
  }

  for (size_t i = currentColumn + 1, j = currentRow + 1; i < board_columns && j < board_rows; i++, j++){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*moves_count)++] = (Move) { .row = j, .column = i};
  }
}
void getKnightPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, Move* moves, uint8_t* moves_count) {
  // UP 2 LEFT 1
  if (currentRow - 2 >= 0 && currentColumn - 1 >= 0 && board->data[currentRow - 2][currentColumn - 1 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 2, .column = currentColumn - 1};
  }
  // UP 2 RIGHT 1
  if (currentRow - 2 >= 0 && currentColumn + 1 < 8 && board->data[currentRow - 2][currentColumn + 1 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 2, .column = currentColumn + 1};
  }

  // DOWN 2  LEFT 1
  if (currentRow + 2 < 8 && currentColumn - 1 >= 0 && board->data[currentRow + 2][currentColumn - 1 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow + 2, .column = currentColumn - 1};
  }
  // DOWN 2 RIGHT 1
  if (currentRow + 2 < 8 && currentColumn + 1 < 8 && board->data[currentRow + 2][currentColumn + 1 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow + 2, .column = currentColumn + 1};
  }

  // UP 1 LEFT 2
  if (currentRow - 1 >= 0 && currentColumn - 2 >= 0 && board->data[currentRow - 1][currentColumn - 2 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 1, .column = currentColumn - 2};
  }
  // UP 1 RIGHT 2
  if (currentRow - 1 >= 0 && currentColumn + 2 < 8 && board->data[currentRow - 1][currentColumn + 2 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 1, .column = currentColumn + 2};
  }

  // DOWN 1  LEFT 2
  if (currentRow + 1 < 8 && currentColumn - 2 >= 0 && board->data[currentRow + 1][currentColumn - 2 ].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow + 1, .column = currentColumn - 2};
  }
  // DOWN 1 RIGHT 2
  if (currentRow + 1 < 8 && currentColumn + 2 < 8 && board->data[currentRow + 1][currentColumn + 2].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow + 1, .column = currentColumn + 2};
  }
}
void getKingPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, Move* moves, uint8_t* moves_count) {
  // DOWN
  if (currentRow > 0 && board->data[currentRow - 1][currentColumn].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 1, .column = currentColumn };
  }
  // RIGHT
  if (currentColumn < 8 && board->data[currentRow][currentColumn + 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow, .column = currentColumn + 1 };
  }
  // LEFT
  if (currentColumn > 0 && board->data[currentRow][currentColumn - 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow, .column = currentColumn - 1 };
  }

  // TOP LEFT
  if (currentColumn < 8 && currentRow < 8 && board->data[currentRow + 1][currentColumn + 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow + 1 , .column = currentColumn + 1 };
  }
  // BOTTOM RIGHT
  if (currentColumn > 0 && currentRow > 0 && board->data[currentRow - 1 ][currentColumn - 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow -1 , .column = currentColumn - 1 };
  }
  // TOP RIGHT
  if (currentColumn > 0 && currentRow < 8 && board->data[currentRow - 1 ][currentColumn + 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow - 1 , .column = currentColumn + 1 };
  }

  // BOTTOM LEFT
  if (currentColumn > 0 && currentRow < 8 && board->data[currentRow + 1 ][currentColumn - 1].type == PT_VOID) {
    moves[(*moves_count)++] = (Move) { .row = currentRow +  1 , .column = currentColumn - 1 };
  }
}

void getPossibleMoves(uint8_t currentRow, uint8_t currentColumn, Board* board, Move* moves, uint8_t* moves_count) {
  if (board == NULL) return;
  Piece piece = board->data[currentRow][currentColumn];
  *moves_count = 0;

  switch(piece.color) {
    case PC_WHITE: {
      switch(piece.type) {
        case PT_VOID: {
          return;
          break;
        }
        case PT_PAWN: {
          if (piece.hasMoved) {
            if (board->data[currentRow - 1 ][currentColumn].type == PT_VOID) {
              moves[(*moves_count)++] = (Move) { .row = currentRow - 1, .column = currentColumn };
            }
            break;
          }
          for (size_t i = currentRow - 1; i > currentRow - 3; i--) {
            if (board->data[i][currentColumn].type == PT_VOID) {
              moves[(*moves_count)++] = (Move) { .row = i, .column = currentColumn };
            }
            else {
              break;
            }
          }
          break;
        }
        case PT_ROOK: {
          getVeriticalHorizontalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
        case PT_KNIGHT: {
          getKnightPossibleMoves(currentRow, currentColumn, board,moves, moves_count);
          break;
        }
        case PT_BISHOP: {
          getDiagonalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
        case PT_QUEEN: {
          getVeriticalHorizontalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          getDiagonalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
        case PT_KING: {
          getKingPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
      }
      break;
    }
    case PC_BLACK: {
      switch(piece.type) {
        case PT_VOID: {
          return;
          break;
        }
        case PT_PAWN: {
          if (piece.hasMoved) {
            if (board->data[currentRow + 1 ][currentColumn].type == PT_VOID) {
              moves[(*moves_count)++] = (Move) { .row = currentRow + 1, .column = currentColumn };
            }
            break;
          }
          for (size_t i = currentRow + 1; i < currentRow + 3; i++ ){
            if (board->data[i][currentColumn].type == PT_VOID) {
              moves[(*moves_count)++] = (Move) { .row = i, .column = currentColumn };
            }
            else {
              break;
            }
          }
          break;
        }
        case PT_ROOK: {
          getVeriticalHorizontalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
        case PT_KNIGHT: {
          getKnightPossibleMoves(currentRow, currentColumn, board,moves, moves_count);
          break;
        }
        case PT_BISHOP: {
          getDiagonalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
        case PT_QUEEN: {
          getVeriticalHorizontalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          getDiagonalPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
         break;
        }
        case PT_KING: {
          getKingPossibleMoves(currentRow, currentColumn, board, moves, moves_count);
          break;
        }
      }
      break;
    }
  }
}

void getMouseRowColumn(uint8_t* row, uint8_t* column) {
  const Vector2 mousePos = GetMousePosition();
  uint8_t cell_width = GetScreenWidth() / board_columns;
  uint8_t cell_height = GetScreenHeight() / board_rows;

  *row = floor(mousePos.y / cell_height);
  *column = floor(mousePos.x  / cell_width);
}

void selectRowColumn(Board* board, uint8_t row, uint8_t column) {
  if (board->data[row][column].type != PT_VOID) {
    if (board->isWhiteTurn && board->data[row][column].color == PC_BLACK) return;
    if (!board->isWhiteTurn && board->data[row][column].color == PC_WHITE) return;

    board->selectedColumn = column;
    board->selectedRow = row;
  }
}

void makeMove(Board* board, uint8_t row, uint8_t column) {
  uint8_t moves_count = 0;
  Move* possibleMoves = malloc(sizeof(Move) * board_rows * board_columns);

  getPossibleMoves(board->selectedRow, board->selectedColumn, board, possibleMoves, &moves_count);

  bool canMove = false;
  for (size_t i = 0; i < moves_count; i++) {
    if (possibleMoves[i].row == row && possibleMoves[i].column == column) {
      canMove = true;
      break;
    }
  }
  free(possibleMoves);

  if (!canMove) return;
  board->data[board->selectedRow][board->selectedColumn].hasMoved = true;
  printf("(%d, %d) to (%d, %d)\n", board->selectedRow, board->selectedColumn, row, column);
  board->data[row][column] = board->data[board->selectedRow][board->selectedColumn];
  board->data[board->selectedRow][board->selectedColumn] = createPiece(PC_BLACK, PT_VOID);
  board->selectedColumn = -1;
  board->selectedRow = -1;

  board->isWhiteTurn = !board->isWhiteTurn;

  if (!IsSoundPlaying(moveSound)) {
    PlaySound(moveSound);
  }
}

void handleMovement(Board* board) {
  uint8_t row;
  uint8_t column;

  getMouseRowColumn(&row, &column);

  if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    return;
  }

  selectRowColumn(board, row, column);

  if (board->selectedColumn == -1 || board->selectedRow == -1) return;

  makeMove(board, row, column);
}
