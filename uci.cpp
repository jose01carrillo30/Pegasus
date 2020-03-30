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

#include "uci.hh"

namespace uci {

    // only use colors if linux, doesn't print color codes properly for windows
    #ifdef __unix__
    static const std::string TITLE = 
        "\033[0;7;36m                                            \033[0m\n" // top border
        "\033[0;1;36m" // set colors of ascii art
        "  ____  ____  ___   __   ____  _  _  ____\n (  _ \\(  __)/ __) / _\\ / ___)/ )( \\/ ___) \n"
        "  ) __/ ) _)( (_ \\/    \\\\___ \\) \\/ (\\___ \\\n (__)  (____)\\___/\\_/\\_/(____/\\____/(____/\n\n"
        "\033[0;7;36m                Chess Engine                \033[0m\n\n"; // bottom border
    #else
    static const std::string TITLE = 
        "============================================\n" // top border
        "  ____  ____  ___   __   ____  _  _  ____\n (  _ \\(  __)/ __) / _\\ / ___)/ )( \\/ ___) \n"
        "  ) __/ ) _)( (_ \\/    \\\\___ \\) \\/ (\\___ \\\n (__)  (____)\\___/\\_/\\_/(____/\\____/(____/\n\n"
        "=============== Chess Engine ===============\n\n"; // bottom border
    #endif

    enum : char {UCI_MODE, CLI_MODE}; // possible interaction modes
    char interfaceMode; // which interaction mode is being used
    bool uciDebug = false; // debug must be off by default 

    /** Prints message when in debug mode. */
    void printDebug(std::string message) {
        if (uciDebug) {
            std::cout << "info string " << message << std::endl;
        }
    }

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
            std::string commandString;
            std::getline(std::cin, commandString);
            printDebug("Got line: " + commandString);

            std::stringstream ss(commandString);
            // tokenizer treats all non-newline whitespace as equal
            // tokenizer ignores unknown tokens, except for those between valid tokens of commands
            // ignores commands sent at wrong time/stage

            while (ss) {

                std::string commandToken;
                ss >> commandToken;
                printDebug("Got cmdToken: " + commandToken);

                /* quit the program as soon as possible */
                if (commandToken == "quit") {
                    printDebug("Quitting...");
                    // TODO: end all threads and exit the program
                    std::exit(EXIT_SUCCESS);

                /* acknowledge redundant call, already in uci mode */
                } else if (commandToken == "uci") {
                    uciok(); 

                /* In debug mode the engine should send additional infos to the GUI, e.g. with the "info string" command,
                to help debugging, e.g. the commands that the engine has received etc.
                This mode should be switched off by default and this command can be sent
                any time, also when the engine is thinking. */
                } else if (commandToken == "debug") {
                    std::string nextToken;
                    ss >> nextToken;
                    if (nextToken == "on") {
                        uciDebug = true;
                    } else if (nextToken == "off") {
                        uciDebug = false;
                    }

                /* used to wait for the engine to be ready again or
                to ping the engine to find out if it is still alive */
                } else if (commandToken == "isready") {
                    printDebug("calling isReady");
                    // TODO: 
                    std::cout << "readyok" << std::endl;

                /*  */
                } else if (commandToken == "setoption") {
                    printDebug("calling setOption");
                    // TODO:

                /*  */
                } else if (commandToken == "register") {
                    printDebug("calling register");
                    // TODO:

                /*  */
                } else if (commandToken == "ucinewgame") {
                    printDebug("calling uciNewGame");
                    // TODO:

                /*  */
                } else if (commandToken == "position") {
                    printDebug("calling position");
                    std::string nextToken;
                    ss >> nextToken;
                    if (nextToken == "fen") {
                        printDebug("parsing fen");
                        ss >> nextToken;
                        // TODO: parse fen string
                    } else if (nextToken == "startpos") {
                        printDebug("using start postition");
                        // TODO: init to starting board
                    } else {
                        printDebug("invalid position command, ignoring");
                        continue; // invalid position command
                    }

                    ss >> nextToken;
                    if (nextToken == "moves") {
                        printDebug("parsing algrebriac");
                        while (ss) {
                            ss >> nextToken;
                            // TODO: parse algebra string
                        }
                        break;
                    } else {
                        // no moves were given
                        printDebug("no moves given");
                        /* This token following position command will be consumed, but since we only
                           need to parse one command from each line, this is probably ok. */
                    }

                /* start calculating on the current position set up with the "position" command. */
                } else if (commandToken == "go") {
                    std::string nextToken;
                    for (ss >> nextToken; ss; ss >> nextToken) {
                        /* restrict search to these moves only */
                        if (nextToken == "searchmoves") {
                            printDebug("searchmoves");
                            while (ss) { // loop until end of line or break
                                ss >> nextToken;
                                // TODO: parse algebra string

                                // if (token is not valid algebraic) {
                                //      recycle token;
                                //      break;
                                // }
                            }

                        /* start searching in pondering mode. */
                        } else if (nextToken == "ponder") {
                            printDebug("ponder");
                            // TODO:

                        /* white has x msec left on the clock */
                        } else if (nextToken == "wtime") {
                            printDebug("wtime");
                            int x;
                            ss >> x;
                            // TODO:
                        /* black has x msec left on the clock */
                        } else if (nextToken == "btime") {
                            printDebug("btime");
                            int x;
                            ss >> x;
                            // TODO:

                        /* white increment per move in mseconds if x > 0 */
                        } else if (nextToken == "winc") {
                            printDebug("winc");
                            int x;
                            ss >> x;
                            // TODO:
                        /* black increment per move in mseconds if x > 0 */
                        } else if (nextToken == "binc") {
                            printDebug("binc");
                            int x;
                            ss >> x;
                            // TODO:

                        /* there are x moves to the next time control,
                        this will only be sent if x > 0,
                        if you don't get this and get the wtime and btime it's sudden death */
                        } else if (nextToken == "movestogo") {
                            printDebug("movestogo");
                            int x;
                            ss >> x;
                            // TODO:

                        /* search x plies only */
                        } else if (nextToken == "depth") {
                            printDebug("depth");
                            int x;
                            ss >> x;
                            // TODO:
                        /* search x nodes only */
                        } else if (nextToken == "nodes") {
                            printDebug("nodes");
                            int x;
                            ss >> x;
                            // TODO:

                        /* search for a mate in x moves */
                        } else if (nextToken == "mate") {
                            printDebug("mate");
                            int x;
                            ss >> x;
                            // TODO:

                        /* search exactly x mseconds. */
                        } else if (nextToken == "movetime") {
                            printDebug("movetime");
                            int x;
                            ss >> x;
                            // TODO:

                        /* search until the "stop" command. */
                        } else if (nextToken == "infinite") {
                            printDebug("infinite");
                            // TODO:

                        /* invalid token as go command */
                        } else {
                            break;
                        }
                        //searching::search* calculation = new searching::search(std::vector<Move>{});
                        //std::thread calcThread(*calculation); // TODO: join or detatch threads
                    }
                /* stop calculating as soon as possible */
                } else if (commandToken == "stop") {
                    // TODO:
                    // TODO: don't forget the "bestmove" and possibly the "ponder" token when finishing the search

                /* the user has played the expected move. This will be sent if the engine was told to ponder on the same move
                 the user has played. The engine should continue searching but switch from pondering to normal search. */
                } else if (commandToken == "ponderhit") {
                    // TODO:

                } else {
                    // do nothing for leading invalid token
                }
            }
        }
    }
}