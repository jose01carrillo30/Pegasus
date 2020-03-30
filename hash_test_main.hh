#ifndef HASH_TEST_MAIN_HH
#define HASH_TEST_MAIN_HH

#include "constants.hh"
#include "board_object.hh"

namespace hash_test_main_namespace {

    uint64_t randomHash(board::Board* board);
    uint64_t createHash(board::Board* board);
    int main();
}

#endif