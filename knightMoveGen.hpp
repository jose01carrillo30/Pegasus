//
// Created by troyl on 2/5/2020.
//

#ifndef PEGASUS_STUFF_KNIGHTMOVEGEN_H
#define PEGASUS_STUFF_KNIGHTMOVEGEN_H

#include "constants.hh"
#include <string>
#include "board_object.hh"
#include "utilityMethods.hh"
#include "move_representation.hpp"
#include <vector>

namespace knightMoveGeneration{
    // width of board is 10
    // clockwise from positive x axis
    const short adjacents[] = {-12, -21, -19, -8, 8, 19, 12, 21};

    // adds a UL representation of every possible move generated to an new vector and returns the vector
    // knightPos in 120
    static std::vector<UL> generateKnightMoves(int8_t knightPos, board::Board* gameBoard){
        bool isWhite = utility::isWhite(gameBoard->chessboard[knightPos]);
        std::vector<UL> toPutMoves;

        //loop through adjacent pieces
        for(short adjacent : adjacents){
            //TODO: the "knightPos + adjecent" is being calculated twice, look into whether this or a temporary variable is faster
            unsigned short targetVal = gameBoard->chessboard[knightPos + adjacent];

            //ignore invalid spaces
            if(targetVal != INVALID){
                //white, check for ally piece, can't move onto them
                if(isWhite && utility::isBlack(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[knightPos], index120to64[knightPos + adjacent], WK, targetVal));
//                    startIndex++;
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && utility::isWhite(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[knightPos], index120to64[knightPos + adjacent], BK, targetVal));
//                    startIndex++;
                }
            }
        }
        return toPutMoves;
    }

    static void test(){
        //TODO:
    }
};

#endif //PEGASUS_STUFF_KNIGHTMOVEGEN_H
