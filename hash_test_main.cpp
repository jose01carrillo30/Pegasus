#include <iostream>
//#include <cstdint>

using namespace std;

//typedef and board struct moved to header file
#include "board_object_DEPRECIATED.h"

//TODO: there has to be a better way than this:
const string pieceRepresentation = "PNBRQKpnbrqk";

void printBoard(BitBoard* board) {
    /**TODO: outputs nice visual given board*/
    cout << "BitBoard: " << board->hashCode << endl;

    //pring bitboards
    /* //Useful for debuggging 
    for (int pieceType = 0; pieceType < 12; pieceType++)
    { 
        cout << pieceRepresentation[pieceType] << " : " << board->bitboards[pieceType] << endl; 
    } */

    // print grid
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char toPrint = '.';
            for (int pieceType = 0; pieceType < 12; pieceType++)
            {
                //cout << "mask for "<<i<<", "<<j<<" : " << ((ULL(1)) << (8*i + j)) << endl;
                if(board->bitboards[pieceType] & ( ULL(1) << (8*i + j)))
                    toPrint = pieceRepresentation[pieceType];
            }
            cout << toPrint;
        }
        cout << endl;
    }
}

BitBoard* createFromFenn(string fenn) {
    /** TODO: */
    //TODO
    return nullptr;
}

#define NUM_TEST_BOARDS 5
BitBoard** createSomeBoards() {
    /** Method to generate boards to be tested */
    BitBoard** boards = new BitBoard*[NUM_TEST_BOARDS];
    for(int i = 0; i < NUM_TEST_BOARDS; i++)
    {
        boards[i] = new BitBoard();
        boards[i]->hashCode = i*i;
    }
    return boards;
}

ULL createHash(BitBoard* board) {
    /** TODO: Hashes 84 bits of board info into 64 bits */
    return board->bitboards[WP]; //TODO: temporary. test by literally returning the white pawn layout as the hash
}

//TODO: renamed and run from "actual_main_here.cpp"
int mainRename_hash_test_main() {

    //TODO: replace this with the FEN string
    BitBoard STARTING_BOARD = BitBoard();
    {
    STARTING_BOARD.CWK = true;
    STARTING_BOARD.CWQ = true;
    STARTING_BOARD.CBK = true;
    STARTING_BOARD.CBQ = true;
    STARTING_BOARD.bitboards[WP] = 0xff00;
    STARTING_BOARD.bitboards[BP] = 0xff000000000000;
    STARTING_BOARD.bitboards[WR] = 0x81;
    STARTING_BOARD.bitboards[BR] = 0x8100000000000000;
    STARTING_BOARD.bitboards[WN] = 0x42;
    STARTING_BOARD.bitboards[BN] = 0x4200000000000000;
    STARTING_BOARD.bitboards[WB] = 0x24;
    STARTING_BOARD.bitboards[BB] = 0x2400000000000000;
    STARTING_BOARD.bitboards[WQ] = 0x8;
    STARTING_BOARD.bitboards[BQ] = 0x800000000000000;
    STARTING_BOARD.bitboards[WK] = 0x10;
    STARTING_BOARD.bitboards[BK] = 0x1000000000000000;
    STARTING_BOARD.CWK = true;
    STARTING_BOARD.CWQ = true;
    STARTING_BOARD.CBK = true;
    STARTING_BOARD.CBQ = true;
    STARTING_BOARD.kings = 64*3 + 59; // king locations: kings = WK*64 + BK // doesn't matter for hashing
    STARTING_BOARD.EP = 0; // Assuming 0 means no en passant
    // materialWhite, materialBlack; // doesn't matter for hashing
    STARTING_BOARD.movesSinceLastCapture = 0; // I don't think this matters for hashing really, only really useful when close to 50
    STARTING_BOARD.hashCode = createHash(&STARTING_BOARD);
    }

    cout << "****************" << endl;
    cout << "Testing program:" << endl;
    cout << "****************" << endl;

    printBoard(&STARTING_BOARD);

    BitBoard** testBoards = createSomeBoards();

    // print all boards
    for(int i=0; i < NUM_TEST_BOARDS; i++) {
        printBoard(testBoards[i]);
    }

    return 0;
}

