#ifndef SEARCH_HH
#define SEARCH_HH

#include <string>
#include <thread>
#include <vector>

#include "constants.hh"
#include "board_object.hh"
#include "move_representation.hpp"

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
        search(std::vector<Move> searchMoves);

        void operator()();

        /** Start search */
        void startSearch();

        /** Stop search and return results */
        searchResults endSearch();
};
}

#endif