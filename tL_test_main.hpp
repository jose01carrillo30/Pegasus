#ifndef TL_TEST_MAIN_HPP
#define TL_TEST_MAIN_HPP

#include <iostream>

#include "constants.hh"
#include "move_representation.hpp"
#include "kingMoveGen.hpp"

namespace tL_test_main_namespace{

    class test{
        private:
        enum : unsigned char {startPos, endPos, castle, enPassant, capture, promote};
        constexpr static int a[6] = {1, 2, 3, 4, 5, 6};
        public:
        static void hello(short castle){
            std::cout << castle << "\n";
            std::cout << a[test::castle];
        }
    };

    int main() {
    //    cout << "Hello, World!\n";
    //    char a[5];
    //    string hi = "dsadasd";
    //    bool b = true;
    //    cout << b;
    //    cout << "\n";
    //    test::hello(999);

    //    cout << "Beginning test\n";
    //    unsigned long num1 = move_rep::encodeMove(0, 0, 0, 0, 0, 0, 0);
    //    std::bitset<32> x(num1);
    //    cout << "Num:\n" << x << "\n";
    //
    //    unsigned long num2 = move_rep::encodeMove(4, 0, 0, 0, 0, 0, 0);
    //    std::bitset<32> x2(num2);
    //    cout << "Num2:\n" << x2 << "\n";
    //
    //    unsigned long num3 = move_rep::encodeMove(0, 1, 2, 3, 4, 5, 6);
    //    std::bitset<32> x3(num3);
    //    cout << "Num3:\n" << x3 << "\n";
    //    for(int i = 0; i < sizeof(move_rep::ranges) / sizeof(move_rep::ranges[0]); i++){
    //        cout << move_rep::decodeItem(num3, i) << ", ";
    //    }

        std::cout << "\n\nHIIIIhjh\n\n";
    //    std::string test;
    //    test += "51";
    //    std::cout << test;
        kingMoveGeneration::test();

        return 0;
    }
}

#endif