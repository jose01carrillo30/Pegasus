/* A bitboard lookup table generation module
 * I'm just experimenting with things I'm learning about here! - Ori
 */

#include <iostream>

// For convenience.
enum {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

// Sets the sq bit in bb to 1 (sq for square, bb for bitboard)
// Trick: SETBIT(bb, E4)
#define SETBIT(bb, sq) bb |= (1L << sq)
#define rankOf(sq) (sq >> 3) // sq / 8
#define fileOf(sq) (sq & 7) // sq % 7

//// As we've made standard:
//typedef unsigned long long ULL;
#include "board_object.h"
//note that ULL typedef has been moved since different places were using different definitions

// Declare the empty diagonal and antidiagonal lookup tables:
ULL diagonalMasks[16];
ULL antiDiagonalMasks[16];

// First, we create a temporary list of numbers.
// Each number represents a different diagonal (i.e., all the 5s will make a diagonal)
short diags[64];
short antidiags[64];

// Generate the diagonal and antidiagonal ookup tables. This doesn't need to be particularly
// efficient, as it's only executed in the beginning of the program:
void initDiagonalMasks() {
  // Generate the diagonals and antidiagonals:
  for (int i = 0; i < 64; i++) {
    diags[i] = (rankOf(i) - fileOf(i)) & 15;
    antidiags[i] = (rankOf(i) + fileOf(i)) ^ 7;
  }

  // Now, we create the corresponding bitboards (one for each number) in diagonalMasks:
  for (int i = 0; i < 16; i++) {
    // Iterate through each square in diags[]:
    for (int j = 0; j < 64; j++) {
      // if the current square in diags[] is equal to i (our current square), set that bit to 1:
      if (diags[j] == i) SETBIT(diagonalMasks[i], j);
      if (antidiags[j] == i) SETBIT(antiDiagonalMasks[i], j);
    }
  }
}

// A utility function to print out a single bitboard:
void printBitboard(ULL board) {
  // Note: this print function is weird because it uses the Little-Endian Rank-File Mapping:
  // Iterate through all 64 bits:
  for (int i = 7; i >= 0; i--) {
    for (int j = 0; j < 8; j++) {
      // THE CURRENT BIT IS (8i + j)
      // If the current bit is 1, print "1 ". Otherwise, print "0 ":
      std::cout << (((board >> (8*i + j)) & 1) ? "1 " : ". ");
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";
}

/* This function is the same as the one above, but uses a different rank-file mapping.
 * We'll discuss this further and which one we'd like to use, but since I know we're
 * probably using the rank-file mapping as above, I've decided to keep things this way.
 * At least for now. */
/* void printBitboardU(ULL board) {
  // Iterate through all 64 bits:
  for (int i = 0; i < 64; i++) {
    // Make sure to change rows after every 8 squares:
    if (!(i & 7)) std::cout << "\n"; // (i & 7) is the same as i % 8 == 0

    // If the ith bit is 1, print "1 ". Otherwise, print "0 ":
    std::cout << (((board >> i) & 1) ? "1 " : ". ");
  }
  std::cout << "\n\n";
}
*/

ULL diagonalAttackMask(short sq) {
  // NOTE: For this to work, the masks must be initialized!
  // (initDiagonalMasks() must be called prior to this)
  return diagonalMasks[diags[sq]] ^ antiDiagonalMasks[antidiags[sq]];
}

//TODO: renamed and run from "actual_main_here.cpp"
int mainRename_tablegen() {
  initDiagonalMasks();
  // ULL tempBoard = 9251592102432489103L;
  // printBitboardU(tempBoard);
  ULL tempBoard = diagonalAttackMask(D3);
    printBitboard(tempBoard);
  return 0;
}
