//
// Created by troyl on 11/8/2019.
//

#ifndef PEGASUS_STUFF_KING_MOVE_GEN_H
#define PEGASUS_STUFF_KING_MOVE_GEN_H

#include <string>
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

namespace kingMoveGeneration{
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    1 1 1 0 0 0 0 0
    //    1 0 1 0 0 0 0 0
    //    1 1 1 0 0 0 0 0
    // assuming bottom left is 0
    const ULL kingMoveMask = 460039LL;
    const short adjacents[] = {-9, -8, -7, -1, 1, 7, 8, 9};

    // for use in removing wrapping problems
    const ULL leftBoardWipe = 17361641481138401520LL;
    const ULL rightBoardWipe = leftBoardWipe >> 4u;

    //returns a bitboard of possible moves, adds a UL representation of every possible move
    static ULL generateKingMoves(int8_t kingPos, Board board, bool isWhite, UL* toPutMoves){
        //generate the ally/enemy boards
        ULL allyBoard;
        ULL enemyBoard;
        if(isWhite){
            allyBoard = board.generateWhiteBoard();
            enemyBoard = board.generateBlackBoard();
        }
        else{
            allyBoard = board.generateBlackBoard();
            enemyBoard = board.generateWhiteBoard();
        }
        ULL fullBoard = allyBoard | enemyBoard;

        //mask starts at position 9
        int8_t initialMaskShift = kingPos - 9;
        ULL possMoves;

        //can't bitshift by a negative number
        if(initialMaskShift >= 0){
            possMoves = kingMoveMask << initialMaskShift;
        }
        else{
            possMoves = kingMoveMask >> -(initialMaskShift);
        }

        //take care of wrapping problems
        if(kingPos % 8 == 7){
            possMoves &= leftBoardWipe;
        }
        else if(kingPos % 8 == 0){
            possMoves &= rightBoardWipe;
        }

        //can't move onto the square of an ally
        possMoves ^= (allyBoard & possMoves);

        //create the string representations and store them
        if(toPutMoves != nullptr){
            //check adjacent squares and create the move representations
            int8_t indexArr = 0;
            for(int i = 0; i < 8; i++){
                int8_t targetBit = kingPos + adjacents[i];

                //check for out of bounds and whether this is a valid move
                if(targetBit >= 0 && (possMoves >> targetBit & 1u)){
                    //check for enemy piece
                    if(enemyBoard >> targetBit & 1u){
                        //find out which piece it is
                        int8_t piece = -1;
                        for(int k = 0; k < WK; k++){
//                            (isWhite)? BP : WP
                            if(board.bitboards[(isWhite)? BP+k : WP+k] >> targetBit){
                                piece = (isWhite)? BP+k : WP+k;
                            }
                        }
                        //TODO: check to see if these values, particularly the 0u's, are correct
                        toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, targetBit, 0u, 0u, piece, 0u, (isWhite)? WK : BK);
                        indexArr++;
                    }

                    //else it is a regular movement
                    else{
                        //TODO: check to see if these values, particularly the 0u's, are correct
                        toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, targetBit, 0u, 0u, 0u, 0u, (isWhite)? WK : BK);
                        indexArr++;
                    }
                }
            }

            //TODO: Check for castle
            //Notes: cannot capture while castling
            //White
            if(isWhite){
                //White queen-side (left) castle: check bits 1-3: 1110
                if(board.CWQ && !(fullBoard & 14u)){
                    //TODO: check to see if these values, particularly the 0u's and the 1u for castle, are correct
                    //TODO: update the board's castling rights either here or in the move processor
                    toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, 2u, 1u, 0u, 0u, 0u, WK);
                    indexArr++;
                }
                //White king-side (right) castle: check bits 5-6: 1100000
                if(board.CWK && !(fullBoard & 96u)){
                    //TODO: check to see if these values, particularly the 0u's and the 0u for castle, are correct
                    //TODO: update the board's castling rights either here or in the move processor
                    toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, 6u, 0u, 0u, 0u, 0u, WK);
                    //indexArr++;
                }
            }
            else{
                //Black queen-side (left) castle: check bits 57-59: 1110 00000000 00000000 00000000 00000000 00000000 00000000 00000000
                if(board.CWQ && !(fullBoard & 1008806316530991104u)){
                    //TODO: check to see if these values, particularly the 0u's and the 3u for castle, are correct
                    //TODO: update the board's castling rights either here or in the move processor
                    toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, 58u, 3u, 0u, 0u, 0u, BK);
                    indexArr++;
                }
                //Black queen-side (left) castle: check bits 61-62: 1100000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
                if(board.CWQ && !(fullBoard & 6917529027641081856u)){
                    //TODO: check to see if these values, particularly the 0u's and the 2u for castle, are correct
                    //TODO: update the board's castling rights either here or in the move processor
                    toPutMoves[indexArr] = MoveRepresentation::encodeMove(kingPos, 62u, 2u, 0u, 0u, 0u, BK);
                    //indexArr++;
                }
            }
        }
        return possMoves;
    }

    static void test(){
//        std::string ans;

        std::cout << "1 Mask:\n";
        utility::printBitboard(kingMoveMask);
        std::cout << "\n";

//        std::cout << "2 Right:\n";
//        utility::printBitboard(rightBoardWipe);
//        std::cout << "\n";
//
        std::cout << "3 Left:\n";
        utility::printBitboard(leftBoardWipe);
        std::cout << "\n";
//
//        std::cout << "4 Mask leftshifted by 2:\n";
//        utility::printBitboard(kingMoveMask << 2);
//        std::cout << "\n";

        std::cout << "5 Mask rightshifted by 8:\n";
        utility::printBitboard(kingMoveMask >> 8);
        std::cout << "\n";

        //TODO: Init Me
        Board testBoard;

        std::cout << "6:\n";
        utility::printBitboard(generateKingMoves(9, testBoard, true, nullptr));
        std::cout << "\n";
    }
};

#endif //PEGASUS_STUFF_KING_MOVE_GEN_H
