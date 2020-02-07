#include <cstdint>

typedef uint32_t UL;
typedef uint32_t Move;

#define STARTING_MATERIAL 0 //TODO: what is an appropriate value?

//---------- Position constants ---------//
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
