//
// Created by troyl on 2/4/2020.
//

#include "move_representation.h"
#include "utilityMethods.h"
#include "board_object.h"

// Castling constants
#define ROOK_B_SHORT_CASTLE_TO 96 // f8
#define ROOK_B_LONG_CASTLE_TO 94 // d8
#define ROOK_W_SHORT_CASTLE_TO 26 // f1
#define ROOK_W_LONG_CASTLE_TO 24 // d1


namespace moveMaker {
    /**
     * Returns true if it was able to apply move to the board,
     * Assumes move is valid.
     */
    bool applyMove(board::Board *board, Move move) {
        // store values since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        // FIXME: trying to call a std::map like a function doesn't work and won't compile, so i've commented it out and added back the old code below it temporaril
        // UL endPos = board::index64to120(MoveRepresentation::decodeMove(move, MoveRepresentation::endPosIndex));
        // UL startPos = board::index64to120(MoveRepresentation::decodeMove(move, MoveRepresentation::startPosIndex));
        UL endPos = MoveRepresentation::decodeMove(move, MoveRepresentation::endPosIndex);
        UL startPos = MoveRepresentation::decodeMove(move, MoveRepresentation::startPosIndex);

        UL piece = MoveRepresentation::decodeMove(move, MoveRepresentation::pieceThatMovedIndex);

//        // assumes promoteIndex stores piece type being promoted to, EMPTY/INVALID otherwise
//        if (MoveRepresentation::decodeMove(move, MoveRepresentation::promoteIndex)) {
//            // promotion
//            if (utility::isWhite(board->chessboard[startPos])) // TODO: eww can we just store whose turn it is?
//                board->chessboard[endPos] = utility::recolor(MoveRepresentation::decodeMove(move, MoveRepresentation::promoteIndex));
//            else
//                board->chessboard[endPos] = utility::toBlack(utility::recolor(MoveRepresentation::decodeMove(move, MoveRepresentation::promoteIndex)));
//        } else {
//            // normal move
//            board->chessboard[endPos] = piece;
//        }


        /*----- set END of move ------*/
        // Should take care of both normal moves and promotion at the same time
        board->chessboard[endPos] = piece;

//        // assumes 0 means not en passant, anything else means en passant
//        if (MoveRepresentation::decodeMove(move, MoveRepresentation::enPassantIndex)) {
//            // assumes 12x10 board, where 10 in a row.
//            // row of start and column of end
//            board->chessboard[startPos / 10 * 10 + endPos % 10] = board::EMPTY;
//        }


        /*----- en passant ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::enPassantIndex)){
            // capture
            UL captured = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
            if(captured != board::EMPTY) {
                // white capture black
                if (captured == board::BP) {
                    board->chessboard[endPos+10] = board::EMPTY;
                }
                // black capture white
                else{
                    board->chessboard[endPos-10] = board::EMPTY;
                }
            }
            // "double jump", allowing an enPassant to happen next turn
            else{
                // TODO: allow the pawn move generation to make the move next turn
            }
        }


        /*----- castling ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)){
            // black left side (top left)
            if(endPos == 93){
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::BR;
            }
            // black right side (top right)
            else if(endPos == 97){
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::BR;
            }
            // white left side (bottom left)
            else if(endPos == 23){
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::WR;
            }
            // white right side (bottom right)
            else{
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::WR;
            }
        }
//        UL castle = MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)
//        // set rook for short castle
//        if (castle == SHORT_CASTLE) {
//            // is this on black or white's side?
//            if (endPos >
//                32) { // Regardless if we use 120 or 64 position numbering, 32 will be between ranks [2,7] inclusive. Could be any other number that fits this criteria.
//                board->chessboard[ROOK_B_SHORT_CORNER] = board::EMPTY;
//                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::BR;
//            } else {
//                board->chessboard[ROOK_W_SHORT_CORNER] = board::EMPTY;
//                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::WR;
//            }
//            // set rook for long castle
//        } else if (castle == LONG_CASTLE) {
//            // is this on black or white's side?
//            if (endPos >
//                32) { // Regardless if we use 120 or 64 position numbering, 32 will be between ranks [2,7] inclusive. Could be any other number that fits this criteria.
//                board->chessboard[ROOK_B_LONG_CORNER] = board::EMPTY;
//                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::BR;
//            } else {
//                board->chessboard[ROOK_W_LONG_CORNER] = board::EMPTY;
//                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::WR;
//            }
//        }

        /*----- set START of move ------*/
        // move from will always leave an empty space (except chess960 castling, which is handled in castling section)
        board->chessboard[startPos] = board::EMPTY;
        return true;
    }

