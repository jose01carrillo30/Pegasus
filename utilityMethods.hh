#ifndef PEGASUS_STUFF_UTILITYMETHODS_H
#define PEGASUS_STUFF_UTILITYMETHODS_H

#include <iostream>
#include <bitset>

#include "constants.hh"
#include "board_object.hh"

namespace utility{

    /** Prints binary representation of 64 bit number to cout */
    void printBinary(uint64_t val);

    /** 
     * Returns string of uint64_t with comma separation 
     * Credit to carljalal https://stackoverflow.com/questions/7276826/c-format-number-with-commas
     */
    std::string toCommaString(uint64_t num);

    /**
     * Gets char respresentation of piece type enum
     * OPTIONALLY set empty to desired character representation of EMPTY, 
     * OPTIONALLY set invalid to desired character representation of INVALID, 
     */
    unsigned char getCharFromEnum(unsigned char enumValue, char empty='.', char invalid='x');

    /** Is this a valid nonempty piece enum? */
    inline bool isPiece(unsigned char spaceEnum) {
        return spaceEnum < EMPTY; // Assumes piece enums are immediately followed by EMPTY enum
    }
    /** Assuming a valid nonempty piece enum, is the piece white or black? */
    inline bool isBlack(unsigned char piece) {
        return piece % 2; // Assumes black pieces are odd enums
    }
    /** Assuming a valid nonempty piece enum, is the piece white or black? */
    inline bool isWhite(unsigned char piece) {
        return !(piece % 2); //Assumes white pieces are even enums
    }
    /** Converts the piece to white, if not already. Note this also converts INVALID to EMPTY. */
    inline unsigned char toWhite(unsigned char piece) {
        // just overwrite LSB.
        return piece & !1u; //Assumes white pieces are even enums
    }
    /** Converts the piece to black, if not already. Note this also converts EMPTY to INVALID. */
    inline unsigned char toBlack(unsigned char piece) {
        // just overwrite LSB.
        return piece | 1u; //Assumes balck pieces are odd enums
    }
    /** Converts the piece to non-colored enum, as used by Move. */
    inline unsigned char uncolor(unsigned char piece) {
        // just strip LSB.
        return piece >> 1;
    }
    /** Converts the piece from a non-colored enum to White. */
    inline unsigned char recolor(unsigned char piece) {
        // just add LSB of zero.
        return piece << 1;
    }

    //TODO: all of these print board, getColumn, etc. should be moved to board class
    /** 
     * Prints the pieceLocation array in a format to help with debugging.
     */
    void printBoardPieceLocations(board::Board* board);
    /** 
     * Generates a board (setting the chessboard[] array only) using the pieceLocation array of another board.
     * For debugging only.
     */
    board::Board boardFromPieceLocations(board::Board* board);

    /** 
     * Prints the entire Board's array, including invalid spaces
     * Set info to true to also print all information about Board
     * Note that this will be vertically mirrored compared to what user (printBoard) would see.
     */
    void printBoardArray(board::Board* board, bool info=true);
    /** 
     * Prints the entire Board in a pretty way
     * Set info to true to also print all information about Board
     * Set flipped to true to see board from black's perspective
     */
    void printBoard(board::Board* board, bool flipped=false, bool info=false);

    // gives the column given a 120 index
    // A is 0, B is 1, ..., H is 7
    inline unsigned int getColumn120(unsigned int index){
        return (index % 10) - 1;
    }

    // gives the row given a 120 index
    // 1 is 1, ..., 8 is 8
    inline unsigned int getRow120(unsigned int index){
        return (index / 10) - 1;
    }
}

#endif //PEGASUS_STUFF_UTILITYMETHODS_H
