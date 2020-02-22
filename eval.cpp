#include <stdio.h>

#include "constants.h"
#include "move_representation.h"
#include "board_object.h"
#include "utilityMethods.h"
#include "moveMaker.h"
#include "FEN.h"

using namespace board;

namespace eval {
    int evaluate(Board* b) {
        int eval = 0;

        int i = 21; // index64to120[0]
        
        // loop over only the squares of the board:
        UC x, y;
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                // add up material:
                eval += PIECEVALUES[b->chessboard[i]];

                // check for piece-specific threats
                switch (b->chessboard[i]) {
                    case EMPTY: break; // will occur most often
                    case WP:
                        // check: if the piece behind this is also a white pawn, deduct 50 points:
                        if (b->chessboard[i+10] == WP) eval -= 50;
                        break;
                    case BP:
                        // check: if the piece behind this is also a black pawn, deduct (add) 50 points:
                        if (b->chessboard[i-10] == BP) eval += 50;
                        break;
                }

                // increment index:
                i++;
            }

            // skip invalid squares on sides:
            i += 2;
        }

        return eval;
    }

    int main() {
        Board b = Board();
        parseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", &b);
        utility::printBoard(&b);

        // printf("static evaluation returned %d\n", evaluate(&b));

        return 0;
    }
};