/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>

#include "uci.cpp"

namespace uci_main_namespace{

    int main() {
        uci::init();
        uci::loop();
        return 0;
    }
}