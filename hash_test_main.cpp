#include <random>
#include <queue>
#include <limits>
#include <functional>
#include <iostream>
#include <stdlib.h>

#include "board_object.h"
#include "utilityMethods.h"

namespace hash_test_main_namespace {

    /** Initialize 64-bit RNG */
    std::random_device rd; //seed
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<uint64_t> distribution(0,0xFFFFFFFFFFFFFFFF); // Distribution on which to apply the generator

    int randomPosition() {
        return 21 + 10*(distribution(generator)%8) + (distribution(generator)%8);
    }

    class CompareHashes {
    public:
        bool operator() (board::Board* b1, board::Board* b2) {
            return b1->hashCode < b2->hashCode;
        }
    };

    uint64_t randomHash(board::Board* board) {
        /** Random number generator. Baseline to compare hashing to */
        return distribution(generator); // random 64-bit number
    }

    //TODO: I'm hoping the built in hashing will have more effecacy and efficiency than what I can come up with
    std::hash<uint64_t> uint_64_hasher; // hashes uint64_t into size_t
    std::hash<size_t> size_hasher; // hashes size_t into size_t

    uint64_t createHash(board::Board* board) { // TODO: move into board object once we have a sufficient method
        /** Hashes into 64 bits */
        uint64_t hash = 0;
        /* Pack all additional info into 16 bit number */
        hash += board->turnWhite << 0; // +1 bit, total 1
        hash += board->CBK << 1; // +1 bit, total 2
        hash += board->CBQ << 2; // +1 bit, total 3
        hash += board->CWK << 3; // +1 bit, total 4
        hash += board->CWQ << 4; // +1 bit, total 5
        hash += board->EP << 5; // +7 bit, total 12 //TODO: what are the values stored in EP? might need to do some transform to it depending on this
        // Map MSLC to 8 bits as follows: 1-7 for last 7 moves, 0 otherwise
        char MSLC = 50 + 1 - board->movesSinceLastCapture; //TODO: Am I off by one? Is 50 or 51 the largest value that can be stored into movesSinceLastCapture?
        if (MSLC > 7) MSLC = 0;  
        hash += MSLC << 12; // +3 bit, total 15

        /* Hash board positions */
        /* Break the chessboard data into 4 sections of 64 bits */
        for (short i = 0; i < 4; i++) { 
            // Each section is made up of 16 spaces, each space requiring 4 bits
            uint64_t section = 0;
            short cursor = 21 + 20*i; // set cursor to start of section. 21 is first space, 20*i is 2*i-th row
            for (short j = 0; j < 16; j++) {
                //cout << utility::getCharFromEnum(board->chessboard[cursor]) << " c:" << cursor << " j:" << j << endl;
                //utility::printBinary(uint64_t(board->chessboard[cursor]) << (4*j));
                section += uint64_t(board->chessboard[cursor++]) << (4*j); // add 4 bits of the space at cursor to section, no overlap
                //utility::printBinary(section);
                if (j % 8 == 7) cursor += 2; // skip invalids between rows
            }

            /* heart of the hash function here */

            // // Try to mix up the bits more? // No noticeable affect on collision rates
            // uint64_t mixed_section = 0;
            // char offset = 8*i;
            // mixed_section |= section << offset;
            // mixed_section |= section >> (64 - offset);
            // section = mixed_section;

            //hash ^= 199*section; //TODO: this is not a good enough hash. 7% collisions at 10 million random boards.
            //hash += 5*section; // 7% collions at 10 million random boards
            //hash ^= section; // still 7% collisions at 10 million random boards?

            // Okay, lets try something different
            hash += uint_64_hasher(section) + (hash << 32); // This is STILL 7% ?!
        }
        return hash;
    }

    typedef std::priority_queue<board::Board*, std::vector<board::Board*>, CompareHashes> board_queue;

