/** 
 * The main main method, called by the actual main method
 */

#include <string>
#include <iostream>

namespace uci_main_namespace{

    const std::string NAME = "Pegasus";
    const std::string VERSION = "0.0";
    const std::string TITLE = 
        "\033[0;7;36m                                            \n" // top border
        "\033[0;1;36m" // set colors of ascii art
        "  ____  ____  ___   __   ____  _  _  ____\n (  _ \\(  __)/ __) / _\\ / ___)/ )( \\/ ___) \n"
        "  ) __/ ) _)( (_ \\/    \\\\___ \\) \\/ (\\___ \\\n (__)  (____)\\___/\\_/\\_/(____/\\____/(____/\n\n"
        "\033[0;7;36m                Chess Engine                \n\n" // bottom border
        "\033[0m"; // reset colors

    enum : char {UCI_MODE, CLI_MODE};
    char interfaceMode; // which interaction mode is being used
    bool uciDebug = false; // debug must be off by default 

    int main() {
        std::cout << TITLE;
        std::string command = "";

        /* Start up */
        // wait for uci
        while (command == "") {
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
            // send id command
            std::cout << "id name " << NAME << " " << VERSION << std::endl;
            std::cout << "id author Pegasus Team" << std::endl; //TODO: what is our name/author?

            // send options command
            //cout << "option name " << // TODO: add options as needed

            // send uciok
            std::cout << "uciok" << std::endl;
            break;
        
        case CLI_MODE:
            std::cout << "cli selected" << std::endl; 
            //TODO:
            break;
        }

        /* Main loop */
        // Wait for isready or setoption
            // Respond to isready with readyok when appropriate

        // only begin calculating when go command is recieved
        // should be threaded so that it can still recieve input while thinking
        return 0;
    }
    // tokenizer treats all non-newline whitespace as equal
    // tokenizer ignores unknown tokens, except for those between valid tokens of commands
    // ignores commands sent at wrong time/stage
    // OwnBook option
    // debug [on|off] can be sent at any time. Toggles sending 'info string' commands
    // 
}