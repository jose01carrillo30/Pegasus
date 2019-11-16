#include <iostream>
//#include <cstdint>

using namespace std;

//typedef and board struct moved to header file
#include "board_object.h"
#include "utilityMethods.h"


#define NUM_TEST_BOARDS 5
board::Board** createSomeBoards() {
    /** Method to generate boards to be tested */
    board::Board** boards = new board::Board*[NUM_TEST_BOARDS];
    for(int i = 0; i < NUM_TEST_BOARDS; i++)
    {
        boards[i] = new board::Board();
        boards[i]->hashCode = i*i;
    }
    return boards;
}

ULL createHash(board::Board* board) {
    /** TODO: Hashes 84 bits of board info into 64 bits */
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

