#include <string>
#include <thread>
#include <vector>

#include "constants.h"
#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

namespace searching {


/* results/statistics returned by search */
struct searchResults {
    Move bestMove;
    //TODO: add other stuff too
};

class search {
    private:
        searchResults* results;
        bool isAlive;
    public:
        /** Initialize search */
        search(std::vector<Move> searchMoves) {
            
        }

        void operator()() {
            //TODO:
            std::cout << "called from another thread" << std::endl;
        }

        /** Start search */
        void startSearch() { 
            isAlive = true;
            //TODO: create thread
        }

        /** Stop search and return results */
        searchResults endSearch() {
            isAlive = false; // kill thread
            //thread.join(); // wait for thread to end safely
            return *results;
        }
};
}
