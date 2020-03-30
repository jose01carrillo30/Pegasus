CXX = g++
CPPFLAGS = -Wall -Wno-unused-function -std=c++11

all : actual_main_here

# TODO: I'm sorry I had to do it this way. Really I want to have multiple executeable files,
# then we could restructure to avoid this madness.
actual_main_here: clean actual_main_here.o
	$(CXX) $(CPPFLAGS) actual_main_here.o -o Pegasus.exe

# TODO: one day, maybe, when we stop avoiding the linker, we will implement some rules
# # commonly included files
# PEGASUS_INCLUDES = board_object.hh utilityMethods.hpp move_representation.hpp
# # ### format for the following header include rules: ###
# # <files which include the header> : <the header> <list of files the header includes>
# uci.o test_moves_main.o search.o hash_test_main.o : board_object.hh 
# test_moves_main.o hash_test_main.o : FEN.hpp board_object.hh
# test_moves_main.o search.o : move_representation.hpp board_object.hh
# uci.o tL_test_main.o test_moves_main.o search.o hash_test_main.o : utilityMethods.hpp board_object.hh
# : bishopMoveGen.hpp $(PEGASUS_INCLUDES)
# : kingMoveGen.h $(PEGASUS_INCLUDES)
# : knightMoveGen.h $(PEGASUS_INCLUDES)
# test_moves_main.o : moveMaker.hpp $(PEGASUS_INCLUDES)
# : pawnMoveGen.h $(PEGASUS_INCLUDES)
# : queenMoveGen.hpp $(PEGASUS_INCLUDES)
# : rookMovGen.hpp $(PEGASUS_INCLUDES)
# # I think it is safe to assume everything uses the constants.hh
# *.o : constants.hh 

.PHONY : clean

clean:
	rm -rf *.o
	rm -f *.exe
	rm -f *.stackdump