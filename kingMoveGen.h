//
// Created by troyl on 11/18/2019.
//

#ifndef PEGASUS_STUFF_KINGMOVEGEN_H
#define PEGASUS_STUFF_KINGMOVEGEN_H

#include <string>
#include <vector>

#include "constants.h"
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

namespace kingMoveGeneration{
    // width of board is 10
    // clockwise from positive x axis
    const short adjacents[] = {-11, -10, -9, -1, 1, 9, 10, 11};

    // adds a UL representation of every possible move generated to an new vector and returns the vector
    // kingPos is in 120
    static std::vector<UL> generateKingMoves(int8_t kingPos, board::Board* gameBoard){
        bool isWhite = utility::isWhite(gameBoard->chessboard[kingPos]);
        std::vector<UL> toPutMoves;

        //loop through adjacent pieces
        for(short adjacent : adjacents){
            //TODO: the "kingPos + adjecent" is being calculated twice, look into whether this or a temporary variable is faster
            unsigned short targetVal = gameBoard->chessboard[kingPos + adjacent];

            //ignore invalid spaces
            if(targetVal != INVALID){
                //white, check for ally piece, can't move onto them
                if(isWhite && utility::isBlack(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[kingPos], index120to64[kingPos + adjacent], WK, targetVal));
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && utility::isWhite(targetVal)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[kingPos], index120to64[kingPos + adjacent], BK, targetVal));
                }
            }
        }
        // White
        if(isWhite){
            //left (queen/long) side castle
            if(gameBoard->CWQ && gameBoard->chessboard[22] == EMPTY && gameBoard->chessboard[23] == EMPTY && gameBoard->chessboard[24] == EMPTY){
                toPutMoves.push_back(move_rep::encodeMove(index120to64[kingPos], 23, WK, EMPTY, 1u));
            }
            //right (king/short) side castle
            if(gameBoard->CWK && gameBoard->chessboard[26] == EMPTY && gameBoard->chessboard[27] == EMPTY){
                toPutMoves.push_back(move_rep::encodeMove(kingPos, 27, WK, EMPTY, 1u));
            }
        }
        // Black
        else{
            //left (queen/long) side castle
            if(gameBoard->CBQ && gameBoard->chessboard[92] == EMPTY && gameBoard->chessboard[93] == EMPTY && gameBoard->chessboard[94] == EMPTY){
                toPutMoves.push_back(move_rep::encodeMove(kingPos, 93, BK, EMPTY, 1u));
            }
            //right (king/short) side castle
            if(gameBoard->CBK && gameBoard->chessboard[96] == EMPTY && gameBoard->chessboard[97] == EMPTY){
                toPutMoves.push_back(move_rep::encodeMove(kingPos, 97, BK, EMPTY, 1u));
            }
        }
        return toPutMoves;
    }

    static void test(){
        //TODO:
    }
};

#endif //PEGASUS_STUFF_KINGMOVEGEN_H
