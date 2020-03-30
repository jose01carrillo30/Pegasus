CXX = g++
CPPFLAGS = -Wall -Wno-unused-function -std=c++11
OBJECTS = hash_test_main.o uci_main.o uci.o board_object.o utilityMethods.o

all : clean actual_main_here #FIXME: doing clean like this until enough is taken out of hpp dependencies

actual_main_here: actual_main_here.o $(OBJECTS)
	$(CXX) $(CPPFLAGS) $^ -o Pegasus.exe

# # ### format for the following header include rules: ###
# <files which include the header> : <the header> <list of files the header includes>
hash_test_main.o : FEN.hpp
hash_test_main.o : move_representation.hpp
uci_main.o : uci.hh

# I think it is safe to assume everything uses these (change if otherwise)
*.o : constants.hh board_object.hh utilityMethods.hh

.PHONY : clean

clean:
	rm -rf *.o
	rm -f *.exe
	rm -f *.stackdump