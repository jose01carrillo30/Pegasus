/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>

#include "uci.cpp"

namespace uci_main_namespace{

    int main() {
        std::cout << "[uci_main] Calling init" << std::endl;
        uci::init();
        std::cout << "[uci_main] Calling loop" << std::endl;
        uci::loop();
        return 0;
    }
}