    bool undoMove(board::Board *board, Move move) {
        // store endpos since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        UL endPos = MoveRepresentation::decodeMove(move, MoveRepresentation::endPosIndex);
        UL startPos = MoveRepresentation::decodeMove(move, MoveRepresentation::startPosIndex);
        UL piece = MoveRepresentation::decodeMove(move, MoveRepresentation::pieceThatMovedIndex);


        /*----- reset START of move ------*/
        // there was a promotion, must be pawn
        if (MoveRepresentation::decodeMove(move, MoveRepresentation::promoteIndex)) {
            board->chessboard[startPos] = utility::isWhite(board->chessboard[endPos]) ? board::WP : board::BP;
        }
        // otherwise keep piece the same
        else {
            board->chessboard[startPos] = piece;
        }
        // from this point on, we can be sure the piece that made the move is the one at start position


        /*----- set END of move ------*/
        // takes care of color and just empty spaces
        board->chessboard[endPos] = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);

//        // replace the piece that was captured,
//        board->chessboard[endPos] = utility::recolor(MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex));
//        // and recolor it if needed
//        if (utility::isBlack(board->chessboard[startPos])) utility::toBlack(board->chessboard[endPos]);


        /*----- en passant ------*/
        // assumes 0 means not en passant, anything else means en passant
        if (MoveRepresentation::decodeMove(move, MoveRepresentation::enPassantIndex)) {
            // capture
            UL captured = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
            if(captured != board::EMPTY) {
                // white did capture black
                if (captured == board::BP) {
                    board->chessboard[endPos+10] = board::BP;
                }
                // black did capture white
                else{
                    board->chessboard[endPos-10] = board::WP;
                }
            }
            // "double jump", allowing an enPassant to happen next turn
            else{
                // Nothing happens here :D
            }
        }


        /*----- castling ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)){
            // black left side (top left)
            if(endPos == 93){
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::EMPTY;
                board->chessboard[91] = board::BR;
            }
            // black right side (top right)
            else if(endPos == 97){
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::EMPTY;
                board->chessboard[98] = board::BR;
            }
            // white left side (bottom left)
            else if(endPos == 23){
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::EMPTY;
                board->chessboard[21] = board::WR;
            }
            // white right side (bottom right)
            else{
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::EMPTY;
                board->chessboard[28] = board::WR;
            }
        }

//        /*----- castling ------*/
//        UL castle = MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)
//        // set rook for short castle
//        if (castle == SHORT_CASTLE) {
//            // is this on black or white's side?
//            if (endPos >
//                32) { // Regardless if we use 120 or 64 position numbering, 32 will be between ranks [2,7] inclusive. Could be any other number that fits this criteria.
//                board->chessboard[ROOK_B_SHORT_CORNER] = board::BR;
//                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::EMPTY;
//            } else {
//                board->chessboard[ROOK_W_SHORT_CORNER] = board::WR;
//                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::EMPTY;
//            }
//            // set rook for long castle
//        } else if (castle == LONG_CASTLE) {
//            // is this on black or white's side?
//            if (endPos >
//                32) { // Regardless if we use 120 or 64 position numbering, 32 will be between ranks [2,7] inclusive. Could be any other number that fits this criteria.
//                board->chessboard[ROOK_B_LONG_CORNER] = board::BR;
//                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::EMPTY;
//            } else {
//                board->chessboard[ROOK_W_LONG_CORNER] = board::WR;
//                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::EMPTY;
//            }
//        }
        return true;
    }
}
