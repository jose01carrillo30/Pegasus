//
// Created by troyl on 2/7/2020.
//

#ifndef PEGASUS_STUFF_PAWNMOVEGEN_H
#define PEGASUS_STUFF_PAWNMOVEGEN_H

#include <string>
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

#include <vector>

namespace pawnMoveGeneration{

    // adds a UL representation of every possible move generated to Move* toPutMoves and returns the length added
    static std::vector<UL> generatePawnMoves(int8_t pawnPos, board::Board* gameBoard) {
        bool isWhite = utility::isWhite(gameBoard->chessboard[pawnPos]);
        std::vector<UL> toPutMoves;

        // double jump
        if(isWhite && (pawnPos > 30 && pawnPos < 39) && (gameBoard->chessboard[pawnPos+10] == board::EMPTY && gameBoard->chessboard[pawnPos+20] == board::EMPTY)){
            toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos+20], board::WP, board::EMPTY, false, true));
        }
        else if(!isWhite && (pawnPos > 80 && pawnPos < 89) && (gameBoard->chessboard[pawnPos-10] == board::EMPTY && gameBoard->chessboard[pawnPos-20] == board::EMPTY)){
            toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos-20], board::BP, board::EMPTY, false, true));
        }

        // Moving forward and capturing
        // white
        if(isWhite){
            // one step forward
            if(gameBoard->chessboard[pawnPos + 10] == board::EMPTY){
                // not promote
                if(pawnPos + 10 < 90) {
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos + 10], board::WP,board::EMPTY));
                }
                // promotion
                else{
                    for (int i = 0; i < 5; i++) {
                        toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos + 10], board::whitePieces[i], board::EMPTY, false, false, true));
                    }
                }
            }

            // capturing
            // left-up diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos + 9]) && utility::isBlack(gameBoard->chessboard[pawnPos + 9])){
                toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos + 9], board::WP,gameBoard->chessboard[pawnPos + 9]));
            }
            // right-up diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos + 11]) && utility::isBlack(gameBoard->chessboard[pawnPos + 11])){
                toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos + 11], board::WP,gameBoard->chessboard[pawnPos + 11]));
            }
        }
        // black
        else{
            // one step forward
            if(gameBoard->chessboard[pawnPos - 10] == board::EMPTY){
                // not promote
                if(pawnPos - 10 > 29) {
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos - 10], board::WP,board::EMPTY));
                }
                    // promotion
                else{
                    for (int i = 0; i < 5; i++) {
                        toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos - 10], board::blackPieces[i], board::EMPTY, false, false, true));
                    }
                }
            }

            // capturing
            // left-down diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos - 11]) && utility::isWhite(gameBoard->chessboard[pawnPos - 11])){
                toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos - 11], board::BP,gameBoard->chessboard[pawnPos - 11]));
            }
            // right-down diagonal
            if(utility::isPiece(gameBoard->chessboard[pawnPos - 9]) && utility::isWhite(gameBoard->chessboard[pawnPos - 9])){
                toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos],board::index120to64[pawnPos - 9], board::BP,gameBoard->chessboard[pawnPos - 9]));
            }
        }

        // TODO: enPassant
        // enPassant
        if(gameBoard->EP > -1){
            int column = utility::getColumn120(pawnPos);
            unsigned int row = utility::getRow120(pawnPos);

            // white enPassant: if in correct row
            if(isWhite && row == 5){
                // left-up diagonal
                if(gameBoard->EP - column == -1){
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos + 9], board::WP, board::BP, false, true));
                }
                // right-up diagonal
                if(gameBoard->EP - column == 1){
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos + 11], board::WP, board::BP, false, true));
                }
            }

            // black enPassant: if in correct row
            if(!isWhite && row == 4){
                // left-down diagonal
                if(gameBoard->EP - column == -1){
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos - 11], board::BP, board::WP, false, true));
                }
                // right-down diagonal
                if(gameBoard->EP - column == 1){
                    toPutMoves.push_back(move_rep::encodeMove(board::index120to64[pawnPos], board::index120to64[pawnPos - 9], board::BP, board::WP, false, true));
                }
            }
        }

        return toPutMoves;
    }
}

#endif //PEGASUS_STUFF_PAWNMOVEGEN_H
