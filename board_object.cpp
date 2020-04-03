#include <cstdint>
#include <stack>

#include "constants.hh"

#include "board_object.hh"

namespace board {
    /**
     * Creates a new board with array set to INVALID. Usually you should call parseFen after creating a new board. 
     */
    Board::Board() {
        // set up the chessboard with all INVALID
        for (int i = 0; i < 120; i++) {
            chessboard[i] = INVALID;
        }
        movesSinceLastCapture = 0;
        for (int i = 0; i < 12; i++) {
            pieceNumbers[i] = 0;
        }
    }

    /** 
     * Boards are equal if all independent fields except moveHistory are equal. 
     * Note that comparing the hashes is MUCH faster that this, and should be used to compare boards
     * for most practical purposes. Really, this is just here to test if the hash function is working.
     */
    bool Board::operator==(const Board& other) const {
        if (CBK != other.CBK || 
            CBQ != other.CBQ || 
            CWK != other.CWK || 
            CWQ != other.CWQ ||
            EP != other.EP ||
            turnWhite != other.turnWhite ||
            movesSinceLastCapture != other.movesSinceLastCapture) {
            return false;
        }
        for (int i = 0; i < 120; i++) {
            if (chessboard[i] != other.chessboard[i]) {
                return false;
            }
        }
        return true;
    }

    void Board::addPieceToPL(pieceEnum piece, pos64 location) {
        pieceLocations[piece][pieceNumbers[piece]++] = location;
    }

    bool Board::updatePieceInPL(pieceEnum piece, pos64 oldLocation, pos64 newLocation) {
        for (int i = 0; i < pieceNumbers[piece]; i++) { // loop for all pieces of type
            if (pieceLocations[piece][i] == oldLocation) { // find the match
                pieceLocations[piece][i] = newLocation;
                return true;
            }
        }
        return false;
    }

    bool Board::removePieceFromPL(pieceEnum piece, pos64 location) {
        for (int i = 0; i < pieceNumbers[piece]; i++) { // loop for all pieces of type
            if (pieceLocations[piece][i] == location) { // find the match
                // override current position with last element in this row of PL
                pieceLocations[piece][i] = pieceLocations[piece][pieceNumbers[piece] - 1];
                // delete last element in this row of PL
                pieceNumbers[piece]--;
                return true;
            }
        }
        return false;
    }

}
