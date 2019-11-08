//
// Created by troyl on 11/8/2019.
//

#include <iostream>
#include "move_representation.h"
#include "king_move_gen.h"
#include "board_object.h"

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

int mainRename_tL_test_main() {
//    cout << "Hello, World!\n";
//    char a[5];
//    string hi = "dsadasd";
//    bool b = true;
//    cout << b;
//    cout << "\n";
//    test::hello(999);

//    cout << "Beginning test\n";
//    unsigned long num1 = MoveRepresentation::encodeMove(0, 0, 0, 0, 0, 0, 0);
//    std::bitset<32> x(num1);
//    cout << "Num:\n" << x << "\n";
//
//    unsigned long num2 = MoveRepresentation::encodeMove(4, 0, 0, 0, 0, 0, 0);
//    std::bitset<32> x2(num2);
//    cout << "Num2:\n" << x2 << "\n";
//
//    unsigned long num3 = MoveRepresentation::encodeMove(0, 1, 2, 3, 4, 5, 6);
//    std::bitset<32> x3(num3);
//    cout << "Num3:\n" << x3 << "\n";
//    for(int i = 0; i < sizeof(MoveRepresentation::ranges) / sizeof(MoveRepresentation::ranges[0]); i++){
//        cout << MoveRepresentation::decodeItem(num3, i) << ", ";
//    }

    Board reeee = Board();
    ULL *boardsOut = reeee.bitboards;

    std::cout << "\n\nHIIIIhjh\n\n";
//    std::string test;
//    test += "51";
//    std::cout << test;
    kingMoveGeneration::test();

    return 0;
}