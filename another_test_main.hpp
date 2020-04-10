#ifndef ANOTHER_TEST_MAIN_HPP
#define ANOTHER_TEST_MAIN_HPP

#include <iostream>

#include "constants.hh"
#include "move_representation.hpp"
#include "board_object.hh"
#include "utilityMethods.hh"
#include "moveMaker.hpp"
#include "FEN.hpp"

namespace another_test_main_namespace{

    int main() {
        // ----------- Required initialization ----------- //
        move_rep::init();

        // ----------- Create a board ----------- //
        board::Board testBoard = board::Board();
        parseFEN(STARTING_BOARD_FEN, &testBoard);
        utility::printBoard(&testBoard);

        // ----------- Apply move ----------- //
        Move move2 = move_rep::encodeMove(index120to64[27], index120to64[46], WN);
        move_rep::applyMove(&testBoard, move2);
        utility::printBoard(&testBoard);
        return 0;
    }
}

#endif