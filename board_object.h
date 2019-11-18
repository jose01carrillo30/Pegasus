//
// Created by troyl on 11/15/2019.
//

#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>

namespace board
{
    //TODO: Is anyone using the ., x, P, N, etc for their code? I'm going to change it to a standard 0, 1, 2, 3 enum for use with indexing - Troy
//    enum : unsigned char {EMPTY='.', INVALID='x', WP='P', WN='N', WB='B', WR='R', WQ='Q', WK='K', BP='p', BN='n', BB='b', BR='r', BQ='q', BK='k'};
    enum : unsigned char {EMPTY, INVALID, WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK};

    class Board {
        public:
            unsigned char chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            short EP; // en passant column / position?
            short materialWhite, materialBlack; // material scores for white and black
            short movesSinceLastCapture; // 50 move rule
            uint64_t hashCode;

            /** 
             * Creates a new board. Set startingPosition to true to initialize Board to the starting position (all members initialized)
             * Set empty to true to initialize Board as empty (chessboard[] only initialized) 
             */
            Board(bool startingPosition=false, bool empty=false) {
                if (startingPosition) {
                    const unsigned char startChessboard[] = {
                //                  A        B        C        D        E        F        G        H
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, BR,      BN,      BB,      BQ,      BK,      BB,      BN,      BR,      INVALID,   // 8
                        INVALID, BP,      BP,      BP,      BP,      BP,      BP,      BP,      BP,      INVALID,   // 7
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 6
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 5
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 4
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 3
                        INVALID, WP,      WP,      WP,      WP,      WP,      WP,      WP,      WP,      INVALID,   // 2
                        INVALID, WR,      WN,      WB,      WQ,      WK,      WB,      WN,      WR,      INVALID,   // 1
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                    };
                    // idk if there is a better way to do this
                    // initialize chessboard to startChessboard
                    for (size_t i = 0; i < 120; i++) {
                        chessboard[i] = startChessboard[i];
                    }
                    CWK = true; CWQ = true; CBK = true; CBQ = true;
                    EP = 0; //TODO: is this an appropriate value for no enpasant?
                    materialBlack = 
                    materialWhite = materialBlack;
                    movesSinceLastCapture = 0;
                    // hashCode = this->hash(); //TODO: 
                } else if (empty) {
                    const unsigned char startChessboard[] = {
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                    };
                    for (size_t i = 0; i < 120; i++) {
                        chessboard[i] = startChessboard[i];
                    }
                }
            }
    };
}

#endif //PEGASUS_STUFF_BOARD_OBJECT_H
