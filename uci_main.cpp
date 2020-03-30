#include <string>
#include <iostream>

#include "constants.hh"
#include "uci.hh"

#include "uci_main.hh"

namespace uci_main_namespace{

    int main() {
        move_rep::init();
        uci::init();
        uci::loop();
        return 0;
    }
}