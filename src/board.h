#pragma once

#include "piece.h"
#include "raylib.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

typedef struct board {
  piece_t data[board_rows][board_columns];
  Texture texture;
  int selectedColumn;
  int selectedRow;
  bool isWhiteTurn;
  Sound moveSound;
  Sound captureSound;
} board_t;

board_t createBoard() {
  board_t board;

  Image boardImg = LoadImage("../resources/boards-png/rect-8x8.png");
  ImageResize(&boardImg, GetScreenWidth(), GetScreenHeight());
  board.texture = LoadTextureFromImage(boardImg);
  UnloadImage(boardImg);

  board.moveSound = LoadSound("../resources/sounds/move.wav");
  board.captureSound = LoadSound("../resources/sounds/capture.wav");

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

typedef struct BoardPosition {
  int row;
  int column;
} boardPosition_t;

void handleVerHozMovement(uint8_t currentRow, uint8_t currentColumn, board_t* board, uint8_t* count, boardPosition_t* moves){
  for (size_t i = currentColumn - 1; i >= 0 ; i--) {
    if (board->data[currentRow][i].type != PT_VOID) break;
    moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = i };
  }
  for (size_t i = currentColumn + 1; i < board_columns; i++){
    if (board->data[currentRow][i].type != PT_VOID) break;
    moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = i };
  }

  for (size_t i = currentRow - 1; i >= 0; i-- ) {
    if (board->data[i][currentColumn].type != PT_VOID) break;
    moves[(*count)++] = (boardPosition_t) { .row = i, .column = currentColumn};
  }
  for (size_t i = currentRow + 1; i < board_columns; i++){
    if (board->data[i][currentColumn].type != PT_VOID) break;
    moves[(*count)++] = (boardPosition_t) { .row = i, .column = currentColumn};
  }
}
void handleDiagMovement(uint8_t currentRow, uint8_t currentColumn, board_t* board, uint8_t* count, boardPosition_t* moves)  {
  // LEFT
  // TOP
  // BOTTOM
  //
  for (size_t i = currentColumn - 1, j = currentRow - 1;i  >= 0 && j >= 0; i--, j--) {
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*count)++] = (boardPosition_t) { .row = j, .column = i};
  }

  for (size_t i = currentColumn - 1 , j = currentRow + 1;i >= 0 && j < board_rows; i--, j++){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*count)++] = (boardPosition_t) { .row = j, .column = i};
  }
  // RIGHT
  // TOP BOTTOM

  for (size_t i = currentColumn + 1, j = currentRow - 1 ; i < board_columns && j < board_rows; i++, j--){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*count)++] = (boardPosition_t) { .row = j, .column = i};
  }

  for (size_t i = currentColumn + 1, j = currentRow + 1; i < board_columns && j < board_rows; i++, j++){
    if (board->data[j][i].type != PT_VOID) {
      break;
    }
    moves[(*count)++] = (boardPosition_t) { .row = j, .column = i};
  }
}

