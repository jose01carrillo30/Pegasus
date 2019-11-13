//
// Created by troyl on 11/13/2019.
//

#ifndef PEGASUS_STUFF_UTILITYMETHODS_H
#define PEGASUS_STUFF_UTILITYMETHODS_H

#include "board_object.h"
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
}

#endif //PEGASUS_STUFF_UTILITYMETHODS_H
