#ifndef PEGASUS_STUFF_UTILITYMETHODS_H
#define PEGASUS_STUFF_UTILITYMETHODS_H

#include <iostream>
#include <bitset>

#include "constants.h"
#include "board_object.h"

namespace utility{

    // FIXME:
    board::Board* createFromFenn(std::string fenn) {
        /** TODO: enpassant and move clocks */
        board::Board* fennBoard = new board::Board(false, true);
        bool isSpace = false;
        fennBoard->CWK = false;
        fennBoard->CBK = false;
        fennBoard->CWQ = false;
        fennBoard->CBQ = false;
        
        int boardIndex = 0;

        // FIXME: if Davis isn't here to support this code, might not be a bad idea to just re-do it.
        for (char c : fenn){
            while (fennBoard->chessboard[boardIndex] == board::INVALID) {
                boardIndex++;
            }
            switch(c) {
                case 'P':
                    fennBoard->chessboard[boardIndex] = board::WP;
                    boardIndex++;
                    break;
                case 'p':
                    fennBoard->chessboard[boardIndex] = board::BP;
                    boardIndex++;
                    break;
                case 'R':
                    fennBoard->chessboard[boardIndex] = board::WR;
                    boardIndex++;
                    break;
                case 'r':
                    fennBoard->chessboard[boardIndex] = board::BR;
                    boardIndex++;
                    break;
                case 'N':
                    fennBoard->chessboard[boardIndex] = board::WN;
                    boardIndex++;
                    break;
                case 'n':
                    fennBoard->chessboard[boardIndex] = board::BN;
                    boardIndex++;
                    break;
                case 'B':
                    fennBoard->chessboard[boardIndex] = board::WB;
                    boardIndex++;
                    break;
                case 'b':
                    if (isSpace) {
                        fennBoard->turnWhite = false;
                    } else {
                        fennBoard->chessboard[boardIndex] = board::BB;
                        boardIndex++;
                    }
                    break;
                case 'Q':
                    if (isSpace)
                        fennBoard->CWQ = true;
                    else {
                        fennBoard->chessboard[boardIndex] = board::WQ;
                        boardIndex++;
                    }
                    break;

                case 'q':
                    if (isSpace) {
                        fennBoard->CBQ = true;
                    } else {
                        fennBoard->chessboard[boardIndex] = board::BQ;
                        boardIndex++;
                    }
                    break;
                case 'K':
                    if (isSpace) {
                        fennBoard->CWK = true;
                    } else {
                        fennBoard->chessboard[boardIndex] = board::WK;
                        boardIndex++;
                    }
                    break;
                case 'k':
                    if (isSpace) {
                        fennBoard->CBK = true;
                    } else {
                        fennBoard->chessboard[boardIndex] = board::BK;
                        boardIndex++;
                    }
                    break;
                case '/':
                    boardIndex++;
                    break;
                case '1':
                    boardIndex++;
                    break;
                case '2':
                    boardIndex += 2;
                    break;
                case '3':
                    boardIndex += 3;
                    break;
                case '4':
                    boardIndex += 4;
                    break;
                case '5':
                    boardIndex += 5;
                    break;
                case '6':
                    boardIndex += 6;
                    break;
                case '7':
                    boardIndex += 7;
                    break;
                case '8':
                    boardIndex += 8;
                    break;
                case ' ':
                    isSpace = true;
                    break;
                case 'w':
                    fennBoard->turnWhite = true;
                    break;
                default:
                    std::cout << "Invalid character in FEN string" << std::endl;
            }
        }
        return fennBoard;
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
    inline bool isPiece(unsigned char spaceEnum) {
        return spaceEnum < board::EMPTY; // Assumes piece enums are immediately followed by EMPTY enum
    }
    /** Assuming a valid nonempty piece enum, is the piece white or black? */
    inline bool isBlack(unsigned char piece) {
        return piece % 2; // Assumes black pieces are odd enums
    }
    /** Assuming a valid nonempty piece enum, is the piece white or black? */
    inline bool isWhite(unsigned char piece) {
        return !isBlack(piece); //Assumes white pieces are even enums
    }
    /** Converts the piece to white, if not already. Note this also converts INVALID to EMPTY. */
    inline unsigned char toWhite(unsigned char piece) {
        // just overwrite LSB.
        return piece & !1u; //Assumes white pieces are even enums
    }
    /** Converts the piece to black, if not already. Note this also converts EMPTY to INVALID. */
    inline unsigned char toBlack(unsigned char piece) {
        // just overwrite LSB.
        return piece | 1u; //Assumes balck pieces are odd enums
    }
    /** Converts the piece to non-colored enum, as used by Move. */
    inline unsigned char uncolor(unsigned char piece) {
        // just strip LSB.
        return piece >> 1;
    }
    /** Converts the piece from a non-colored enum to White. */
    inline unsigned char recolor(unsigned char piece) {
        // just add LSB of zero.
        return piece << 1;
    }


    //forward declaration so I can put ugly switch statement at the bottom of file
    unsigned char getCharFromEnum(unsigned char enumValue, char empty='.', char invalid='x'); 

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
            std::cout << "Material: {White: " << board->materialWhite << " Black: " << board->materialBlack << "}";
            break;
        case 6:
            std::cout << "Move history stack size: " << board->moveHistory.size();
            break;
        default:
            break;
        }
    }

    /** 
     * Prints the entire Board's array, including invalid spaces
     * Set info to true to also print all information about Board
     * Note that this will be vertically mirrored compared to what user (printBoard) would see.
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
     * Set flipped to true to see board from black's perspective
     */
    void printBoard(board::Board* board, bool flipped=false, bool info=false) {
        std::cout << "  +-----------------+" << std::endl;
        for (size_t r = 0; r < 8; r++) {
            // ranks top to bottom go 8->1 normally, reversed when flipped
            std::cout << (flipped? r+1 : 8-r) << " | ";
            for (size_t c = 0; c < 8; c++) { 
                if (flipped) 
                    // 21 is starting tile. +10*r means white at top. (7-c) means reverse columns
                    std::cout << getCharFromEnum(board->chessboard[21 + 10*r + (7-c)]) << " ";
                else
                    std::cout << getCharFromEnum(board->chessboard[91 - 10*r + c]) << " ";
            }
            std::cout << "|  ";
            if (info) printInfo(board, r);
            std::cout << std::endl;
        }
        std::cout << "  +-----------------+" << std::endl;
        if (flipped)
            // columns were reversed so their enumeration needs to be too
            std::cout << "    h g f e d c b a  " << std::endl;
        else
            std::cout << "    a b c d e f g h  " << std::endl;
    }

    // is there a better way to do this than just a big switch?
    /**
     * Gets char respresentation of piece type enum
     * OPTIONALLY set empty to desired character representation of EMPTY, 
     * OPTIONALLY set invalid to desired character representation of INVALID, 
     */
    unsigned char getCharFromEnum(unsigned char enumValue, char empty, char invalid) {
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
