#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>
#include <map>

namespace board {
    // White is even, black is odd, and all pieces are less than EMPTY
    // For example, WP means White Pawn, BN mean Black kNight
    enum : unsigned char {WP, BP, WR, BR, WN, BN, WB, BB, WQ, BQ, WK, BK, EMPTY, INVALID};

    // // mapping 120 indexes to 64
    // const std::map<int, int> index120to64 = {
    //          {91, 56}, {92, 57}, {93, 58}, {94, 59}, {95, 60}, {96, 61}, {97, 62}, {98, 63}
    //         ,{81, 48}, {82, 49}, {83, 50}, {84, 51}, {85, 52}, {86, 53}, {87, 54}, {88, 55}
    //         ,{71, 40}, {72, 41}, {73, 42}, {74, 43}, {75, 44}, {76, 45}, {77, 46}, {78, 47}
    //         ,{61, 32}, {62, 33}, {63, 34}, {64, 35}, {65, 36}, {66, 37}, {67, 38}, {68, 39}
    //         ,{51, 24}, {52, 25}, {53, 26}, {54, 27}, {55, 28}, {56, 29}, {57, 30}, {58, 31}
    //         ,{41, 16}, {42, 17}, {43, 18}, {44, 19}, {45, 20}, {46, 21}, {47, 22}, {48, 23}
    //         ,{31, 8},  {32, 9},  {33, 10}, {34, 11}, {35, 12}, {36, 13}, {37, 14}, {38, 15}
    //         ,{21, 0},  {22, 1},  {23, 2},  {24, 3},  {25, 4},  {26, 5},  {27, 6},  {28, 7} };
    // // and vice versa
    // std::map<int, int> reverseMap(std::map<int, int> input){
    //     std::map<int, int> newMap;
    //     for(std::map<int, int>::iterator it = input.begin(); it != input.end(); it++){
    //         newMap.insert({it->second, it->first});
    //     }
    //     return newMap;
    // }
    // const std::map<int, int> index64to120 = reverseMap(index120to64);

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
            // independent fields, provide necessary information about board
            unsigned char chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            char EP; // en passant rights: what column did a double jump just occur? -1 if no double jump. 
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
