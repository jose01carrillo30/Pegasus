#include <iostream>
#include <vector>

#include "constants.h"
#include "move_representation.h"
#include "board_object.h"
#include "utilityMethods.h"
#include "moveMaker.h"

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
        board::Board testBoard = board::Board(true);
        utility::printBoardArray(&testBoard);

        Move move2 = move_rep::encodeMove(board::index120to64[27], board::index120to64[46], board::WN);
        move_rep::applyMove(&testBoard, move2);
        utility::printBoardArray(&testBoard);

        Move move3 = move_rep::encodeMove(board::index120to64[83], board::index120to64[63], board::BP, board::EMPTY, false, true /*double jump*/);
        move_rep::applyMove(&testBoard, move3);
        utility::printBoard(&testBoard, true);

        std::vector<Move> testMoves {
            move_rep::encodeMove(board::index120to64[37], board::index120to64[47], board::WP),
            move_rep::encodeMove(board::index120to64[84], board::index120to64[74], board::BP),
            move_rep::encodeMove(board::index120to64[26], board::index120to64[48], board::WB),
            move_rep::encodeMove(board::index120to64[92], board::index120to64[71], board::BN),
            move_rep::encodeMove(board::index120to64[25], board::index120to64[27], board::WK, board::EMPTY, true /*castle*/),
            move_rep::encodeMove(board::index120to64[93], board::index120to64[48], board::BB, board::WB /*capture*/),
            move_rep::encodeMove(board::index120to64[34], board::index120to64[54], board::WP, board::EMPTY, false, true /*double jump*/),
            move_rep::encodeMove(board::index120to64[94], board::index120to64[61], board::BQ),
            move_rep::encodeMove(board::index120to64[46], board::index120to64[34], board::WN),
            move_rep::encodeMove(board::index120to64[63], board::index120to64[53], board::BP),
            move_rep::encodeMove(board::index120to64[32], board::index120to64[52], board::WP, board::EMPTY, false, true /*double jump*/),
            move_rep::encodeMove(board::index120to64[53], board::index120to64[42], board::BP, board::WP, false, true /*en passant*/),
            move_rep::encodeMove(board::index120to64[34], board::index120to64[55], board::WN),
            move_rep::encodeMove(board::index120to64[42], board::index120to64[31], board::BP, board::WP),
            move_rep::encodeMove(board::index120to64[55], board::index120to64[74], board::WN, board::BP),
            move_rep::encodeMove(board::index120to64[31], board::index120to64[22], board::BQ, board::WN /*capture*/, false, false, true /*promote*/),
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