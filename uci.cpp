/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>

#include "board_object.h"
#include "utilityMethods.h"

namespace uci {

    const std::string NAME = "Pegasus";
    const std::string VERSION = "0.0";
    const std::string TITLE = 
        "\033[0;7;36m                                            \n" // top border
        "\033[0;1;36m" // set colors of ascii art
        "  ____  ____  ___   __   ____  _  _  ____\n (  _ \\(  __)/ __) / _\\ / ___)/ )( \\/ ___) \n"
        "  ) __/ ) _)( (_ \\/    \\\\___ \\) \\/ (\\___ \\\n (__)  (____)\\___/\\_/\\_/(____/\\____/(____/\n\n"
        "\033[0;7;36m                Chess Engine                \n\n" // bottom border
        "\033[0m"; // reset colors

    enum : char {UCI_MODE, CLI_MODE}; // possible interaction modes
    char interfaceMode; // which interaction mode is being used
    bool uciDebug = false; // debug must be off by default 

    void uciok() {
        std::cout << "id name " << NAME << " " << VERSION << std::endl;
        std::cout << "id author Pegasus Team" << std::endl; //TODO: what is our name/author?

        // send options commands
        //cout << "option name " << // TODO: add options as needed

        std::cout << "uciok" << std::endl;
    }

    int init() {
        std::cout << TITLE;
        std::string command = "";

        /* Start up */
        // wait for uci
        while (command == "") { // loop until valid selection
            std::cout << "Select mode by entering it's command below:" << std::endl;
            std::cout << "<cli> Command line user-friendly interface. Intended for human use." << std::endl;
            std::cout << "<uci> Universal chess interface. Intended for use by other programs." << std::endl;
            std::cout << "> ";
            std::cin >> command;
            if (command == "cli") {
                interfaceMode = CLI_MODE;
                break;
            } else if (command == "uci") {
                interfaceMode = UCI_MODE;
                break;
            } else {
                std::cout << "invalid selection, please try again" << std::endl << std::endl;
                command = "";
            }            
        }

        /* Initialization */
        switch (interfaceMode)
        {
        case UCI_MODE:
            uciok();
            break;
        
        case CLI_MODE:
            std::cout << "cli selected" << std::endl; 
            //TODO:
            break;
        }

        return 0;
    }

    /* Main loop */
    void loop() { // TODO: threading
        for (;;) {
            // tokenizer treats all non-newline whitespace as equal
            // tokenizer ignores unknown tokens, except for those between valid tokens of commands
            // ignores commands sent at wrong time/stage

            std::string commandToken;
            std::cin >> commandToken;
            if (commandToken == "quit") {
                // TODO:
                break;
            } else if (commandToken == "uci") {
                uciok(); // Already in uci mode
            } else if (commandToken == "debug") {
                std::string nextToken;
                std::cin >> nextToken;
                if (nextToken == "on") {
                    uciDebug = true;
                } else if (nextToken == "off") {
                    uciDebug = false;
                }
            } else if (commandToken == "isready") {
                // TODO:
            } else if (commandToken == "setoption") {
                // TODO:
            } else if (commandToken == "register") {
                // TODO:
            } else if (commandToken == "ucinewgame") {
                // TODO:
            } else if (commandToken == "position") {
                // TODO:
            } else if (commandToken == "go") {
                // TODO:
            } else if (commandToken == "stop") {
                // TODO:
            } else if (commandToken == "ponderhit") {
                // TODO:
            } else {
                // do nothing for leading invalid token
            }
        }
    }

    // tokens: 
    // Wait for isready or setoption
        // Respond to isready with readyok when appropriate

    // only begin calculating when go command is recieved
    // should be threaded so that it can still recieve input while thinking

    // OwnBook option
    // debug [on|off] can be sent at any time. Toggles sending 'info string' commands
    // 
}