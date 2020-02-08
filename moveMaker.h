#ifndef PEGASUS_STUFF_MOVEMAKER_H
#define PEGASUS_STUFF_MOVEMAKER_H

#include "constants.h"
#include "move_representation.h"
#include "utilityMethods.h"
#include "board_object.h"


namespace moveMaker {
    /**
     * Returns true if it was able to apply move to the board,
     * Assumes move is valid.
     */
    bool applyMove(board::Board *board, Move move) {
        // store values since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        UL endPos = board::index64to120[move_rep::decodeMove(move, move_rep::endPosIndex)];
        UL startPos = board::index64to120[move_rep::decodeMove(move, move_rep::startPosIndex)];

        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        board->EP = -1; // we no longer care if the previous turn was a double jump, so reset it since this turn probably won't be.

        /*----- set END of move ------*/
        // Should take care of both normal moves and promotion at the same time
        board->chessboard[endPos] = piece;


        /*----- en passant ------*/
        if(move_rep::decodeMove(move, move_rep::enPassantIndex)){
            // capture and enPassant means that this is the execution of the enPassant
            UL captured = move_rep::decodeMove(move, move_rep::captureIndex);
            if(captured != board::EMPTY) {
                // white capture black
                if (captured == board::BP) {
                    board->chessboard[endPos-10] = board::EMPTY;
                }
                    // black capture white
                else{
                    board->chessboard[endPos+10] = board::EMPTY;
                }
            }
                // otherwise, this is a "double jump" that allows enPassant to happen next turn
            else{
                // set board to describe a double jump just occur in this column (column A corresponds to zero, etc.).
                board->EP = board::index120to64[endPos] & 7;
            }
        }


        /*----- move rook in castling ------*/
        if(move_rep::decodeMove(move, move_rep::castleIndex)){
            // black left side (top left)
            if(endPos == ROOK_B_LONG_CASTLE_TO - 1){ // king end is 'left' of rook end on long (queenside) castle, so -1
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::BR;
                board->chessboard[ROOK_B_LONG_CORNER] = board::EMPTY;
            }
                // black right side (top right)
            else if(endPos == ROOK_B_SHORT_CASTLE_TO + 1){ // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::BR;
                board->chessboard[ROOK_B_SHORT_CORNER] = board::EMPTY;
            }
                // white left side (bottom left)
            else if(endPos == ROOK_W_LONG_CASTLE_TO - 1){  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::WR;
                board->chessboard[ROOK_W_LONG_CORNER] = board::EMPTY;
            }
                // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::WR;
                board->chessboard[ROOK_W_SHORT_CORNER] = board::EMPTY;
            }
        }

        /*----- set START of move ------*/
        // move from will always leave an empty space (except chess960 castling, which is handled in castling section)
        board->chessboard[startPos] = board::EMPTY;

        /*----- final things that need to be reset -------*/
        board->turnWhite = ! board->turnWhite; // switch turns
        board->moveHistory.push(move);
        return true;
    }

    void undoMove(board::Board *board) {
        Move move = board->moveHistory.top();
        board->moveHistory.pop();

        // store endpos since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        UL endPos = board::index64to120[move_rep::decodeMove(move, move_rep::endPosIndex)];
        UL startPos = board::index64to120[move_rep::decodeMove(move, move_rep::startPosIndex)];
        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        /*----- reset START of move ------*/
        // there was a promotion, must be pawn
        if (move_rep::decodeMove(move, move_rep::promoteIndex)) {
            board->chessboard[startPos] = utility::isWhite(board->chessboard[endPos]) ? board::WP : board::BP;
        }
            // otherwise keep piece the same
        else {
            board->chessboard[startPos] = piece;
        }
        // from this point on, we can be sure the piece that made the move is the one at start position

        /*----- set END of move / en passant ------*/
        board->EP = -1; // this default assumes we are not undoing to a board where a pawn has just double jumped; this will change if we are.

        // if en passant (not including double jump)
        if (move_rep::decodeMove(move, move_rep::enPassantIndex) && move_rep::decodeMove(move, move_rep::captureIndex) != board::EMPTY) {
            UL captured = move_rep::decodeMove(move, move_rep::captureIndex);
            // white did capture black
            if (captured == board::BP) {
                board->chessboard[endPos-10] = board::BP;

            // black did capture white
            } else {
                board->chessboard[endPos+10] = board::WP;
            }
            // No other piece can be captured during an en passant, so pawn must have moved onto empty square.
            board->chessboard[endPos] = board::EMPTY;
            // The previous move must have been a double jump in the column the attacking piece ended in, so store this column number
            board->EP = board::index120to64[endPos] & 7;
        // No en passant (either regular move or double jump)
        } else {
            // if there was no capture, then 'captured' will be set to empty which is what we wanted to set the spot to anyways
            board->chessboard[endPos] = move_rep::decodeMove(move, move_rep::captureIndex);
            // check if the previous move was a double jump
            if (!!move_rep::decodeMove(board->moveHistory.top(), move_rep::enPassantIndex) && move_rep::decodeMove(board->moveHistory.top(), move_rep::captureIndex) == board::EMPTY) {
                // store column of previous move's double jump
                board->EP = move_rep::decodeMove(board->moveHistory.top(), move_rep::endPosIndex) & 7;
            }
        }

        /*----- castling ------*/
        if(move_rep::decodeMove(move, move_rep::castleIndex)){
            // black left side (top left)
            if (endPos == ROOK_B_LONG_CASTLE_TO - 1) { // king end is 'left' of rook end on long (queenside) castle, so -1
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = board::EMPTY;
                board->chessboard[ROOK_B_LONG_CORNER] = board::BR;
            }
                // black right side (top right)
            else if (endPos == ROOK_B_SHORT_CASTLE_TO + 1) { // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = board::EMPTY;
                board->chessboard[ROOK_B_SHORT_CORNER] = board::BR;
            }
                // white left side (bottom left)
            else if (endPos == ROOK_W_LONG_CASTLE_TO - 1) {  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = board::EMPTY;
                board->chessboard[ROOK_W_LONG_CORNER] = board::WR;
            }
                // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = board::EMPTY;
                board->chessboard[ROOK_W_SHORT_CORNER] = board::WR;
            }
        }

        board->turnWhite = ! board->turnWhite; // switch turns
    }
}

#endif //PEGASUS_STUFF_MOVEMAKER_H