boardPosition_t* getPossibleMoves(uint8_t currentRow, uint8_t currentColumn, board_t* board, uint8_t* count) {
  if (board == NULL) return  NULL;
  piece_t piece = board->data[currentRow][currentColumn];
  *count = 0;
  boardPosition_t* moves = malloc(sizeof(boardPosition_t) * board_rows * board_columns);

  switch(piece.color) {
    case PC_WHITE: {
      switch(piece.type)
      {
        case PT_VOID: {
          return NULL;
          break;
        }
        case PT_PAWN: {
          if (piece.hasMoved) {
            if (board->data[currentRow - 1 ][currentColumn].type == PT_VOID) {
              moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn };
            }
            break;
          }
          for (size_t i = currentRow - 1; i > currentRow - 3; i--) {
            if (board->data[i][currentColumn].type == PT_VOID) {
              moves[(*count)++] = (boardPosition_t) { .row = i, .column = currentColumn };
            }
            else {
              break;
            }
          }
          break;
        }
        case PT_ROOK: {
          handleVerHozMovement(currentRow, currentColumn, board, count, moves);
          break;
        }
        case PT_KNIGHT: {
          // UP 2 LEFT 1
          if (currentRow - 2 >= 0 && currentColumn - 1 >= 0 && board->data[currentRow - 2][currentColumn - 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 2, .column = currentColumn - 1};
          }
          // UP 2 RIGHT 1
          if (currentRow - 2 >= 0 && currentColumn + 1 < 8 && board->data[currentRow - 2][currentColumn + 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 2, .column = currentColumn + 1};
          }

          // DOWN 2  LEFT 1
          if (currentRow + 2 < 8 && currentColumn - 1 >= 0 && board->data[currentRow + 2][currentColumn - 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 2, .column = currentColumn - 1};
          }
          // DOWN 2 RIGHT 1
          if (currentRow + 2 < 8 && currentColumn + 1 < 8 && board->data[currentRow + 2][currentColumn + 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 2, .column = currentColumn + 1};
          }

          // UP 1 LEFT 2
          if (currentRow - 1 >= 0 && currentColumn - 2 >= 0 && board->data[currentRow - 1][currentColumn - 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn - 2};
          }
          // UP 1 RIGHT 2
          if (currentRow - 1 >= 0 && currentColumn + 2 < 8 && board->data[currentRow - 1][currentColumn + 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn + 2};
          }

          // DOWN 1  LEFT 2
          if (currentRow + 1 < 8 && currentColumn - 2 >= 0 && board->data[currentRow + 1][currentColumn - 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn - 2};
          }
          // DOWN 1 RIGHT 2
          if (currentRow + 1 < 8 && currentColumn + 2 < 8 && board->data[currentRow + 1][currentColumn + 2].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn + 2};
          }

          break;
        }
        case PT_BISHOP: {
          handleDiagMovement(currentRow, currentColumn, board, count, moves);
          break;
        }
        case PT_QUEEN: {
          handleVerHozMovement(currentRow, currentColumn, board, count, moves);
          handleDiagMovement(currentRow, currentColumn, board, count, moves);
          break;
        }
        case PT_KING: {
          // UP
          if (currentRow < 8 && board->data[currentRow + 1][currentColumn].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn };
          }
          // DOWN
          if (currentRow > 0 && board->data[currentRow - 1][currentColumn].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn };
          }
          // RIGHT
          if (currentColumn < 8 && board->data[currentRow][currentColumn + 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = currentColumn + 1 };
          }
          // LEFT
          if (currentColumn > 0 && board->data[currentRow][currentColumn - 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = currentColumn - 1 };
          }

          // TOP LEFT
          if (currentColumn < 8 && currentRow < 8 && board->data[currentRow + 1][currentColumn + 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1 , .column = currentColumn + 1 };
          }
          // BOTTOM RIGHT
          if (currentColumn > 0 && currentRow > 0 && board->data[currentRow - 1 ][currentColumn - 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow -1 , .column = currentColumn - 1 };
          }
          // TOP RIGHT
          if (currentColumn > 0 && currentRow < 8 && board->data[currentRow - 1 ][currentColumn + 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1 , .column = currentColumn + 1 };
          }

          // BOTTOM LEFT
          if (currentColumn > 0 && currentRow < 8 && board->data[currentRow + 1 ][currentColumn - 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow +  1 , .column = currentColumn - 1 };
          }
          break;
        }
      }
      break;
    }
    case PC_BLACK: {
      switch(piece.type)
      {
        case PT_VOID: {
          return NULL;
          break;
        }
        case PT_PAWN: {
          if (piece.hasMoved) {
            if (board->data[currentRow + 1 ][currentColumn].type == PT_VOID) {
              moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn };
            }
            break;
          }
          for (size_t i = currentRow + 1; i < currentRow + 3; i++ ){
            if (board->data[i][currentColumn].type == PT_VOID) {
              moves[(*count)++] = (boardPosition_t) { .row = i, .column = currentColumn };
            }
            else {
              break;
            }
          }
          break;
        }
        case PT_ROOK: {
          handleVerHozMovement(currentRow, currentColumn, board, count, moves);
          break;
        }
        case PT_KNIGHT: {
          // UP 2 LEFT 1
          if (currentRow - 2 >= 0 && currentColumn - 1 >= 0 && board->data[currentRow - 2][currentColumn - 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 2, .column = currentColumn - 1};
          }
          // UP 2 RIGHT 1
          if (currentRow - 2 >= 0 && currentColumn + 1 < 8 && board->data[currentRow - 2][currentColumn + 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 2, .column = currentColumn + 1};
          }

          // DOWN 2  LEFT 1
          if (currentRow + 2 < 8 && currentColumn - 1 >= 0 && board->data[currentRow + 2][currentColumn - 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 2, .column = currentColumn - 1};
          }
          // DOWN 2 RIGHT 1
          if (currentRow + 2 < 8 && currentColumn + 1 < 8 && board->data[currentRow + 2][currentColumn + 1 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 2, .column = currentColumn + 1};
          }

          // UP 1 LEFT 2
          if (currentRow - 1 >= 0 && currentColumn - 2 >= 0 && board->data[currentRow - 1][currentColumn - 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn - 2};
          }
          // UP 1 RIGHT 2
          if (currentRow - 1 >= 0 && currentColumn + 2 < 8 && board->data[currentRow - 1][currentColumn + 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn + 2};
          }

          // DOWN 1  LEFT 2
          if (currentRow + 1 < 8 && currentColumn - 2 >= 0 && board->data[currentRow + 1][currentColumn - 2 ].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn - 2};
          }
          // DOWN 1 RIGHT 2
          if (currentRow + 1 < 8 && currentColumn + 2 < 8 && board->data[currentRow + 1][currentColumn + 2].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn + 2};
          }
          break;
        }
        case PT_BISHOP: {
          handleDiagMovement(currentRow, currentColumn, board, count, moves);
          break;
        }
        case PT_QUEEN: {
          handleVerHozMovement(currentRow, currentColumn, board, count, moves);
          handleDiagMovement(currentRow, currentColumn, board, count, moves);
         break;
        }
        case PT_KING: {
          if (currentRow < 8 && board->data[currentRow + 1][currentColumn].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow + 1, .column = currentColumn };
          }
          if (currentRow > 0 && board->data[currentRow - 1][currentColumn].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow - 1, .column = currentColumn };
          }
          if (currentColumn && board->data[currentRow][currentColumn + 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = currentColumn + 1 };
          }
          if (currentColumn > 0 && board->data[currentRow][currentColumn - 1].type == PT_VOID) {
            moves[(*count)++] = (boardPosition_t) { .row = currentRow, .column = currentColumn - 1 };
          }
         break;
        }
      }
      break;
    }
  }
  return moves;
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

  uint8_t count = 0;
  boardPosition_t* possibleMoves = getPossibleMoves(board->selectedRow, board->selectedColumn, board, &count);

  bool canMove = false;
  for (size_t i = 0; i < count; i++) {
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

  if (!IsSoundPlaying(board->moveSound)) {
    PlaySound(board->moveSound);
  }
}
