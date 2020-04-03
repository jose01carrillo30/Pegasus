#include <iostream>
#include <bitset>
#include <assert.h>

#include "constants.hh"
#include "board_object.hh"

#include "utilityMethods.hh"

namespace utility{

    void printBinary(uint64_t val) {
        std::bitset<64> b(val);
        std::cout << b << std::endl;
    }

    std::string toCommaString(uint64_t num) {
        std::string numWithCommas = std::to_string(num);
        int insertPosition = numWithCommas.length() - 3;
        while (insertPosition > 0) {
            numWithCommas.insert(insertPosition, ",");
            insertPosition-=3;
        }
        return numWithCommas;
    }

    void printInfo(board::Board* board, int lineNum) {
        switch (lineNum) {
        case 0:
            std::cout << "hash code: " << toCommaString(board->hashCode);
            break;
        case 1:
            std::cout << "white castle rights: {king: " << board->CWK << " queen: " << board->CWQ << "}";
            break;
        case 2:
            std::cout << "black castle rights: {king: " << board->CBK << " queen: " << board->CBQ << "}";
            break;
        case 3:
            std::cout << "Moves since last capture: " << board->movesSinceLastCapture;
            break;
        case 4:
            std::cout << "En Passant: " << (int)board->EP;
            break;
        case 5:
            std::cout << "Material: " << board->material;
            break;
        case 6:
            std::cout << "Move history stack size: " << board->moveHistory.size();
            break;
        default:
            break;
        }
    }

    void printBoardPieceLocations(board::Board* board) {
        std::cout << "~~~~~~~~~~~~~~" << std::endl;
        for (int pieceIndex = 0; pieceIndex < 12; pieceIndex++) { // for all types of pieces
            std::cout << getCharFromEnum(pieceIndex) << " (" << (int)board->pieceNumbers[pieceIndex] << ")| ";
            for (int i = 0; i < board->pieceNumbers[pieceIndex]; i++) { // for all of those pieces
                std::cout << (int) board->pieceLocations[pieceIndex][i] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "~~~~~~~~~~~~~~" << std::endl;
    }
    board::Board boardFromPieceLocations(board::Board* board) {
        board::Board genBoard = board::Board();
        for (int pieceIndex = 0; pieceIndex < 12; pieceIndex++) { // for all types of pieces
            for (int i = 0; i < board->pieceNumbers[pieceIndex]; i++) { // for all of those pieces
                assert(genBoard.chessboard[index64to120[board->pieceLocations[pieceIndex][i]]] == INVALID);
                genBoard.chessboard[index64to120[board->pieceLocations[pieceIndex][i]]] = pieceIndex;
            }
        }
        return genBoard;
    }

    void printBoardArray(board::Board* board, bool info) {
        for (size_t i = 0; i < 120; i++) {
            std::cout << getCharFromEnum(board->chessboard[i]) << " ";
            if(i % 10 == 9) {
                if (info) printInfo(board, i/10 - 2);
                std::cout << std::endl;
            }
        }
    }

    void printBoard(board::Board* board, bool flipped, bool info) {
        std::cout << "  +-----------------+" << std::endl;
        for (size_t r = 0; r < 8; r++) {
            // ranks top to bottom go 8->1 normally, reversed when flipped
            std::cout << (flipped? r+1 : 8-r) << " | ";
            for (size_t c = 0; c < 8; c++) { 
                if (flipped) {
                    // 21 is starting tile. +10*r means white at top. (7-c) means reverse columns
                    std::cout << getCharFromEnum(board->chessboard[21 + 10*r + (7-c)]) << " ";
                } else {
                    std::cout << getCharFromEnum(board->chessboard[91 - 10*r + c]) << " ";
                }
            }

            std::cout << "|  ";
            if (info) printInfo(board, r);
            std::cout << std::endl;
        }
        std::cout << "  +-----------------+" << std::endl;
        if (flipped) {
            // columns were reversed so their enumeration needs to be too
            std::cout << "    h g f e d c b a  " << std::endl;
        }
        else {
            std::cout << "    a b c d e f g h  " << std::endl;
        }
    }

    // is there a better way to do this than just a big switch?
    char getCharFromEnum(PieceEnum enumValue, char empty, char invalid) {
        switch (enumValue) {
        case EMPTY:
            return empty;
            break;
        case INVALID:
            return invalid;
            break;
        case WP:
            return 'P';
            break;
        case BP:
            return 'p';
            break;
        case WR:
            return 'R';
            break;
        case BR:
            return 'r';
            break;
        case WN:
            return 'N';
            break;
        case BN:
            return 'n';
            break;
        case WB:
            return 'B';
            break;
        case BB:
            return 'b';
            break;
        case WQ:
            return 'Q';
            break;
        case BQ:
            return 'q';
            break;
        case WK:
            return 'K';
            break;
        case BK:
            return 'k';
            break;
        default:
            return '?';
            break;
        }
    }
}