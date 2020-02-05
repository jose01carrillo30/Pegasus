#ifndef PEGASUS_STUFF_MOVE_REPRESENTATION_H
#define PEGASUS_STUFF_MOVE_REPRESENTATION_H

#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include <array>

#include "board_object.h"

typedef uint32_t UL;
typedef uint32_t Move;

//---------- Position constants ---------//
// Corners of the board
//#define ROOK_B_SHORT_CORNER 98 // h8
//#define ROOK_B_LONG_CORNER 91 // a8
//#define ROOK_W_SHORT_CORNER 28 // h1
//#define ROOK_W_LONG_CORNER 21 // a1

//FIXME: this is a awful and long namespace, any recomendations for something shorter?
namespace MoveRepresentation {

    enum : unsigned char {startPosIndex /*6 bits*/, endPosIndex /*6 bits*/,
    castleIndex /*1 bits*/, enPassantIndex /*1 bits*/, captureIndex /*4 bits*/,
    promoteIndex /*1 bits*/, pieceThatMovedIndex /*4 bits*/};
    const UL numBits = sizeof(UL) * 8;
    // Redid this so its easier to work with lol
    constexpr const static unsigned short widths[7] = {6, 6,
                                                       1, 1, 4,
                                                       1, 4};
    // Automatically calculated for speed
    static unsigned short prefixRanges[sizeof(widths)/ sizeof(widths[0])];



    // Changelog: changed piece that moved and capture to 4 bits so it can use the piece enum found in board.h for compatibility/speed and since there is extra space anyways
    //            changed ranges so that it looks nicer an is easier to work with lol
    //            finalized the rules of each bit and what they each stand for:     v v v v v SEE BELOW v v v v v

    /**
     * Creates a new move given the parameters.
     * Required parameters: 
     *   <start/end>Position: 64-index of the moving piece (castling is done by a king move)
     *   pieceThatMoved: colored piece that is making the move
     * Optional parameters:
     *   castle: 0 = no castle, 1 = castle, can determine which side by start/end position
     *   enPassant: 0 = no enPassant, 1 = enPassant(either the capture or the initial forward 2 jump), can determine btw them by checking whether capture is empty or not, since the jump forward 2 cannot capture
     *   capture: the colored piece that was captured during this move
     *   promote: 0 = no promote, 1 = promote. If 1, pieceThatMoved will contain what it promoted to, can be assumed it WAS a pawn cuz only pawns promote
     * board::EMPTY is used for no capture/promote and stuff
     */
    Move encodeMove(short startPosition, short endPosition, short piece, 
    short capturedPiece=board::EMPTY, short castle=0u, short enPassant=0u, short promotedPiece=board::EMPTY) {
        Move code = 0;

        // calculate prefixRanges, should run only once
        if (prefixRanges == nullptr){
            prefixRanges[0] = widths[0];
            for (unsigned int i = 0; i < sizeof(widths)/ sizeof(widths[0]); i++){
                prefixRanges[i] = prefixRanges[i-1] + widths[i];
            }
        }

        // Get result by bit-shifting the inputs into place then or'ing the results
        code |= (startPosition << (numBits - prefixRanges[startPosIndex]));
        code |= (endPosition << (numBits - prefixRanges[endPosIndex]));
        code |= (castle << (numBits - prefixRanges[castleIndex]));
        code |= (enPassant << (numBits - prefixRanges[enPassantIndex]));
        code |= (capturedPiece << (numBits - prefixRanges[captureIndex]));
        code |= (promotedPiece << (numBits - prefixRanges[promoteIndex]));
        code |= (piece << (numBits - prefixRanges[pieceThatMovedIndex]));

        return code;
    }

    // TODO: optimization? change UL return type to short or int or something
    // Generic decoder function, decodes "target" from "toDecode"
    // Meant to use MoveRepresentation::"enum" as "target"
    UL decodeMove(Move code, unsigned short target){
        // Use bit operations to extract "len" bits starting from right-most bit "right"
        // Bit mask generated by shifting 1 to the left, then subtracting 1, then shifting: ex: 0000 0001 -> 0001 0000 -> 0000 1111 -> 0111 1000
        return ((1u << (prefixRanges[target] - ((target == 0) ? 0 : prefixRanges[target-1])) ) - 1u) & (code >> (numBits - prefixRanges[target]));
    }
};

#endif //PEGASUS_STUFF_MOVE_REPRESENTATION_H
