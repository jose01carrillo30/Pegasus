#include <iostream>
#include <vector>
#include "move_representation.h"
#include "board_object.h"
#include "utilityMethods.h"

namespace test_moves_main_namespace{

    int main() {

        /*---------- Test encode/decode move ---------*/
        Move move1 = MoveRepresentation::encodeMove(119, 119, 6, 6, 2, 15, 6);
        for (char target = MoveRepresentation::startPosIndex; target <= MoveRepresentation::pieceThatMovedIndex; target++) {
            std::cout << "i:" << (int)target << "  data:" << MoveRepresentation::decodeMove(move1, target) << std::endl;
        }

        /*---------- Test print/apply move ---------*/
        std::vector<Move> testMoves {
            MoveRepresentation::encodeMove(37, 47, board::WP),
            MoveRepresentation::encodeMove(84, 74, board::BP),
            MoveRepresentation::encodeMove(26, 48, board::WB),
            MoveRepresentation::encodeMove(92, 71, board::BN),
            MoveRepresentation::encodeMove(25, 27, board::WK, utility::uncolor(board::EMPTY), MoveRepresentation::SHORT_CASTLE),
            MoveRepresentation::encodeMove(93, 48, board::BB, utility::uncolor(board::WB)),
            MoveRepresentation::encodeMove(34, 54, board::WP),
            MoveRepresentation::encodeMove(94, 61, board::BQ),
            MoveRepresentation::encodeMove(46, 34, board::WN),
            MoveRepresentation::encodeMove(63, 53, board::BP),
            MoveRepresentation::encodeMove(32, 52, board::WP),
            MoveRepresentation::encodeMove(53, 42, board::BP, utility::uncolor(board::EMPTY), MoveRepresentation::NO_CASTLE, 1u /*TODO: what should this be?*/),
            MoveRepresentation::encodeMove(34, 55, board::WN),
            MoveRepresentation::encodeMove(42, 31, board::BP, utility::uncolor(board::WP)),
            MoveRepresentation::encodeMove(55, 74, board::WN, utility::uncolor(board::BP)),
            MoveRepresentation::encodeMove(31, 22, board::BP, utility::uncolor(board::WN), MoveRepresentation::NO_CASTLE, 0u, utility::uncolor(board::BQ)),
        }; 
        board::Board testBoard = board::Board(true);
        utility::printBoardArray(&testBoard);

        Move move2 = MoveRepresentation::encodeMove(27, 46, board::WN);
        MoveRepresentation::applyMove(&testBoard, move2);
        utility::printBoardArray(&testBoard);

        Move move3 = MoveRepresentation::encodeMove(83, 63, board::BP);
        MoveRepresentation::applyMove(&testBoard, move3);
        utility::printBoard(&testBoard, true);

        for (auto moveIter = testMoves.begin(); moveIter != testMoves.end(); moveIter++) { 
            MoveRepresentation::applyMove(&testBoard, *moveIter);
            utility::printBoard(&testBoard, false, true);
        }

        /*---------- Test undo move ---------*/
        std::cout << "\n\n------------------------\nTESING UNDO MOVES\n------------------------\n" << std::endl;
        for (auto moveIter = testMoves.rbegin(); moveIter != testMoves.rend(); moveIter++) { 
            MoveRepresentation::undoMove(&testBoard, *moveIter);
            utility::printBoard(&testBoard, false, true);
        }
        return 0;
    }
}