#pragma once

#define board_columns 8
#define board_rows 8

#include <raylib.h>
#include <inttypes.h>

typedef enum PieceType {
  PT_VOID,
  PT_PAWN,
  PT_ROOK,
  PT_KNIGHT,
  PT_BISHOP,
  PT_QUEEN,
  PT_KING
} PieceType;

typedef enum PieceColor {
  PC_VOID,
  PC_WHITE,
  PC_BLACK,
} PieceColor;

typedef struct Piece {
  PieceColor color;
  PieceType type;
  Texture* texture;
  bool hasMoved;
} Piece;

Piece createPiece(PieceColor color, PieceType type);
