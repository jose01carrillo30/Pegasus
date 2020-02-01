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
                    //TODO: Note that if we go ahead with making EMPTY the "capturedPiece" default (no capture), then this branch (target...)? x : y is unnecessary
                    //TODO: check enPassant and promote number
                    toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, kingPos + adjacent, 0u, 0u, (targetVal != board::EMPTY)? targetVal : board::EMPTY, board::EMPTY, board::WK);
                    index++;
                }
                //black, check for ally piece, can't move onto them
                else if(!isWhite && targetVal < board::BP){
                    //TODO: Note that if we go ahead with making EMPTY the "capturedPiece" default (no capture), then this branch (target...)? x : y is unnecessary
                    //TODO: check enPassant and promote number
                    toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, kingPos + adjacent, 0u, 0u, (targetVal != board::EMPTY)? targetVal : board::EMPTY, board::EMPTY, board::BK);
                    index++;
                }
            }
        }
        //white
        if(isWhite){
            //left (queen) side castle
            if(gameBoard.CWQ && gameBoard.chessboard[92] == board::EMPTY && gameBoard.chessboard[93] == board::EMPTY && gameBoard.chessboard[94] == board::EMPTY){
                //TODO: are we doing 64 or 120 for spot indexes?
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 93, 1u, 0u, board::EMPTY, board::EMPTY, board::WK);
                index++;
            }
            //right (king) side castle
            if(gameBoard.CWK && gameBoard.chessboard[96] == board::EMPTY && gameBoard.chessboard[97] == board::EMPTY){
                //TODO: are we doing 64 or 120 for spot indexes?
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 97, 2u, 0u, board::EMPTY, board::EMPTY, board::WK);
//                index++;
            }
        }
        //black
        else{
            //left (queen) side castle
            if(gameBoard.CBQ && gameBoard.chessboard[22] == board::EMPTY && gameBoard.chessboard[23] == board::EMPTY && gameBoard.chessboard[24] == board::EMPTY){
                //TODO: are we doing 64 or 120 for spot indexes?
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 23, 1u, 0u, board::EMPTY, board::EMPTY, board::BK);
                index++;
            }
            //right (king) side castle
            if(gameBoard.CBK && gameBoard.chessboard[26] == board::EMPTY && gameBoard.chessboard[27] == board::EMPTY){
                //TODO: are we doing 64 or 120 for spot indexes?
                //TODO: check enPassant and promote number
                toPutMoves[index] = MoveRepresentation::encodeMove(kingPos, 27, 2u, 0u, board::EMPTY, board::EMPTY, board::BK);
//                index++;
            }
        }
        return nullptr; //TODO: added a temporary return so my compiler stops complaining to me
    }

    static void test(){

    }
};

#endif //PEGASUS_STUFF_KINGMOVEGEN_H
