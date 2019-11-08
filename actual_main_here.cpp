//
// Created by troyl on 11/6/2019.
//

//using "hash_test_main.cpp";

#include <string>
#include <iostream>
#include "board_object.h"

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
int main(){
    // GIANT main method so that the project would actually compile and run lol - Troy

    //------------------------------------------------------------------------------------------------------------------
    print_seperator("Code from hash_test_main.cpp main() here");
    hash_test_main_namespace::mainRename_hash_test_main();

    //------------------------------------------------------------------------------------------------------------------
    print_seperator("Code from tablegen.cpp main() here");
    tablegen_namespace::mainRename_tablegen();

    //------------------------------------------------------------------------------------------------------------------
    print_seperator("Code from tL_test_main main() here");
    tL_test_main_namespace::mainRename_tL_test_main();
}


