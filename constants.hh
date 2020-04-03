#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

// For readability
/** Stores information about which piece moved on a turn */
typedef uint32_t Move;
/** Board position, as a 64 position index */
typedef unsigned char pos64;
/** Board position, as a 120 position index */
typedef unsigned char pos120;

// For convenience
typedef unsigned char UC;
typedef unsigned int uint;
typedef uint32_t UL;

#define STARTING_MATERIAL 0 //TODO: what is an appropriate value?

typedef unsigned char PieceEnum;
/**
 * White is even, black is odd, and all pieces are less than EMPTY
 * We also use this so that this enum can be directly used as an array index for pieces
 * For example, WP means White Pawn, BN mean Black kNight
 * INVALID is a tile that appears outside the 8x8 square but within the 120-index array.
*/
enum : PieceEnum {WP, BP, WR, BR, WN, BN, WB, BB, WQ, BQ, WK, BK, EMPTY, INVALID};

static const PieceEnum blackPieces[6] = {BP, BR, BN, BB, BQ, BK};
static const PieceEnum whitePieces[6] = {WP, WR, WN, WB, WQ, WK};

static const pos64 index120to64[] = {
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127,  0,  1,  2,  3,  4,  5,  6,  7, 127,
    127,  8,  9, 10, 11, 12, 13, 14, 15, 127,
    127, 16, 17, 18, 19, 20, 21, 22, 23, 127,
    127, 24, 25, 26, 27, 28, 29, 30, 31, 127,
    127, 32, 33, 34, 35, 36, 37, 38, 39, 127,
    127, 40, 41, 42, 43, 44, 45, 46, 47, 127,
    127, 48, 49, 50, 51, 52, 53, 54, 55, 127,
    127, 56, 57, 58, 59, 60, 61, 62, 63, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127
};
static const pos120 index64to120[] = {
    21, 22, 23, 24, 25, 26, 27, 28,
    31, 32, 33, 34, 35, 36, 37, 38,
    41, 42, 43, 44, 45, 46, 47, 48,
    51, 52, 53, 54, 55, 56, 57, 58,
    61, 62, 63, 64, 65, 66, 67, 68,
    71, 72, 73, 74, 75, 76, 77, 78,
    81, 82, 83, 84, 85, 86, 87, 88,
    91, 92, 93, 94, 95, 96, 97, 98
};


//---------- 120 index position constants ---------//
// Corners of the board
#define ROOK_B_SHORT_CORNER 98 // h8
#define ROOK_B_LONG_CORNER 91 // a8
#define ROOK_W_SHORT_CORNER 28 // h1
#define ROOK_W_LONG_CORNER 21 // a1

// Castling constants
#define ROOK_B_SHORT_CASTLE_TO 96 // f8
#define ROOK_B_LONG_CASTLE_TO 94 // d8
#define ROOK_W_SHORT_CASTLE_TO 26 // f1
#define ROOK_W_LONG_CASTLE_TO 24 // d1

// piece value list:
// used as follows: PIECEVALUES[WP], for example
const short PIECEVALUES[] = {100, -100, 500, -500, 300, -300, 300, -300, 900, -900, 10000, -10000, 0};

static const char* EMPTY_BOARD_FEN = "8/8/8/8/8/8/8/8 w - - 0 1";

static const char* STARTING_BOARD_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

#endif