//
// Created by troyl on 11/15/2019.
//

#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>

namespace board
{
    enum : unsigned char {EMPTY, INVALID, WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

    struct Board {
        unsigned short chessboard[120];
        bool CWK, CWQ, CBK, CBQ; // castle rights
        short EP; // en passant column / position?
        short materialWhite, materialBlack; // material scores for white and black
        short movesSinceLastCapture; // 50 move rule
        uint64_t hashCode;
    };
}

#endif //PEGASUS_STUFF_BOARD_OBJECT_H
