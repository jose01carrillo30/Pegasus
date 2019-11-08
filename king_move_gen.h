//
// Created by troyl on 11/8/2019.
//

#ifndef PEGASUS_STUFF_KING_MOVE_GEN_H
#define PEGASUS_STUFF_KING_MOVE_GEN_H

#include <string>
#include "board_object.h"

namespace kingMoveGeneration{
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 0 0 0
    //    0 0 0 0 0 1 1 1
    //    0 0 0 0 0 1 1 1
    //    0 0 0 0 0 1 1 1
    // assuming bottom right is 0
    const ULL kingMoveMask = 460551LL;
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    //    1 1 1 1 0 0 0 0
    // for use in removing wrapping problems
    const ULL rightBoardWipe = 17361641481138401520LL;
    const ULL leftBoardWipe = rightBoardWipe >> 4u;

    static void test(){
//        std::string ans;

        std::cout << "1:\n";
        printBits(kingMoveMask);
        std::cout << "\n";

        std::cout << "2:\n";
        printBits(rightBoardWipe);
        std::cout << "\n";

        std::cout << "3:\n";
        printBits(leftBoardWipe);
        std::cout << "\n";
//        ans += "1:\n" + printBits(kingMoveMask) + "\n";
//
//        ans += "2:\n" + printBits(rightBoardWipe) + "\n";
//
//        ans += "3:\n" + printBits(leftBoardWipe) + "\n";

//        return ans;
    }
};

#endif //PEGASUS_STUFF_KING_MOVE_GEN_H
