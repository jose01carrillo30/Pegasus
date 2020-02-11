//
// Created by troyl on 2/5/2020.
//

#ifndef PEGASUS_STUFF_KNIGHTMOVEGEN_H
#define PEGASUS_STUFF_KNIGHTMOVEGEN_H

#include "constants.h"
#include <string>
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"
#include <vector>

namespace knightMoveGeneration{
    //width of board is 10
    const short adjacents[] = {-21, -19, -12, -8, 8, 12, 19, 21};

    // adds a UL representation of every possible move generated to Move* toPutMoves and returns the length added
    // knightPos in 120
    static std::vector<UL> generateKnightMoves(int8_t knightPos, board::Board* gameBoard){
        bool isWhite = utility::isWhite(gameBoard->chessboard[knightPos]);
        std::vector<UL> toPutMoves;

        //loop through adjacent pieces
        for(short adjacent : adjacents){
            //TODO: the "knightPos + adjecent" is being calculated twice, look into whether this or a temporary variable is faster
            unsigned short targetVal = gameBoard->chessboard[knightPos + adjacent];

            //ignore invalid spaces
            if(targetVal != board::INVALID){
                //white, check for ally piece, can't move onto them
                if(isWhite && utility::isBlack(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[knightPos], board::index120to64[knightPos + adjacent], board::WK, targetVal));
//                    startIndex++;
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && utility::isWhite(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[knightPos], board::index120to64[knightPos + adjacent], board::BK, targetVal));
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