    unsigned int num_test_boards; // how many random boards generated and tested
    unsigned int print_sample_size; // number of sample boards to print 
    /** 
     * Method to generate random boards to be tested. 
     * param customHash is function pointer to method used to hash boards
     */
    board_queue createSomeBoards(uint64_t (*customHash)(board::Board*)) {
    //void createSomeBoards() {
        //board::Board** boards = new board::Board*[num_test_boards];
        board_queue boards;

        for(uint64_t boardNum = 0; boardNum < num_test_boards; boardNum++)
        {
            board::Board* nextBoard = new board::Board(false, true); //TODO: stop leak
            // Generate random board
            const size_t pieces_length = 32; //size of array
            const unsigned char pieces[pieces_length] = { //first ones have lower priority since they will be overwritten
                board::BP,board::WP,board::BP,board::WP,board::BP,board::WP,board::BP,board::WP, // 4 pawns each 
                board::WN,board::BN,board::WN,board::BN, board::BB,board::WB,board::BB,board::WB, // Knights and bishops
                board::WR,board::BR,board::WR,board::BR, //Rooks
                board::BP,board::WP,board::BP,board::WP,board::BP,board::WP,board::BP,board::WP, // remaining 4 pawns
                board::BQ,board::WQ,board::WK,board::BK //queens and kings
            };
            for (size_t i = 0; i < pieces_length; i++)
                nextBoard->chessboard[randomPosition()] = pieces[i];

            // Initialize values (just so they are not garbage that will interfere with hashing)
            nextBoard->CBK = false;
            nextBoard->CBQ = false;
            nextBoard->CWK = false;
            nextBoard->CWQ = false;
            nextBoard->EP = 0;
            nextBoard->movesSinceLastCapture = distribution(generator) % 51; //random number from 0 to 50
            nextBoard->turnWhite = distribution(generator) % 2; // random boolean, probably overkill
            // Generate hash 
            nextBoard->hashCode = customHash(nextBoard);
            // store to queue for later
            boards.push(nextBoard);
        }
        return boards;
    }

    int main() {

        /* User selects which hash method to use */
        uint64_t (*hashFunction)(board::Board*) = nullptr; // 
        bool just_compare_boards = false; //option 3
        while (hashFunction == nullptr)  {
            std::cout << "Hash method? (type number of choice)" << std::endl
            << "1) randomHash()" << std::endl
            << "2) createHash()" << std::endl
            << "3) Just compare boards directly" << std::endl
            << ">";
            short response;
            std::cin >> response;
            switch (response)
            {
            case 1:
                hashFunction = &randomHash;
                break;
            case 2:
                hashFunction = &createHash;
                break;
            case 3:
                hashFunction = &createHash; // Assumes working hash function, i.e. that boards share hash iff they are same board
                just_compare_boards = true;
                break;
            default:
                std::cout << "invalid response. Please enter only the number of a given option." << std::endl;
                break;
            }
        }
        std::cout << "Please enter number of boards to test:" << std::endl
        << ">";
        std::cin >> num_test_boards;

        std::cout << "Please enter number of samples to print:" << std::endl
        << ">";
        std::cin >> print_sample_size;

        std::cout << "Generating " << utility::toCommaString(num_test_boards) << " boards..." << std::endl;

        //Create testboards using the selected function
        board_queue testBoards = createSomeBoards(hashFunction);

        int sample_step;
        if (print_sample_size > 0) {
            sample_step = num_test_boards / print_sample_size;
        }

        //TODO: would be nice if collision counting was more efficient
        std::cout << "Counting collisions..." << std::endl;
        int collisions = 0;
        board::Board* prev = nullptr;
        for(int i=0; !testBoards.empty(); i++) {
            if (print_sample_size > 0 && i % sample_step == 0) { // only show boards from sample
                std::cout << "board #" << i << ":" ;
                //utility::printBoardArray(testBoards.top());
                std::cout << testBoards.top()->hashCode / uint64_t(1000000000000000000); // print first two digits of decimal expansion
                std::cout << std::endl;
            }

            // Condition to be considered collision
            if (prev) { // only compare if prev != nullptr
                if (just_compare_boards) {
                    if (prev == testBoards.top()) { 
                        collisions++;
                    }
                } else { // if compare hashes
                    if (prev->hashCode == testBoards.top()->hashCode) {
                        collisions++;
                    }
                }
            }
            delete prev;
            prev = testBoards.top();
            testBoards.pop();
        }
        std::cout << "Collisions/Boards: " << collisions << " / " << num_test_boards << " ≈ " << collisions / (float) num_test_boards;
        //utility::printBoard(testBoards.pop());
        std::cout << std::endl;

        return 0;
    }
}