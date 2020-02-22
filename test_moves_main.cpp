#include <iostream>
#include <vector>

#include "constants.h"
#include "move_representation.h"
#include "board_object.h"
#include "utilityMethods.h"
#include "moveMaker.h"
#include "FEN.h"

namespace test_moves_main_namespace{

    int main() {
        /*---------- Required initialization ---------*/
        move_rep::init();

        /*---------- Test encode/decode move ---------*/
        Move move1 = move_rep::encodeMove(63, 59, 14, 10, 1, 0, 1);
        for (char target = move_rep::startPosIndex; target <= move_rep::pieceThatMovedIndex; target++) {
            std::cout << "i:" << (int)target << "  data:" << move_rep::decodeMove(move1, target) << std::endl;
        }

        /*---------- Test print/apply move ---------*/
        board::Board testBoard = board::Board();
        parseFEN(STARTING_BOARD_FEN, &testBoard);
        utility::printBoardArray(&testBoard);

        Move move2 = move_rep::encodeMove(index120to64[27], index120to64[46], WN);
        move_rep::applyMove(&testBoard, move2);
        utility::printBoardArray(&testBoard);

        Move move3 = move_rep::encodeMove(index120to64[83], index120to64[63], BP, EMPTY, false, true /*double jump*/);
        move_rep::applyMove(&testBoard, move3);
        utility::printBoard(&testBoard, true);

        std::vector<Move> testMoves {
            move_rep::encodeMove(index120to64[37], index120to64[47], WP),
            move_rep::encodeMove(index120to64[84], index120to64[74], BP),
            move_rep::encodeMove(index120to64[26], index120to64[48], WB),
            move_rep::encodeMove(index120to64[92], index120to64[71], BN),
            move_rep::encodeMove(index120to64[25], index120to64[27], WK, EMPTY, true /*castle*/),
            move_rep::encodeMove(index120to64[93], index120to64[48], BB, WB /*capture*/),
            move_rep::encodeMove(index120to64[34], index120to64[54], WP, EMPTY, false, true /*double jump*/),
            move_rep::encodeMove(index120to64[94], index120to64[61], BQ),
            move_rep::encodeMove(index120to64[46], index120to64[34], WN),
            move_rep::encodeMove(index120to64[63], index120to64[53], BP),
            move_rep::encodeMove(index120to64[32], index120to64[52], WP, EMPTY, false, true /*double jump*/),
            move_rep::encodeMove(index120to64[53], index120to64[42], BP, WP, false, true /*en passant*/),
            move_rep::encodeMove(index120to64[34], index120to64[55], WN),
            move_rep::encodeMove(index120to64[42], index120to64[31], BP, WP),
            move_rep::encodeMove(index120to64[55], index120to64[74], WN, BP),
            move_rep::encodeMove(index120to64[31], index120to64[22], BQ, WN /*capture*/, false, false, true /*promote*/),
            move_rep::encodeMove(index120to64[55], index120to64[74], WN, BP),
            move_rep::encodeMove(index120to64[31], index120to64[22], BQ, WN /*capture*/, false, false, true /*promote*/),
        }; 
        for (auto moveIter = testMoves.begin(); moveIter != testMoves.end(); moveIter++) { 
            move_rep::applyMove(&testBoard, *moveIter);
            utility::printBoard(&testBoard, false, true);
        }

        /*---------- Test undo move ---------*/
        std::cout << "\n\n------------------------\nTESING UNDO MOVES\n------------------------\n" << std::endl;
        for (auto moveIter = testMoves.rbegin(); moveIter != testMoves.rend(); moveIter++) { 
            move_rep::undoMove(&testBoard);
            utility::printBoard(&testBoard, false, true);
        }
        return 0;
    }
}