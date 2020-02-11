#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include "constants.h"
#include <cstdint>
#include <stack>

namespace board {
    // White is even, black is odd, and all pieces are less than EMPTY
    // For example, WP means White Pawn, BN mean Black kNight
    enum : unsigned char {WP, BP, WR, BR, WN, BN, WB, BB, WQ, BQ, WK, BK, EMPTY, INVALID};

    const unsigned char blackPieces[6] = {BP, BR, BN, BB, BQ, BK};
    const unsigned char whitePieces[6] = {WP, WR, WN, WB, WQ, WK};

    const char index120to64[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7, -1,
        -1,  8,  9, 10, 11, 12, 13, 14, 15, -1,
        -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
        -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
        -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
        -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
        -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
        -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
    const char index64to120[] = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
    };

    class Board {
        public:
            /* ------- independent fields, provide necessary information about board ------- */
            unsigned char chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            char EP; // en passant rights: what column did a double jump just occur? -1 if no double jump. 
            short movesSinceLastCapture; // 50 move rule
            bool turnWhite; // whose turn it is
            std::stack<Move> moveHistory; // list of moves applied to starting FEN.

            /* ------- dependent fields, store information about board that is derived from independent fields -------- */
            short materialWhite, materialBlack; // material scores for white and black
            uint64_t hashCode;
            unsigned char whitePieceLocations[16]; // TODO: I am not willing to initialize these by hand, so I will wait until the FEN importer can before I implement code for this in moveMaker
            unsigned char blackPieceLocations[16];

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
                    EP = -1; // No en passant / double jump
                    materialBlack = STARTING_MATERIAL;
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

            /** 
             * Boards are equal if all independent fields except moveHistory are equal. 
             * Note that comparing the hashes is MUCH faster that this, and should be used to compare boards
             * for most practical purposes. Really, this is just here to test if the hash function is working.
             */
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
