//
// Created by troyl on 11/13/2019.
//

#ifndef PEGASUS_STUFF_UTILITYMETHODS_H
#define PEGASUS_STUFF_UTILITYMETHODS_H

#include "board_object_DEPRECIATED.h"
//#include "board_object.h"
#include <iostream>

namespace utility{
    // A utility function to print out a single bitboard:
    void printBitboard(ULL board) {
        // Note: this print function is weird because it uses the Little-Endian Rank-File Mapping:
        // Iterate through all 64 bits:
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // THE CURRENT BIT IS (8i + j)
                // If the current bit is 1, print "1 ". Otherwise, print "0 ":
                std::cout << (((board >> (8*i + j)) & 1) ? "1 " : ". ");
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    void printInfo(board::Board* board, int lineNum) {
        switch (lineNum)
        {
        case 0:
            std::cout << "hash code: " << board->hashCode;
            break;
        case 1:
            std::cout << "white castle rights: {king: " << board->CWK << " queen: " << board->CWQ << "}";
            break;
        case 2:
            std::cout << "black castle rights: {king: " << board->CBK << " queen: " << board->CBQ << "}";
            break;
        case 3:
            std::cout << "Moves since last capture: " << board->movesSinceLastCapture;
            break;
        case 4:
            std::cout << "En Passant: " << board->EP;
            break;
        case 5:
            std::cout << "Material: {White: " << board->materialWhite << " Black: " << board->materialBlack << "}";
            break;
        default:
            break;
        }
    }

    /** 
     * Prints the entire Board's array, including invalid spaces
     * Set info to true to also print all information about Board
     */
    void printBoardArray(board::Board* board, bool info=true) {
        for (size_t i = 0; i < 120; i++) {
            std::cout << board->chessboard[i] << " ";
            if(i % 10 == 9) {
                if (info) printInfo(board, i/10 - 2);
                std::cout << std::endl;
            }
        }
    }
    /** 
     * Prints the entire Board in a pretty way
     * Set info to true to also print all information about Board
     */
    void printBoard(board::Board* board, bool info=true) {
        std::cout << "  +-----------------+" << std::endl;
        for (size_t r = 0; r < 8; r++) {
            std::cout << 8-r << " | ";
            for (size_t c = 0; c < 8; c++) { 
                std::cout << board->chessboard[21 + 10*r + c] << " ";
            }
            std::cout << "|  ";
            if (info) printInfo(board, r);
            std::cout << std::endl;
        }
        std::cout << "  +-----------------+" << std::endl;
        std::cout << "    a b c d e f g h  " << std::endl;
    }
}

#endif //PEGASUS_STUFF_UTILITYMETHODS_H
