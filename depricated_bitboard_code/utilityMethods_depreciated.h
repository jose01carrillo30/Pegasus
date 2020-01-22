//
// Created by troyl on 11/13/2019.
//

#ifndef PEGASUS_STUFF_UTILITYMETHODS_H
#define PEGASUS_STUFF_UTILITYMETHODS_H

#include "board_object.h"
#include <iostream>
#include <bitset>
#include "board_object_DEPRECIATED.h"

namespace utility{
    // A utility function to print out a single bitboard:
    void printBitboard(ULL board) {
        // Note: this print function is weird because it uses the Little-Endian Rank-File Mapping:
        // Iterate through all 64 bits:
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // THE CURRENT BIT IS (8i + j)
                // If the current bit is 1, print "1 ". Otherwise, print "0 ":
                std::cout << (((board >> (8*i + j)) & 1) ? "1 " : ". ");
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    /** Prints binary representation of 64 bit number to cout */
    void printBinary(uint64_t val) {
        std::bitset<64> b(val);
        std::cout << b << std::endl;
    }

    /** 
     * Returns string of uint64_t with comma separation 
     * Credit to carljalal https://stackoverflow.com/questions/7276826/c-format-number-with-commas
     */
    std::string toCommaString(uint64_t num) {
        std::string numWithCommas = std::to_string(num);
        int insertPosition = numWithCommas.length() - 3;
        while (insertPosition > 0) {
            numWithCommas.insert(insertPosition, ",");
            insertPosition-=3;
        }
        return numWithCommas;
    }

    /** Is this a valid nonempty piece enum? */
    bool isPiece(unsigned char spaceEnum) {
        return spaceEnum < board::EMPTY; // Assumes piece enums are immediately followed by EMPTY enum
    }

    /** Assuming a valid nonempty piece enum, is the piece white or black? */
    bool isBlack(unsigned char piece) {
        return piece % 2; // Assumes black pieces are even enums
    }
    bool isWhite(unsigned char piece) {
        return !isBlack(piece); //Assumes white pieces are odd enums
    }

    //forward declaration so I can put ugly switch statement at the bottom of file
    unsigned char getCharFromEnum(unsigned char enumValue, unsigned char empty='.', unsigned char invalid='x'); 

    void printInfo(board::Board* board, int lineNum) {
        switch (lineNum)
        {
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
            std::cout << "En Passant: " << board->EP;
            break;
        case 5:
            std::cout << "Material: {White: " << board->materialWhite << " Black: " << board->materialBlack << "}";
            break;
        case 6:
            std::cout << "Space 21 isWhite(): " << isWhite(board->chessboard[21]) <<  " Space 21 isPiece(): " << isPiece(board->chessboard[21]);
            break;
        default:
            break;
        }
    }

    /** 
     * Prints the entire Board's array, including invalid spaces
     * Set info to true to also print all information about Board
     */
    void printBoardArray(board::Board* board, bool info=true) {
        for (size_t i = 0; i < 120; i++) {
            std::cout << getCharFromEnum(board->chessboard[i]) << " ";
            if(i % 10 == 9) {
                if (info) printInfo(board, i/10 - 2);
                std::cout << std::endl;
            }
        }
    }
    /** 
     * Prints the entire Board in a pretty way
     * Set info to true to also print all information about Board
     */
    void printBoard(board::Board* board, bool info=true) {
        std::cout << "  +-----------------+" << std::endl;
        for (size_t r = 0; r < 8; r++) {
            std::cout << 8-r << " | ";
            for (size_t c = 0; c < 8; c++) { 
                std::cout << board->chessboard[21 + 10*r + c] << " ";
            }
            std::cout << "|  ";
            if (info) printInfo(board, r);
            std::cout << std::endl;
        }
        std::cout << "  +-----------------+" << std::endl;
        std::cout << "    a b c d e f g h  " << std::endl;
    }

    // is there a better way to do this than just a big switch?
    /**
     * Gets char respresentation of piece type enum
     * OPTIONALLY set empty to desired character representation of EMPTY, 
     * OPTIONALLY set invalid to desired character representation of INVALID, 
     */
    unsigned char getCharFromEnum(unsigned char enumValue, unsigned char empty, unsigned char invalid) {
        switch (enumValue) {
        case board::EMPTY:
            return empty;
            break;
        case board::INVALID:
            return invalid;
            break;
        case board::WP:
            return 'P';
            break;
        case board::BP:
            return 'p';
            break;
        case board::WR:
            return 'R';
            break;
        case board::BR:
            return 'r';
            break;
        case board::WN:
            return 'N';
            break;
        case board::BN:
            return 'n';
            break;
        case board::WB:
            return 'B';
            break;
        case board::BB:
            return 'b';
            break;
        case board::WQ:
            return 'Q';
            break;
        case board::BQ:
            return 'q';
            break;
        case board::WK:
            return 'K';
            break;
        case board::BK:
            return 'k';
            break;
        default:
            return '?';
            break;
        }
    }
}

#endif //PEGASUS_STUFF_UTILITYMETHODS_H
