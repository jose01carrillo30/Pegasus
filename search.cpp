#include <string>
#include <thread>
#include <vector>

#include "board_object.h"
#include "utilityMethods.h"
#include "move_representation.h"

class search {
    private:
        searchResults* results;
        bool isAlive;
    public:
        /** Initialize search */
        search(std::vector<MoveRepresentation::Move> searchMoves) {
            results = new searchResults{MoveRepresentation::Move(0,0,0,0,0,0,0)}; // placeholder
            //TODO:
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

/* results/statistics returned by search */
struct searchResults {
    MoveRepresentation::Move bestMove;
};
