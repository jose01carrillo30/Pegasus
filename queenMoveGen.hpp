//
// Created by troyl on 2/26/2020.
//

#ifndef PEGASUS_STUFF_QUEENMOVEGEN_H
#define PEGASUS_STUFF_QUEENMOVEGEN_H

#include <string>
#include "board_object.hh"
#include "utilityMethods.hpp"
#include "move_representation.hpp"

#include <vector>

namespace queenMoveGeneration{
    // width of board is 10
    // clockwise from positive x: bot right, bot, bot left, left, top left, top, top right, right
    const short steps[] = {-9, -10, -11, -1, 9, 10, 11, 1};

    // adds a UL representation of every possible move generated to an new vector and returns the vector
    static std::vector<UL> generateQueenMoves(int8_t queenPos, board::Board* gameBoard) {
        short myPiece = gameBoard->chessboard[queenPos];
        bool isWhite = utility::isWhite(myPiece);
        std::vector<UL> toPutMoves;

        // loop through steps
        for (short step : steps) {
            // for each step, loop infinitely until find an invalid or blocking piece
            unsigned short stepNum = 1;
            unsigned short targetVal = gameBoard->chessboard[queenPos + steps[step]];
            while(targetVal == EMPTY){
                // can move to any position along the ray
                toPutMoves.push_back(move_rep::encodeMove(queenPos, queenPos + (steps[step] * stepNum), myPiece));

                // calculate the next move
                stepNum++;
                targetVal = gameBoard->chessboard[queenPos + (steps[step] * stepNum)];
            }

            // upon exit from while loop targetVal should be either INVALID or a piece
            // take out cases where the edge of the board is reached and/or an ally piece is blocking the way
            if(targetVal == INVALID || utility::isWhite(targetVal) == isWhite){
                continue;
            }
            // enemy piece blocking the way
            toPutMoves.push_back(move_rep::encodeMove(queenPos, queenPos + (steps[step] * stepNum), myPiece, targetVal));
        }

        // return the vector generated
        return toPutMoves;
    }
}

#endif //PEGASUS_STUFF_QUEENMOVEGEN_H
