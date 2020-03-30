#ifndef UCI_HH
#define UCI_HH
/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <thread>

#include "constants.hh"
#include "board_object.hh"
#include "utilityMethods.hh"
#include "search.hh"

namespace uci {

    static const std::string NAME = "Pegasus";
    static const std::string VERSION = "0.0";

    int init();
    void loop();
}
#endif