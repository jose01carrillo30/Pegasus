//
// Created by troyl on 11/8/2019.
//

#ifndef PEGASUS_STUFF_KING_MOVE_GEN_H
#define PEGASUS_STUFF_KING_MOVE_GEN_H

#include <string>
#include "board_object.h"
#include "utilityMethods.h"

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
    const ULL leftBoardWipe = 17361641481138401520LL;
    const ULL rightBoardWipe = leftBoardWipe >> 4u;

    static void test(){
//        std::string ans;

        std::cout << "1 Mask:\n";
        utility::printBitboard(kingMoveMask);
        std::cout << "\n";

        std::cout << "2 Right:\n";
        utility::printBitboard(rightBoardWipe);
        std::cout << "\n";

        std::cout << "3 Left:\n";
        utility::printBitboard(leftBoardWipe);
        std::cout << "\n";

        std::cout << "4 Mask leftshifted by 2:\n";
        utility::printBitboard(kingMoveMask << 2);
        std::cout << "\n";

        std::cout << "5 Mask leftshifted by 8:\n";
        utility::printBitboard(kingMoveMask << 8);
        std::cout << "\n";
//        ans += "1:\n" + utility::printBitboardU(kingMoveMask) + "\n";
//
//        ans += "2:\n" + utility::printBitboardU(rightBoardWipe) + "\n";
//
//        ans += "3:\n" + utility::printBitboardU(leftBoardWipe) + "\n";

//        return ans;
    }
};

#endif //PEGASUS_STUFF_KING_MOVE_GEN_H
