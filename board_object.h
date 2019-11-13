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

#endif //PEGASUS_BOARD_OBJECT_H
