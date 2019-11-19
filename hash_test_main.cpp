/*
 * Can't include anything here for some reason to do with the namespacing done in actual_main_here,
 * so all includes have been moved to actual_main_here.cpp
 */

using namespace std;

int randomPosition() {
    return 21 + 10*(rand()%8) + (rand()%8);
}

class CompareHashes {
public:
    bool operator() (board::Board* b1, board::Board* b2) {
        return b1->hashCode < b2->hashCode;
    }
};

uint64_t createHash(board::Board* board) {
    /** TODO: Hashes into 64 bits */
    return 420 * rand() % uint64_t(69420000); //TODO: temporary
}

typedef priority_queue<board::Board*, std::vector<board::Board*>, CompareHashes> board_queue;

//#define NUM_TEST_BOARDS 3
#define NUM_TEST_BOARDS 3000000
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
        nextBoard->hashCode = createHash(nextBoard);
        // store to queue for later
        boards.push(nextBoard);
    }
    return boards; //TODO:
}

//TODO: renamed and run from "actual_main_here.cpp"
int mainRename_hash_test_main() {
    srand(time(NULL));

    cout << "Generating " << NUM_TEST_BOARDS << " random boards..." << endl;
    board_queue testBoards = createSomeBoards();

    cout << "Counting collisions..." << endl;
    int collisions = 0;
    board::Board* prev = nullptr;
    for(int i=0; !testBoards.empty(); i++) {
        //utility::printBoardArray(testBoards.top());
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

