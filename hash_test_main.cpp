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

<<<<<<< HEAD
Board* createFromFenn(string fenn) {
    /** TODO: */
    
    
    int boardIndex = 0;

    for (char c : fenn){

        switch(c) {

            case 'P':
                

            case 'p':

            case 'R':

            case 'r':

            case 'N':

            case 'n':

            case 'B':

            case 'b':

            case 'Q':

            case 'q':

            case 'K':

            case 'k':

            case '/':

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

            default:
                cout << "Invalid character in FEN string" << endl;

        }

    }
    
    
    

    //TODO
    return nullptr;
=======
uint64_t createHash(board::Board* board) {
    /** TODO: Hashes into 64 bits */
    return 420 * rand() % uint64_t(69420000); //TODO: temporary
>>>>>>> f5381579583c0a29f44c3547ba68f7ed319bdb51
}

typedef priority_queue<board::Board*, std::vector<board::Board*>, CompareHashes> board_queue;

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
        const string pieces = "ppppPPPPnnNNbbBBrrRRppppPPPPqQkK";
        for (size_t i = 0; i < pieces.length(); i++)
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

