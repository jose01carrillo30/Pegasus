//
// Created by troyl on 2/7/2020.
//

#ifndef PEGASUS_STUFF_PAWNMOVEGEN_H
#define PEGASUS_STUFF_PAWNMOVEGEN_H

#include <string>
#include "board_object.hh"
#include "utilityMethods.hpp"
#include "move_representation.hpp"

#include <vector>

namespace pawnMoveGeneration{

    // adds a UL representation of every possible move generated to an new vector and returns the vector
    static std::vector<UL> generatePawnMoves(int8_t pawnPos, board::Board* gameBoard) {
        bool isWhite = utility::isWhite(gameBoard->chessboard[pawnPos]);
        std::vector<UL> toPutMoves;

        // double jump
        if(isWhite && (pawnPos > 30 && pawnPos < 39) && (gameBoard->chessboard[pawnPos+10] == EMPTY && gameBoard->chessboard[pawnPos+20] == EMPTY)){
            toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos+20], WP, EMPTY, false, true));
        }
        else if(!isWhite && (pawnPos > 80 && pawnPos < 89) && (gameBoard->chessboard[pawnPos-10] == EMPTY && gameBoard->chessboard[pawnPos-20] == EMPTY)){
            toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos-20], BP, EMPTY, false, true));
        }

        // Moving forward and capturing
        // white
        if(isWhite){
            // one step forward
            if(gameBoard->chessboard[pawnPos + 10] == EMPTY){
                // not promote
                if(pawnPos + 10 < 90) {
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos + 10], WP,EMPTY));
                }
                // promotion
                else{
                    for (int i = 0; i < 5; i++) {
                        toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos + 10], whitePieces[i], EMPTY, false, false, true));
                    }
                }
            }

            // capturing
            // left-up diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos + 9]) && utility::isBlack(gameBoard->chessboard[pawnPos + 9])){
                toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos + 9], WP,gameBoard->chessboard[pawnPos + 9]));
            }
            // right-up diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos + 11]) && utility::isBlack(gameBoard->chessboard[pawnPos + 11])){
                toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos + 11], WP,gameBoard->chessboard[pawnPos + 11]));
            }
        }
        // black
        else{
            // one step forward
            if(gameBoard->chessboard[pawnPos - 10] == EMPTY){
                // not promote
                if(pawnPos - 10 > 29) {
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos - 10], WP,EMPTY));
                }
                    // promotion
                else{
                    for (int i = 0; i < 5; i++) {
                        toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos - 10], blackPieces[i], EMPTY, false, false, true));
                    }
                }
            }

            // capturing
            // left-down diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos - 11]) && utility::isWhite(gameBoard->chessboard[pawnPos - 11])){
                toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos - 11], BP,gameBoard->chessboard[pawnPos - 11]));
            }
            // right-down diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos - 9]) && utility::isWhite(gameBoard->chessboard[pawnPos - 9])){
                toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos],index120to64[pawnPos - 9], BP,gameBoard->chessboard[pawnPos - 9]));
            }
        }

        // enPassant
        if(gameBoard->EP > -1){
            int column = utility::getColumn120(pawnPos);
            unsigned int row = utility::getRow120(pawnPos);

            // white enPassant: if in correct row
            if(isWhite && row == 5){
                // left-up diagonal
                if(gameBoard->EP - column == -1){
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos + 9], WP, BP, false, true));
                }
                // right-up diagonal
                if(gameBoard->EP - column == 1){
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos + 11], WP, BP, false, true));
                }
            }

            // black enPassant: if in correct row
            if(!isWhite && row == 4){
                // left-down diagonal
                if(gameBoard->EP - column == -1){
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos - 11], BP, WP, false, true));
                }
                // right-down diagonal
                if(gameBoard->EP - column == 1){
                    toPutMoves.push_back(move_rep::encodeMove(index120to64[pawnPos], index120to64[pawnPos - 9], BP, WP, false, true));
                }
            }
        }

        return toPutMoves;
    }
}

#endif //PEGASUS_STUFF_PAWNMOVEGEN_H
