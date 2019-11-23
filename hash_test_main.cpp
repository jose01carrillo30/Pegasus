/*
 * Can't include anything here for some reason to do with the namespacing done in actual_main_here,
 * so all includes have been moved to actual_main_here.cpp
 */

using namespace std;

/** Initialize 64-bit RNG */
random_device rd; //seed
default_random_engine generator(rd());
uniform_int_distribution<uint64_t> distribution(0,0xFFFFFFFFFFFFFFFF); // Distribution on which to apply the generator

int randomPosition() {
    return 21 + 10*(distribution(generator)%8) + (distribution(generator)%8);
}

class CompareHashes {
public:
    bool operator() (board::Board* b1, board::Board* b2) {
        return b1->hashCode < b2->hashCode;
    }
};

board::Board* createFromFenn(string fenn) {
    /** TODO: enpassant and move clocks */
    board::Board* fennBoard = new board::Board(false, true);
    bool isSpace = false;
    fennBoard->CWK = false;
    fennBoard->CBK = false;
    fennBoard->CWQ = false;
    fennBoard->CBQ = false;
    
    int boardIndex = 0;

    for (char c : fenn){

        while (fennBoard->chessboard[boardIndex] == board::INVALID){
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
                if (isSpace)
                    fennBoard->turnWhite = false;
                else {
                    fennBoard->chessboard[boardIndex] = board::BB;
                    boardIndex++;
                }
                break;

            case 'Q':
                if(isSpace)
                    fennBoard->CWQ = true;
                else{
                    fennBoard->chessboard[boardIndex] = board::WQ;
                    boardIndex++;
                }
                break;

            case 'q':
                if(isSpace)
                    fennBoard->CBQ = true;
                else{
                    fennBoard->chessboard[boardIndex] = board::BQ;
                    boardIndex++;
                }
                break;

            case 'K':
                if(isSpace)
                    fennBoard->CWK = true;
                else{
                    fennBoard->chessboard[boardIndex] = board::WK;
                    boardIndex++;
                }
                break;

            case 'k':
                if(isSpace)
                    fennBoard->CBK = true;
                else{
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
                boardIndex+=2;
                break;

            case '3':
                boardIndex+=3;
                break;

            case '4':
                boardIndex+=4;
                break;

            case '5':
                boardIndex+=5;
                break;

            case '6':
                boardIndex+=6;
                break;

            case '7':
                boardIndex+=7;
                break;

            case '8':
                boardIndex+=8;
                break;

            case ' ':
                isSpace = true;
                break;

            case 'w':
                fennBoard->turnWhite = true;
                break;

            default:
                std::cout << "Invalid character in FEN string" << endl;

        }

    }
}

uint64_t randomHash() {
    /** Random number generator. Baseline to compare hashing to */
    //return rand() % numeric_limits<uint64_t>::max(); // Uniform random distribution of numbers within bounds
    return distribution(generator);
}
uint64_t createHash(board::Board* board) {
    /** TODO: Hashes into 64 bits */
    return 420; //TODO: temporary
    for (size_t r = 0; r < 8; r++) { // Loop over valid spaces
        size_t R = 10*r; // row offset
        for (size_t c = 0; c < 8; c++) { 
            //board->chessboard[21 + R + c]
        }

    }
}

typedef priority_queue<board::Board*, std::vector<board::Board*>, CompareHashes> board_queue;

//#define NUM_TEST_BOARDS 3
#define NUM_TEST_BOARDS 10000000
/** Method to generate boards to be tested */
board_queue createSomeBoards() {
//void createSomeBoards() {
    //board::Board** boards = new board::Board*[NUM_TEST_BOARDS];
    board_queue boards;

    for(uint64_t boardNum = 0; boardNum < NUM_TEST_BOARDS; boardNum++)
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
        // Generate hash 
        //nextBoard->hashCode = createHash(nextBoard); //Change which of these is commented out to select them
        nextBoard->hashCode = randomHash();
        // store to queue for later
        boards.push(nextBoard);
    }
    return boards; //TODO:
}

//TODO: renamed and run from "actual_main_here.cpp"
int mainRename_hash_test_main() {

    cout << "Generating " << utility::toCommaString(NUM_TEST_BOARDS) << " random boards..." << endl;
    board_queue testBoards = createSomeBoards();

    cout << "Counting collisions..." << endl;
    int collisions = 0;
    board::Board* prev = nullptr;
    for(int i=0; !testBoards.empty(); i++) {
        if (NUM_TEST_BOARDS < 10) { // only show boards if very small batch
            utility::printBoardArray(testBoards.top());
        }
        //cout << endl;
        if (prev && prev->hashCode == testBoards.top()->hashCode) {
            collisions++;
            // utility::printBoardArray(testBoards.top());
            // cout << endl;
            // utility::printBoardArray(prev);
            // cout << endl;
        }
        delete prev;
        prev = testBoards.top();
        testBoards.pop();
    }
    cout << "Collisions/Boards: " << collisions << " / " << NUM_TEST_BOARDS << " ≈ " << collisions / (float) NUM_TEST_BOARDS;
    //utility::printBoard(testBoards.pop());
    cout << endl;

    return 0;
}

