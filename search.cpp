#include <string>
#include <thread>
#include <vector>

#include "constants.hh"
#include "board_object.hh"
#include "utilityMethods.hh"
#include "move_representation.hpp"

#include "search.hh"

namespace searching {

search::search(std::vector<Move> searchMoves) {
    
}

void search::operator()() {
    //TODO:
    std::cout << "called from another thread" << std::endl;
}

/** Start search */
void search::startSearch() { 
    isAlive = true;
    //TODO: create thread
}

/** Stop search and return results */
searchResults search::endSearch() {
    isAlive = false; // kill thread
    //thread.join(); // wait for thread to end safely
    return *results;
}
}

