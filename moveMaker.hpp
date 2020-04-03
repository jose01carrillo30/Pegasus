#ifndef PEGASUS_STUFF_MOVEMAKER_H
#define PEGASUS_STUFF_MOVEMAKER_H

#include <assert.h>

#include "constants.hh"
#include "move_representation.hpp"
#include "utilityMethods.hh"
#include "board_object.hh"


namespace move_rep {
    /**
     * Returns true if it was able to apply move to the board,
     * Assumes move is valid.
     */
    bool applyMove(board::Board *board, Move move) {
        // store values since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        pos64 endPos64 = move_rep::decodeMove(move, move_rep::endPosIndex);
        pos64 startPos64 = move_rep::decodeMove(move, move_rep::startPosIndex);
        UL endPos = index64to120[endPos64];
        UL startPos = index64to120[startPos64];

        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        board->EP = -1; // we no longer care if the previous turn was a double jump, so reset it since this turn probably won't be.

        /*----- update PL for main movement ------*/
        // We need to know whether this is a pawn promoting, or a regular piece moving.
        if (move_rep::decodeMove(move, move_rep::promoteIndex)) {
            assert(board->removePieceFromPL(utility::isWhite(piece) ? WP : BP, startPos64));
            board->addPieceToPL(piece, endPos64);
        } else {
            std::cout << "piece: " << utility::getCharFromEnum(piece) << " startPos " << (int) startPos64 << " endpos " << (int) endPos64 << std::endl;
            assert(board->updatePieceInPL(piece, startPos64, endPos64));
        }

        /*----- set END of move ------*/
        if (board->chessboard[endPos] != EMPTY) {
            assert(board->removePieceFromPL(board->chessboard[endPos], endPos64));
        }
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
                    assert(board->removePieceFromPL(captured, index120to64[endPos-10]));
                }
                    // black capture white
                else{
                    board->chessboard[endPos+10] = EMPTY;
                    assert(board->removePieceFromPL(captured, index120to64[endPos+10]));
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
                assert(board->updatePieceInPL(BR, index120to64[ROOK_B_LONG_CORNER], index120to64[ROOK_B_LONG_CASTLE_TO]));
            }
                // black right side (top right)
            else if(endPos == ROOK_B_SHORT_CASTLE_TO + 1){ // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = BR;
                board->chessboard[ROOK_B_SHORT_CORNER] = EMPTY;
                assert(board->updatePieceInPL(BR, index120to64[ROOK_B_SHORT_CORNER], index120to64[ROOK_B_SHORT_CASTLE_TO]));
            }
                // white left side (bottom left)
            else if(endPos == ROOK_W_LONG_CASTLE_TO - 1){  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = WR;
                board->chessboard[ROOK_W_LONG_CORNER] = EMPTY;
                assert(board->updatePieceInPL(WR, index120to64[ROOK_W_LONG_CORNER], index120to64[ROOK_W_LONG_CASTLE_TO]));
            }
                // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = WR;
                board->chessboard[ROOK_W_SHORT_CORNER] = EMPTY;
                assert(board->updatePieceInPL(WR, index120to64[ROOK_W_SHORT_CORNER], index120to64[ROOK_W_SHORT_CASTLE_TO]));
            }
        }

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

        // store values since we will use it multiple times, and it does not make sense to repeatedly recalculate it
        pos64 endPos64 = move_rep::decodeMove(move, move_rep::endPosIndex);
        pos64 startPos64 = move_rep::decodeMove(move, move_rep::startPosIndex);
        UL endPos = index64to120[endPos64];
        UL startPos = index64to120[startPos64];

        UL piece = move_rep::decodeMove(move, move_rep::pieceThatMovedIndex);

        /*----- reset START of move / update PL for main movement ------*/
        // there was a promotion, must be pawn
        if (move_rep::decodeMove(move, move_rep::promoteIndex)) {
            board->chessboard[startPos] = utility::isWhite(board->chessboard[endPos]) ? WP : BP;

            assert(board->removePieceFromPL(piece, endPos64));
            board->addPieceToPL(utility::isWhite(piece) ? WP : BP, startPos64);
        }
            // otherwise keep piece the same
        else {
            board->chessboard[startPos] = piece;

            assert(board->updatePieceInPL(piece, endPos64, startPos64));
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
                board->addPieceToPL(BP, index120to64[endPos-10]);

            // black did capture white
            } else {
                board->chessboard[endPos+10] = WP;
                board->addPieceToPL(WP, index120to64[endPos+10]);
            }
            // No other piece can be captured during an en passant, so pawn must have moved onto empty square.
            board->chessboard[endPos] = EMPTY;
            // The previous move must have been a double jump in the column the attacking piece ended in, so store this column number
            board->EP = index120to64[endPos] & 7;
        // No en passant (either regular move or double jump)
        } else {
            // if there was no capture, then 'captured' will be set to empty which is what we wanted to set the spot to anyways
            PieceEnum capturedPiece = move_rep::decodeMove(move, move_rep::captureIndex);
            board->chessboard[endPos] = capturedPiece;

            if (capturedPiece != EMPTY) {
                board->addPieceToPL(capturedPiece, endPos64);
            }
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
                assert(board->updatePieceInPL(BR, index120to64[ROOK_B_LONG_CASTLE_TO], index120to64[ROOK_B_LONG_CORNER]));
            }
            // black right side (top right)
            else if (endPos == ROOK_B_SHORT_CASTLE_TO + 1) { // king end is 'right' of rook end on short (kingside) castle, so +1
                board->chessboard[ROOK_B_SHORT_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_B_SHORT_CORNER] = BR;
                assert(board->updatePieceInPL(BR, index120to64[ROOK_B_SHORT_CASTLE_TO], index120to64[ROOK_B_SHORT_CORNER]));
            }
            // white left side (bottom left)
            else if (endPos == ROOK_W_LONG_CASTLE_TO - 1) {  // king end is 'left' of rook end on long castle, so -1
                board->chessboard[ROOK_W_LONG_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_W_LONG_CORNER] = WR;
                assert(board->updatePieceInPL(WR, index120to64[ROOK_W_LONG_CASTLE_TO], index120to64[ROOK_W_LONG_CORNER]));
            }
            // white right side (bottom right)
            else {
                board->chessboard[ROOK_W_SHORT_CASTLE_TO] = EMPTY;
                board->chessboard[ROOK_W_SHORT_CORNER] = WR;
                assert(board->updatePieceInPL(WR, index120to64[ROOK_W_SHORT_CASTLE_TO], index120to64[ROOK_W_SHORT_CORNER]));
            }
        }

        board->turnWhite = ! board->turnWhite; // switch turns
    }
}

#endif //PEGASUS_STUFF_MOVEMAKER_H
