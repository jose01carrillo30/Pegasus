//
// Created by troyl on 11/6/2019.
//

//using "hash_test_main.cpp";

#include <string>
#include <iostream>

// Because of the weird namespacing, all includes for main files must be added here
#include "board_object_DEPRECIATED.h"

//hash_test_main.cpp includes
#include <stdlib.h>
#include <string>
#include <queue>
#include <limits>
#include <random>
#include "board_object.h"
#include "utilityMethods.h"


using namespace std;

void print_seperator(string txt){
    int length_text = txt.length();
    std::cout << "\n\n\n\n";

    //print 1st line of asterisks
    for(int i = 0; i < length_text + 10; i++){
        cout << "*";
    }
    cout << "\n";

    //print middle line
    cout << "**** " + txt + " ****\n";

    //print 2nd line of asterisks
    for(int i = 0; i < length_text + 10; i++){
        cout << "*";
    }
    cout << "\n\n";
}

//TODO: here is where you put the namespaces and includes
namespace hash_test_main_namespace{
    #include "hash_test_main.cpp"
}
namespace tablegen_namespace{
    #include "tablegen.cpp"
}
namespace tL_test_main_namespace{
    #include "tL_test_main.cpp"
}

//TODO: here is where you put the method call/main method/testing code along with a seperator
int main(int argc, char *argv[]) {
    string USAGE_ERROR = "Usage: " + string(argv[0]) + " [main_method_name.cpp]";

    bool run_all; // all main methods will execute if true
    string input_main = ""; // which main is the user calling
    switch (argc) {
    case 1: // user did not specify a main to run
        run_all = true;
        break;
    case 2: // user gave a main to run
        run_all = false;
        input_main = string(argv[1]);
        break;
    default: // user is confused
        cout << USAGE_ERROR << endl;
        return 1;
        break;
    }

    bool has_run = false;
    // GIANT main method so that the project would actually compile and run lol - Troy

    //------------------------------------------------------------------------------------------------------------------
    if (run_all || input_main == "hash_test_main.cpp") {
        print_seperator("Code from hash_test_main.cpp main() here");
        hash_test_main_namespace::mainRename_hash_test_main();
        has_run = true;
    }
    //------------------------------------------------------------------------------------------------------------------
    if (run_all || input_main == "tablegen.cpp") {
        print_seperator("Code from tablegen.cpp main() here");
        tablegen_namespace::mainRename_tablegen();
        has_run = true;
    }
    //------------------------------------------------------------------------------------------------------------------
    if (run_all || input_main == "tL_test_main.cpp") {
        print_seperator("Code from tL_test_main.cpp main() here");
        tL_test_main_namespace::mainRename_tL_test_main();
        has_run = true;
    }
    if (! has_run) { // input_main did not match any known main()
        cout << USAGE_ERROR << endl;
        return 1;
    }
    return 0;
}


