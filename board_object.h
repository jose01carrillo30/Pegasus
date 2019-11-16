//
// Created by troyl on 11/15/2019.
//

#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>

namespace board
{
    enum : unsigned char {EMPTY='.', INVALID='x', WP='P', WN='N', WB='B', WR='R', WQ='Q', WK='K', BP='p', BN='n', BB='b', BR='r', BQ='q', BK='k'};

    class Board {
        public:
            unsigned char chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            short EP; // en passant column / position?
            short materialWhite, materialBlack; // material scores for white and black
            short movesSinceLastCapture; // 50 move rule
            uint64_t hashCode;

            // Constructor for the starting position board
            Board() {
                const unsigned char startChessboard[] = {
                    INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                    INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                    INVALID, BR,      BN,      BB,      BQ,      BK,      BB,      BN,      BR,      INVALID,
                    INVALID, BP,      BP,      BP,      BP,      BP,      BP,      BP,      BP,      INVALID,
                    INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                    INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                    INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                    INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,
                    INVALID, WP,      WP,      WP,      WP,      WP,      WP,      WP,      WP,      INVALID,
                    INVALID, WR,      WN,      WB,      WQ,      WK,      WB,      WN,      WR,      INVALID,
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
            }
    };
}

#endif //PEGASUS_STUFF_BOARD_OBJECT_H
