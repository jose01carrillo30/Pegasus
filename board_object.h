#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>

namespace board {
    // White is even, black is odd, and all pieces are less than EMPTY
    // For example, WP means White Pawn, BN mean Black kNight
    enum : unsigned char {WP, BP, WR, BR, WN, BN, WB, BB, WQ, BQ, WK, BK, EMPTY, INVALID};

    class Board {
        public:
            // independent fields, provide necessary information about board
            unsigned char chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            short EP; // en passant column / position?
            short movesSinceLastCapture; // 50 move rule
            bool turnWhite; // whose turn it is
            // dependent fields, store information about board that is derived from independent fields
            short materialWhite, materialBlack; // material scores for white and black
            uint64_t hashCode;

            /** 
             * Creates a new board. Set startingPosition to true to initialize Board to the starting position (all members initialized)
             * Set empty to true to initialize Board as empty (chessboard[] only initialized) 
             */
            Board(bool startingPosition=false, bool empty=false) {
                if (startingPosition) { //TODO: just use Fenn string converter instead once that is completed
                    const unsigned char startChessboard[] = {
                //                  A        B        C        D        E        F        G        H
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID, INVALID,
                        INVALID, WR,      WN,      WB,      WQ,      WK,      WB,      WN,      WR,      INVALID,   // 1
                        INVALID, WP,      WP,      WP,      WP,      WP,      WP,      WP,      WP,      INVALID,   // 2
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 3
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 4
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 5
                        INVALID, EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   EMPTY,   INVALID,   // 6
                        INVALID, BP,      BP,      BP,      BP,      BP,      BP,      BP,      BP,      INVALID,   // 7
                        INVALID, BR,      BN,      BB,      BQ,      BK,      BB,      BN,      BR,      INVALID,   // 8
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
                    materialBlack = 0; //TODO: what is an appropriate value?
                    materialWhite = materialBlack;
                    movesSinceLastCapture = 0;
                    turnWhite = true;
                    // hashCode = this->hash(); //TODO: 
                } else if (empty) {
                    const unsigned char startChessboard[] = { //TODO: replace this mess with FEN imports
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

            /** Boards are equal if all independent fields are equal */
            bool operator==(const Board& other) const {
                if (CBK != other.CBK || 
                    CBQ != other.CBQ || 
                    CWK != other.CWK || 
                    CWQ != other.CWQ ||
                    EP != other.EP ||
                    turnWhite != other.turnWhite ||
                    movesSinceLastCapture != other.movesSinceLastCapture) {
                    return false;
                }
                for (int i = 0; i < 120; i++) {
                    if (chessboard[i] != other.chessboard[i]) {
                        return false;
                    }
                }
                return true;
            }

    };
}

#endif //PEGASUS_STUFF_BOARD_OBJECT_H
