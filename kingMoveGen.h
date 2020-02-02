//
// Created by troyl on 11/18/2019.
//

#ifndef PEGASUS_STUFF_KINGMOVEGEN_H
#define PEGASUS_STUFF_KINGMOVEGEN_H

#include <string>
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

namespace kingMoveGeneration{
    //width of board is 10
    const short adjacents[] = {-11, -10, -9, -1, 1, 9, 10, 11};

    //returns a pointer to the array of possible moves, adds a UL representation of every possible move
    static Move* generateKingMoves(int8_t kingPos, board::Board gameBoard, bool isWhite, Move* toPutMoves){
        //index in toPutMoves
        unsigned short index = 0;

        //loop through adjacent pieces
        for(short adjacent : adjacents){
            //TODO: the "kingPos + adjecent" is being calculated twice, look into whether this or a temporary variable is faster
            unsigned short targetVal = gameBoard.chessboard[kingPos + adjacent];

            //ignore invalid spaces
            if(targetVal != board::INVALID){
                //white, check for ally piece, can't move onto them
                if(isWhite && (targetVal < board::WP || targetVal > board::WK)){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    //TODO: check enPassant and promote number
                    toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, kingPos + adjacent, board::WK, targetVal);
                    index++;
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && targetVal < board::BP){
                    // Assumes no capture is represented by capturedPiece=EMPTY
                    //TODO: check enPassant and promote number
                    toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, kingPos + adjacent, board::BK, targetVal);
                    index++;
                }
            }
        }
        // White
        if(isWhite){
            //left (queen/long) side castle
            // TODO: magic numbers (btw we are using 120 index)
            if(gameBoard.CWQ && gameBoard.chessboard[92] == board::EMPTY && gameBoard.chessboard[93] == board::EMPTY && gameBoard.chessboard[94] == board::EMPTY){
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 93, board::WK, board::EMPTY, MoveRepresentation::LONG_CASTLE);
                index++;
            }
            //right (king/short) side castle
            if(gameBoard.CWK && gameBoard.chessboard[96] == board::EMPTY && gameBoard.chessboard[97] == board::EMPTY){
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 97, board::WK, board::EMPTY, MoveRepresentation::SHORT_CASTLE);
//                index++;
            }
        }
        // Black
        else{
            //left (queen/long) side castle
            if(gameBoard.CBQ && gameBoard.chessboard[22] == board::EMPTY && gameBoard.chessboard[23] == board::EMPTY && gameBoard.chessboard[24] == board::EMPTY){
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 23, board::BK, board::EMPTY, MoveRepresentation::LONG_CASTLE);
                index++;
            }
            //right (king/short) side castle
            if(gameBoard.CBK && gameBoard.chessboard[26] == board::EMPTY && gameBoard.chessboard[27] == board::EMPTY){
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 27, board::BK, board::EMPTY, MoveRepresentation::SHORT_CASTLE);
//                index++;
            }
        }
        return nullptr; //FIXME: added a temporary return so my compiler stops complaining to me. But this should still return something.
    }

    static void test(){
        //TODO:
    }
};

#endif //PEGASUS_STUFF_KINGMOVEGEN_H
