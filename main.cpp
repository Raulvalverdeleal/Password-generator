#include "handler.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    extern Handler handler;

    if ((argv[1][0] != '-') && (argc > 1 && argc < 5) && (argc == 2 || argc == 4)) {
        //i -> pw <key> || -file <file_name>
        handler.validateValue( argv[1], 2);
        if ( argc > 3 && std::string(argv[3]).compare("-file") == 0 ) handler.validateValue( argv[3], 3);
        handler.takeAction( 1 );
    } else if ( (argc > 6 && argc < 10) && std::string(argv[1]).compare("-t") == 0 && std::string(argv[3]).compare("-s") == 0 && std::string(argv[5]).compare("-k") == 0 ) {
        //i -> pw -t <text> -s <seed> -k <key> || -file <file_name>
        handler.validateValue( argv[2], 0);
        handler.validateValue( argv[4], 1);
        handler.validateValue( argv[6], 2);
        if ( argc > 7 && std::string(argv[7]).compare("-file") == 0 ) handler.validateValue( argv[8], 3);
        handler.takeAction( 2 );
    } else if ( (argc > 2 && argc < 6) && std::string(argv[1]).compare("-delete") == 0 && (argc == 3 || argc == 5) ){
        //i-> pw -delete <key> || -file <file_name>
        handler.validateValue( argv[2], 2);
        if ( argc > 3 && std::string(argv[3]).compare("-file") == 0 ) handler.validateValue( argv[4], 3);
        handler.takeAction(3);
    } else if ( (argc > 1 && argc < 5) && std::string(argv[1]).compare("-delete") == 0 && (argc == 2 || argc == 4)){
        //i-> pw -delete || -file <file_name>
        if ( argc > 2 && std::string(argv[2]).compare("-file") == 0 ) handler.validateValue( argv[3], 3);
        handler.takeAction(4);
    } else if ( (argc > 1 && argc < 5) && std::string(argv[1]).compare("-list") == 0 && (argc == 2 || argc == 4)) {
        //i-> pw -list || -file <file_name>
        if ( argc > 2 && std::string(argv[2]).compare("-file") == 0 ) handler.validateValue( argv[3], 3);
        handler.takeAction(5);

    } else if ( (argc > 1 && argc < 3) && (std::string(argv[1]).compare("-h") == 0 || std::string(argv[1]).compare("-help") == 0)) {
        std::cout
        << "\n\033[1;90m---   PARAMS USE   ---\n\n\033[1;90m"
        << "-k <key>\n-> \033[0mLooks for a key in the default file \033[1;90m./jsons/default.json\033[0m, returns its value, and copies it to the clipboard.\033[1;90m\n\n"
        << "-k <key> -file <file_name>\n-> \033[0mLooks for a key in the specified file \033[1;90m./jsons/file_name.json\033[0m, returns its value, and copies it to the clipboard.\033[1;90m\n\n"
        << "-t <password> -s <seed> -k <key>\n-> \033[0mAdds a new item in the default file \033[1;90m./jsons/default.json\033[0m, returns its value, and copies it to the clipboard.\033[1;90m\n\n"
        << "-t <password> -s <seed> -k <key> -file <file_name>\n-> \033[0mAdds a new item in the specified file \033[1;90m./jsons/file_name.json\033[0m, returns its value, and copies it to the clipboard.\033[1;90m\n\n"
        << "-delete <key>\n-> \033[0mLooks for a key and delete it in \033[1;90m./jsons/default.json\033[1;90m\n\n"
        << "-delete <key> -file <file_name>\n-> \033[0mLooks for a key and delete it in \033[1;90m./jsons/file_name.json\033[1;90m\n\n"
        << "-delete\n-> \033[0mDeletes all \033[1;90m./jsons/\033[1;90m content.\n\n"
        << "-delete -file <file_name>\n-> \033[0mDeletes \033[1;90m./jsons/file_name.json\033[1;90m\n\n"
        << "-list\n-> \033[0mReads all keys stored in \033[1;90m./jsons/\n\n"
        << "-list -file <file_name>\n-> \033[0mReads all keys stored in \033[1;90m./jsons/file_name.json\033[0m\n\n";
    } else {
        std::cout << "\n\033[1;31mError: \033[0m param combination not found, enter \033[1;90m-h\033[0m or \033[1;90m-help\033[0m for help.\n\n";
    }

    return 0;
}
