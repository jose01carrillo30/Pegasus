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
        UL endPos = board::index64to120[MoveRepresentation::decodeMove(move, MoveRepresentation::endPosIndex)];
        UL startPos = board::index64to120[MoveRepresentation::decodeMove(move, MoveRepresentation::startPosIndex)];

        UL piece = MoveRepresentation::decodeMove(move, MoveRepresentation::pieceThatMovedIndex);

        board->EP = -1; // we no longer care if the previous turn was a double jump, so reset it since this turn probably won't be.

        /*----- set END of move ------*/
        // Should take care of both normal moves and promotion at the same time
        board->chessboard[endPos] = piece;


        /*----- en passant ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::enPassantIndex)){
            // capture and enPassant means that this is the execution of the enPassant
            UL captured = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
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
                board->EP = board::index120to64[endPos] & 7; //TODO: unless some other info needs to be stored here.
            }
        }


        /*----- move rook in castling ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)){
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
        UL endPos = board::index64to120[MoveRepresentation::decodeMove(move, MoveRepresentation::endPosIndex)];
        UL startPos = board::index64to120[MoveRepresentation::decodeMove(move, MoveRepresentation::startPosIndex)];
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

        /*----- set END of move / en passant ------*/
        if (MoveRepresentation::decodeMove(move, MoveRepresentation::enPassantIndex)) {
            UL captured = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
            // en passant was executed so a pawn was captured
            if(captured != board::EMPTY) {
                std::cout << "undo capture en passant" << std::endl;
                // white did capture black
                if (captured == board::BP) {
                    board->chessboard[endPos-10] = board::BP;
                }
                    // black did capture white
                else{
                    board->chessboard[endPos+10] = board::WP;
                }
                // No other piece can be captured during an en passant, so pawn must have moved onto empty square.
                board->chessboard[endPos] = board::EMPTY;
            }
                // otherwise, must have been a "double jump"
            else{
                std::cout << "undo double jump" << std::endl; //TODO: peak previous move from board's move stack, and figure out double jumping
                // reset endPos just like a regular move
                board->chessboard[endPos] = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
            }
        } else {
            // No en passant, just a regular move or capture
            // if there was no capture, then 'captured' will be set to empty which is what we wanted to set the spot to anyways
            board->chessboard[endPos] = MoveRepresentation::decodeMove(move, MoveRepresentation::captureIndex);
        }

        /*----- castling ------*/
        if(MoveRepresentation::decodeMove(move, MoveRepresentation::castleIndex)){
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
