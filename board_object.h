//
// Created by troyl on 11/6/2019.
//

#ifndef PEGASUS_BOARD_OBJECT_H
#define PEGASUS_BOARD_OBJECT_H

#include <cstdint>
#include <string>
#include <iostream>

typedef uint64_t ULL; // ensures ULL is 64 bits

enum : unsigned char {WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

struct Board {
    ULL bitboards[12];
    bool CWK, CWQ, CBK, CBQ; // castle rights
    short kings; // king locations: kings = WK*64 + BK
    short EP; // en passant column / position?
    short materialWhite, materialBlack; // material scores for white and black
    short movesSinceLastCapture; // 50 move rule
    ULL hashCode;
};

// Helper method which prints the bits of a single 64 bit number
static void printBits(ULL toPrint){
    std::string ans;
    ULL mask = 1u;
    for(int i = 63; i >= 0; i--){
//        ans += std::to_string((toPrint >> i) & mask) + " ";
        std::cout << std::to_string((toPrint >> i) & mask) + " ";
        if(i % 8 == 0){
//            ans += "\n";
            std::cout << "\n";
        }
    }
//    return ans;
}

#endif //PEGASUS_BOARD_OBJECT_H
