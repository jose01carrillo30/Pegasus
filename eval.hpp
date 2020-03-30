// /* NOTE: this is my current implementation for the static evaluation function.
//  * for some reason, the project doesn't compile for me so i'm writing this separately,
//  * but designing it so that it could be directly plugged into pegasus :)
//  * 
//  * - ori
//  * 
//  * ANOTHER NOTE!!! WE SHOULD ADD A MATERIAL COUNT IN BOARD OBJECT TO AVOID REPEATED CALCULATION
// */

// #include <iostream> // won't be needed when plugged into pegasus

namespace eval {
// typedef unsigned char UC; // for convenience
// typedef unsigned int uint; // for convenience

// // straight from Pegasus:
// // enum {WP, BP, WR, BR, WN, BN, WB, BB, WQ, BQ, WK, BK, EMPTY, INVALID};

// // piece value list:
// // used as follows: PIECEVALUES[WP], for example
// // const uint PIECEVALUES[] = {100, -100, 500, -500, 300, -300, 300, -300, 900, -900, 10000, -10000, 0};

// struct Board {
//     // TEMPORARY STRUCT
//     unsigned char chessboard[120];
// };

// int evaluate(Board* b) {
//     int eval = 0;

//     int i = 21; // index64to120[0]
    
//     // loop over only the squares of the board:
//     UC x, y;
//     for (x = 0; x < 8; x++) {
//         for (y = 0; y < 8; y++) {
//             // add up material:
//             eval += PIECEVALUES[b->chessboard[i]];

//             // check for piece-specific threats
//             switch (b->chessboard[i]) {
//                 case EMPTY: break; // will occur most often
//                 case WP:
//                     // check: if the piece behind this is also a white pawn, deduct 50 points:
//                     if (b->chessboard[i+10] == WP) eval -= 50;
//                     break;
//                 case BP:
//                     // check: if the piece behind this is also a black pawn, deduct (add) 50 points:
//                     if (b->chessboard[i-10] == BP) eval += 50;
//                     break;
//             }

//             // increment index:
//             i++;
//         }

//         // skip invalid squares on sides:
//         i += 2;
//     }

//     return eval;
// }

int main() {
//     // again, temporary
//     Board b;
//     const char blah[] = {
//         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//         -1, BR, BN, BB, BQ, BK, BB, BN, BR, -1,
//         -1, BP, BP, BP, BP, BP, BP, BP, BP, -1,
//         -1, 12, 12, 12, 12, 12, 12, 12, 12, -1,
//         -1, 12, 12, 12, 12, 12, 12, 12, 12, -1,
//         -1, 12, 12, 12, 12, 12, 12, 12, 12, -1,
//         -1, 12, 12, 12, 12, 12, 12, 12, 12, -1,
//         -1, WP, WP, WP, WP, WP, WP, WP, WP, -1,
//         -1, WR, WN, WB, WQ, WK, WB, WN, WR, -1,
//         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
//         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
//     };
    
//     // copy 'blah' to chessboard
//     for (int i = 0; i < 120; i++) {
//         b.chessboard[i] = blah[i];
//     }

//     printf("static evaluation returned %d\n", evaluate(&b));
}
}