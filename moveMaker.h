#ifndef PEGASUS_STUFF_MOVEMAKER_H
#define PEGASUS_STUFF_MOVEMAKER_H

#include "constants.h"
#include "move_representation.h"
#include "utilityMethods.h"
#include "board_object.h"


namespace move_rep {
    /**
     * Returns true if it was able to apply move to the board,
     * Assumes move is valid.
     */
    bool applyMove(board::Board *board, Move move) {
        // TODO: castling
        //  ??? i think castling is done? - Troy
        // TODO: pieceLocations
        //  ??? wut?
        // store values since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        UL endPos = index64to120[move_rep::decodeMove(move, move_rep::endPosIndex)];
        UL startPos = index64to120[move_rep::decodeMove(move, move_rep::startPosIndex)];

        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        board->EP = -1; // we no longer care if the previous turn was a double jump, so reset it since this turn probably won't be.

        /*----- set END of move ------*/
        // Should take care of both normal moves and promotion at the same time
        board->chessboard[endPos] = piece;


        /*----- en passant ------*/
        if(move_rep::decodeMove(move, move_rep::enPassantIndex)){
            // capture and enPassant means that this is the execution of the enPassant
            UL captured = move_rep::decodeMove(move, move_rep::captureIndex);
            if(captured != EMPTY) {
                // white capture black
                if (captured == BP) {
                    board->chessboard[endPos-10] = EMPTY;
                }
                    // black capture white
                else{
                    board->chessboard[endPos+10] = EMPTY;
                }
            }
                // otherwise, this is a "double jump" that allows enPassant to happen next turn
            else{
                // set board to describe a double jump just occur in this column (column A corresponds to zero, etc.).
                board->EP = index120to64[endPos] & 7;
            }
        }


        /*----- move rook in castling ------*/
        if(move_rep::decodeMove(move, move_rep::castleIndex)){
            // black left side (top left)
            if(endPos == ROOK_B_LONG_CASTLE_TO - 1){ // king end is 'left' of rook end on long (queenside) castle, so -1
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = BR;
                board->chessboard[ROOK_B_LONG_CORNER] = EMPTY;
            }
                // black right side (top right)
            else if(endPos == ROOK_B_SHORT_CASTLE_TO + 1){ // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = BR;
                board->chessboard[ROOK_B_SHORT_CORNER] = EMPTY;
            }
                // white left side (bottom left)
            else if(endPos == ROOK_W_LONG_CASTLE_TO - 1){  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = WR;
                board->chessboard[ROOK_W_LONG_CORNER] = EMPTY;
            }
                // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = WR;
                board->chessboard[ROOK_W_SHORT_CORNER] = EMPTY;
            }
        }

        // TODO: castling rights
        // Castling rights: organized in branches such that the least calculations are needed, pls don't change it for now
        // Black
        // King moves, lose all castle rights
        if(piece == BK && (board->CBK || board->CBQ)){
            board->CBK = false;
            board->CBQ = false;
        }
        // Rook moves
        else if(piece == BR && (board->CBK || board->CBQ)){
            // top left of board
            if(board->CBQ && board->chessboard[91] != BR){
                board->CBQ = false;
            }
            // top right of board
            else if(board->CBK && board->chessboard[98] != BR){
                board->CBK = false;
            }
        }

        // White
        // King moves, lose all castle rights
        if(piece == WK && (board->CWK || board->CWQ)){
            board->CWK = false;
            board->CWQ = false;
        }
        // Rook moves
        else if(piece == WR && (board->CWK || board->CWQ)){
            // top left of board
            if(board->CWQ && board->chessboard[21] != WR){
                board->CWQ = false;
            }
            // top right of board
            else if(board->CWK && board->chessboard[28] != WR){
                board->CWK = false;
            }
        }

        /*----- set START of move ------*/
        // move from will always leave an empty space (except chess960 castling, which is handled in castling section)
        board->chessboard[startPos] = EMPTY;

        /*----- final things that need to be reset -------*/
        board->turnWhite = ! board->turnWhite; // switch turns
        board->moveHistory.push(move);
        return true;
    }

    void undoMove(board::Board *board) {
        Move move = board->moveHistory.top();
        board->moveHistory.pop();

        // store endpos since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        UL endPos = index64to120[move_rep::decodeMove(move, move_rep::endPosIndex)];
        UL startPos = index64to120[move_rep::decodeMove(move, move_rep::startPosIndex)];
        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        /*----- reset START of move ------*/
        // there was a promotion, must be pawn
        if (move_rep::decodeMove(move, move_rep::promoteIndex)) {
            board->chessboard[startPos] = utility::isWhite(board->chessboard[endPos]) ? WP : BP;
        }
            // otherwise keep piece the same
        else {
            board->chessboard[startPos] = piece;
        }
        // from this point on, we can be sure the piece that made the move is the one at start position

        /*----- set END of move / en passant ------*/
        board->EP = -1; // this default assumes we are not undoing to a board where a pawn has just double jumped; this will change if we are.

        // if en passant (not including double jump)
        if (move_rep::decodeMove(move, move_rep::enPassantIndex) && move_rep::decodeMove(move, move_rep::captureIndex) != EMPTY) {
            UL captured = move_rep::decodeMove(move, move_rep::captureIndex);
            // white did capture black
            if (captured == BP) {
                board->chessboard[endPos-10] = BP;

            // black did capture white
            } else {
                board->chessboard[endPos+10] = WP;
            }
            // No other piece can be captured during an en passant, so pawn must have moved onto empty square.
            board->chessboard[endPos] = EMPTY;
            // The previous move must have been a double jump in the column the attacking piece ended in, so store this column number
            board->EP = index120to64[endPos] & 7;
        // No en passant (either regular move or double jump)
        } else {
            // if there was no capture, then 'captured' will be set to empty which is what we wanted to set the spot to anyways
            board->chessboard[endPos] = move_rep::decodeMove(move, move_rep::captureIndex);
            // check if the previous move was a double jump
            if (!!move_rep::decodeMove(board->moveHistory.top(), move_rep::enPassantIndex) && move_rep::decodeMove(board->moveHistory.top(), move_rep::captureIndex) == EMPTY) {
                // store column of previous move's double jump
                board->EP = move_rep::decodeMove(board->moveHistory.top(), move_rep::endPosIndex) & 7;
            }
        }

        /*----- castling ------*/
        if(move_rep::decodeMove(move, move_rep::castleIndex)){
            // black left side (top left)
            if (endPos == ROOK_B_LONG_CASTLE_TO - 1) { // king end is 'left' of rook end on long (queenside) castle, so -1
                board->chessboard[ROOK_B_LONG_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_B_LONG_CORNER] = BR;
            }
            // black right side (top right)
            else if (endPos == ROOK_B_SHORT_CASTLE_TO + 1) { // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_B_SHORT_CORNER] = BR;
            }
            // white left side (bottom left)
            else if (endPos == ROOK_W_LONG_CASTLE_TO - 1) {  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_W_LONG_CORNER] = WR;
            }
            // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_W_SHORT_CORNER] = WR;
            }
        }

        board->turnWhite = ! board->turnWhite; // switch turns
    }
}

#endif //PEGASUS_STUFF_MOVEMAKER_H
