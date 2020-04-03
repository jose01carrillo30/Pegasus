#ifndef PEGASUS_STUFF_BOARD_OBJECT_H
#define PEGASUS_STUFF_BOARD_OBJECT_H

#include <cstdint>
#include <stack>

#include "constants.hh"

namespace board {
    class Board {
        public:
            /* ------- independent fields, provide necessary information about board ------- */
            pieceEnum chessboard[120];
            bool CWK, CWQ, CBK, CBQ; // castle rights
            char EP; // en passant rights: what column did a double jump just occur? -1 if no double jump. 
            short movesSinceLastCapture; // 50 move rule
            bool turnWhite; // whose turn it is
            std::stack<Move> moveHistory; // list of moves applied to starting FEN.

            /* ------- dependent fields, store information about board that is derived from independent fields -------- */
            short material; // changed material score to just be material for both
            uint64_t hashCode;
            
            /** store pieces as 64 bit indexed pieces */
            pos64 pieceLocations[12][10]; 
            /** parallel to pieceLocations, stores how many pieces we have locations for */
            unsigned char pieceNumbers[12];

            /** 
             * Creates a new board with all values set to INVALID. Usually you should call parseFen after creating a new board. 
             */
            Board();

            /** 
             * Boards are equal if all independent fields except moveHistory are equal. 
             * Note that comparing the hashes is MUCH faster that this, and should be used to compare boards
             * for most practical purposes. Really, this is just here to test if the hash function is working.
             */
            bool operator==(const Board& other) const;

            /***/
            void addPieceToPL(pieceEnum piece, pos64 location);

            /** 
             * Update the position oldLocation to be newLocation for type piece.
             * Returns false if it does not find such a piece to update.
             */
            bool updatePieceInPL(pieceEnum piece, pos64 oldLocation, pos64 newLocation);

            /** 
             * Remove the piece at location for type piece.
             * Returns false if it does not find such a piece to remove.
             */
            bool removePieceFromPL(pieceEnum piece, pos64 location);
    };
}

#endif //PEGASUS_STUFF_BOARD_OBJECT_H
