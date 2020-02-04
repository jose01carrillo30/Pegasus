// NOTE: if we're calling our board object something other than 'board', we gotta change
// it in this little snippet
// TODO:
// - write idx64to120() 'function' (well, a table) and vice versa
// SquareConvert macro: #define SquareConvert(file, rank) ((21 + file) + (10 * rank));

#include <iostream>

bool parseFEN(char* FEN, board* board) {
  if (FEN == nullptr || board == nullptr) return false;

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
        std::cout << "Error while parsing FEN string.\n";
        return false;
    }

    for (int i = 0; i < ct; i++) {
      int sq64 = (rank * 8) + file;
      int sq120 = idx64to120(sq64);
      if (piece != EMPTY) {
        board->pieces[sq120] = piece;
      }
      file++;
    }

    // Now, we move to the next character in the FEN:
    FEN++;
  }

  // Now, we're done parsing the board section of the FEN
  // Parse the current turn:
  board->side = (*FEN == 'w') ? WHITE : BLACK;
  FEN += 2;

  // Parse the castling rights:
  if (*FEN == 'K') {
    board->castleRights += CWK;
    FEN++;
  }
  if (*FEN == 'Q') {
    board->castleRights += CWQ;
    FEN++;
  }
  if (*FEN == 'k') {
    board->castleRights += CBK;
    FEN++;
  }
  if (*FEN == 'q') {
    board->castleRights += CBQ;
    FEN++;
  }

  FEN++;

  // If the next char is a space, move our pointer forward:
  if (*FEN == ' ') FEN++;

  // Parse possible en passant square:
  if (*FEN != '-') {
    file = FEN[0] - 'a'; // get file number
    rank = FEN[1] - '1'; // get rank number
    board->enpassant = SquareConvert(file, rank);

    std::cout << "DEBUG: enpassant " << std::endl;
    std::cout << FEN[0] << std::endl;
    std::cout << FEN[1] << std::endl;
  }

  // Update piece lists:
  // board->updatePieceLists(); // TODO: WRITE THIS FUNCTION!

  return true;
}
