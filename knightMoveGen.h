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

namespace knightMoveGeneration{
    //width of board is 10
    const short adjacents[] = {-21, -19, -12, -8, 8, 12, 19, 21};

    //returns a pointer to the array of possible moves, adds a UL representation of every possible move
    static Move* generateKnightMoves(int8_t knightPos, board::Board gameBoard, bool isWhite, Move* toPutMoves){
        //index in toPutMoves
        unsigned short index = 0;

        //loop through adjacent pieces
        for(short adjacent : adjacents){
            //TODO: the "knightPos + adjecent" is being calculated twice, look into whether this or a temporary variable is faster
            unsigned short targetVal = gameBoard.chessboard[knightPos + adjacent];

            //ignore invalid spaces
            if(targetVal != board::INVALID){
                //white, check for ally piece, can't move onto them
                if(isWhite && (targetVal < board::WP || targetVal > board::WK)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves[index] = move_rep::encodeMove(board::index120to64[knightPos], board::index120to64[knightPos + adjacent], board::WK, targetVal);
                    index++;
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && targetVal < board::BP){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves[index] = move_rep::encodeMove(board::index120to64[knightPos], board::index120to64[knightPos + adjacent], board::BK, targetVal);
                    index++;
                }
            }
        }
        return nullptr; //FIXME: added a temporary return so my compiler stops complaining to me. But this should still return something.
    }

    static void test(){
        //TODO:
    }
};

#endif //PEGASUS_STUFF_KNIGHTMOVEGEN_H
