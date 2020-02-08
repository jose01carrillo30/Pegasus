/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>

#include "constants.h"
#include "uci.cpp"

namespace uci_main_namespace{

    int main() {
        move_rep::init();
        uci::init();
        uci::loop();
        return 0;
    }
}