#include <iostream>
#include "move_representation.h"
#include "utilityMethods.h"

namespace test_moves_main_namespace{

    int main() {

        /*---------- Test encode/decode move ---------*/
        Move move1 = MoveRepresentation::encodeMove(119, 119, 3, 1, 6, 6, 6);
        for (char target = MoveRepresentation::startPosIndex; target <= MoveRepresentation::pieceThatMovedIndex; target++) {
            std::cout << "i:" << (int)target << "  data:" << MoveRepresentation::decodeMove(move1, target) << std::endl;
        }

        /*---------- Test print/apply move ---------*/
        board::Board testBoard = board::Board(true);
        utility::printBoardArray(&testBoard);

        Move move2 = MoveRepresentation::encodeMove(27, 46);
        MoveRepresentation::applyMove(&testBoard, move2);
        utility::printBoardArray(&testBoard);

        Move move3 = MoveRepresentation::encodeMove(83, 63);
        MoveRepresentation::applyMove(&testBoard, move3);
        utility::printBoard(&testBoard, true);

        MoveRepresentation::applyMove(&testBoard, MoveRepresentation::encodeMove(31, 41));
        utility::printBoard(&testBoard, false, true);
        return 0;
    }
}