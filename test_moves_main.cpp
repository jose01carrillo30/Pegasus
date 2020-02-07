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
        MoveRepresentation::init();

        /*---------- Test encode/decode move ---------*/
        Move move1 = MoveRepresentation::encodeMove(63, 59, 14, 10, 1, 0, 1);
        for (char target = MoveRepresentation::startPosIndex; target <= MoveRepresentation::pieceThatMovedIndex; target++) {
            std::cout << "i:" << (int)target << "  data:" << MoveRepresentation::decodeMove(move1, target) << std::endl;
        }

        /*---------- Test print/apply move ---------*/
        board::Board testBoard = board::Board(true);
        utility::printBoardArray(&testBoard);

        Move move2 = MoveRepresentation::encodeMove(board::index120to64[27], board::index120to64[46], board::WN);
        moveMaker::applyMove(&testBoard, move2);
        utility::printBoardArray(&testBoard);

        Move move3 = MoveRepresentation::encodeMove(board::index120to64[83], board::index120to64[63], board::BP, board::EMPTY, false, true /*double jump*/);
        moveMaker::applyMove(&testBoard, move3);
        utility::printBoard(&testBoard, true);

        std::vector<Move> testMoves {
            MoveRepresentation::encodeMove(board::index120to64[37], board::index120to64[47], board::WP),
            MoveRepresentation::encodeMove(board::index120to64[84], board::index120to64[74], board::BP),
            MoveRepresentation::encodeMove(board::index120to64[26], board::index120to64[48], board::WB),
            MoveRepresentation::encodeMove(board::index120to64[92], board::index120to64[71], board::BN),
            MoveRepresentation::encodeMove(board::index120to64[25], board::index120to64[27], board::WK, board::EMPTY, true /*castle*/),
            MoveRepresentation::encodeMove(board::index120to64[93], board::index120to64[48], board::BB, board::WB /*capture*/),
            MoveRepresentation::encodeMove(board::index120to64[34], board::index120to64[54], board::WP, board::EMPTY, false, true /*double jump*/),
            MoveRepresentation::encodeMove(board::index120to64[94], board::index120to64[61], board::BQ),
            MoveRepresentation::encodeMove(board::index120to64[46], board::index120to64[34], board::WN),
            MoveRepresentation::encodeMove(board::index120to64[63], board::index120to64[53], board::BP),
            MoveRepresentation::encodeMove(board::index120to64[32], board::index120to64[52], board::WP, board::EMPTY, false, true /*double jump*/),
            MoveRepresentation::encodeMove(board::index120to64[53], board::index120to64[42], board::BP, board::WP, false, true /*en passant*/),
            MoveRepresentation::encodeMove(board::index120to64[34], board::index120to64[55], board::WN),
            MoveRepresentation::encodeMove(board::index120to64[42], board::index120to64[31], board::BP, board::WP),
            MoveRepresentation::encodeMove(board::index120to64[55], board::index120to64[74], board::WN, board::BP),
            MoveRepresentation::encodeMove(board::index120to64[31], board::index120to64[22], board::BQ, board::WN /*capture*/, false, false, true /*promote*/),
        }; 
        for (auto moveIter = testMoves.begin(); moveIter != testMoves.end(); moveIter++) { 
            moveMaker::applyMove(&testBoard, *moveIter);
            utility::printBoard(&testBoard, false, true);
        }

        /*---------- Test undo move ---------*/
        std::cout << "\n\n------------------------\nTESING UNDO MOVES\n------------------------\n" << std::endl;
        for (auto moveIter = testMoves.rbegin(); moveIter != testMoves.rend(); moveIter++) { 
            moveMaker::undoMove(&testBoard, *moveIter);
            utility::printBoard(&testBoard, false, true);
        }
        return 0;
    }
}