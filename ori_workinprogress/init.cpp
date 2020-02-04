#ifndef INIT_H
#define INIT_H

// function declarations go here:
void initAll();
void initArrays();

// function that will be called by main() at startup to initialize everything at once:
void initAll() {
  initArrays();
}

// initializes the index conversion arrays:
void initArrays() {
  // Populate our arrays with values:
  for (int i = 0; i < 120; i++) {
    idx120to64[i] = 65; // 65 = INVALID
  }

  for (int i = 0; i < 64; i++) {
    idx64to120[i] = 120;
  }

  unsigned int numSquare = 0;
  for (int rank = 0; rank <= 7; rank++) {
    for (int file = 0; file <= 7; file++) {
      int sq = SquareConvert(file, rank); // SquareConvert is a macro defined in FEN.h
      idx64to120[numSquare] = sq;
      idx120to64[sq] = numSquare++;
    }
  }
}

#endif
