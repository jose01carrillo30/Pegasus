#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

//typedef and board struct moved to header file
#include "board_object.h"
#include "utilityMethods.h"

int randomPosition() {
    //return rand() % 120;
    return 21 + 10*(rand()%8) + (rand()%8);
}

#define NUM_TEST_BOARDS 5
/** Method to generate boards to be tested */
board::Board** createSomeBoards() {
    board::Board** boards = new board::Board*[NUM_TEST_BOARDS];
    for(int boardNum = 0; boardNum < NUM_TEST_BOARDS; boardNum++)
    {
        cout << "creating board..." << endl;
        boards[boardNum] = new board::Board(false, true);
        // Generate random board
        const string pieces = "ppppPPPPnnNNbbBBrrRRppppPPPPqQkK";
        for (size_t i = 0; i < pieces.length(); i++)
            boards[boardNum]->chessboard[randomPosition()] = pieces[i];

    }
    return boards;
}

uint64_t createHash(board::Board* board) {
    /** TODO: Hashes into 64 bits */
    return 69420; //TODO: temporary
}

//TODO: renamed and run from "actual_main_here.cpp"
int mainRename_hash_test_main() {

    board::Board** testBoards = createSomeBoards();

    // print all boards
    for(int i=0; i < NUM_TEST_BOARDS; i++) {
        utility::printBoardArray(testBoards[i]);
        cout << endl;
    }
    utility::printBoard(testBoards[0]);
    cout << endl;

    return 0;
}

