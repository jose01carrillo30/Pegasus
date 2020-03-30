#ifndef FEN_H
#define FEN_H

#include <iostream>
#include "board_object.hh"
#include "constants.hh"

using namespace board;

static bool parseFEN(const char* FEN, Board* board) {
  if (FEN == nullptr || board == nullptr) return false;

  board->material = 0;
  int rank = 7, file = 0;

  // resetBoard(board); // TODO: create a function that resets the board

  // Parse the FEN, character by character:
  while (rank >= 0 && *FEN) {
    int ct = 1;
    int piece = EMPTY;
    switch (*FEN) {
      // Parse characters:
      case 'p': piece = BP; break;
      case 'r': piece = BR; break;
      case 'n': piece = BN; break;
      case 'b': piece = BB; break;
      case 'k': piece = BK; break;
      case 'q': piece = BQ; break;

      case 'P': piece = WP; break;
      case 'R': piece = WR; break;
      case 'N': piece = WN; break;
      case 'B': piece = WB; break;
      case 'K': piece = WK; break;
      case 'Q': piece = WQ; break;

      // If current FEN char is a number:
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
        // convert the char to its int value:
        ct = *FEN - '0';
        break;

      case '/':
      case ' ':
        rank--; // Because we're parsing down the ranks (we start on 7)
        file = 0;
        FEN++;
        continue;

      // Otherwise, there's an error:
      default:
        return false;
    }

    for (unsigned int i = 0; i < ct; i++) {
      int square_64_index = (rank * 8) + file;
      int square_120_index = index64to120[square_64_index]; // defined in board namespace
      board->chessboard[square_120_index] = piece;
      if (piece != EMPTY) {
        board->material += PIECEVALUES[piece];
      }
      file++;
    }

    // Move the FEN pointer forward:
    FEN++;
  }

  // Now, we're done parsing the board section of the FEN
  // Parse the current turn:
  // NOTE: might be easier to do something like 'const bool WHITE = true' and
  // 'const bool BLACK = false' and use those for turn, that way we could write
  // 'turn = WHITE' which is a lot nicer and easier to understand than 'turnWhite = true'
  board->turnWhite = (*FEN == 'w') ? true : false;
  FEN += 2;

  // Parse the castling rights:
  // set them all to false at first (only done here instead of as an else-if for easier readability):
  board->CWK = false;
  board->CWQ = false;
  board->CBK = false;
  board->CBQ = false;

  if (*FEN == 'K') {
    board->CWK = true;
    FEN++;
  }
  if (*FEN == 'Q') {
    board->CWQ += true;
    FEN++;
  }
  if (*FEN == 'k') {
    board->CBK += true;
    FEN++;
  }
  if (*FEN == 'q') {
    board->CBQ += true;
    FEN++;
  }

  FEN++;

  // If the next char is a space, move our pointer forward:
  if (*FEN == ' ') FEN++;

  // Parse possible en passant square:
  board->EP = (*FEN == '-') ? -1 : (*FEN - 'a');

  // Update piece lists:
  // board->updatePieceLists(); // TODO: WRITE THIS FUNCTION!

  return true;
}
#endif