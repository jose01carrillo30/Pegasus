//
// Created by troyl on 11/6/2019.
//

#ifndef PEGASUS_BOARD_OBJECT_H_DEPRICIATED
#define PEGASUS_BOARD_OBJECT_H_DEPRICIATED

#include <cstdint>
#include <string>
#include <iostream>

// THIS IS DEAD, USES BITBOARDS

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

    //TODO: do we want to generate these every time or just have them permanantly stored?
    ULL generateWhiteBoard(){
        ULL ans = bitboards[WP];
        for(int i = 1; i < BP; i++){
            ans |= bitboards[i];
        }
        return ans;
    }
    ULL generateBlackBoard(){
        ULL ans = bitboards[BP];
        for(int i = BP+1; i < BK+1; i++){
            ans |= bitboards[i];
        }
        return ans;
    }
};

#endif //PEGASUS_BOARD_OBJECT_H_DEPRICIATED
