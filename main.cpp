#include "handler.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    extern Handler handler;

    if ((argc == 2 || argc == 4) && (argv[1][0] != '-')) {
        //i -> pg <key> || -file <file_name>
        handler.validateValue( argv[1], 2);
        if ( argc > 3 && std::string(argv[3]).compare("-file") == 0 ) handler.validateValue( argv[3], 3);
        handler.takeAction( 1, true );

    } else if ((argc == 3 || argc == 5) && std::string(argv[1]).compare("-u")==0) {
        //i-> pg -u <key>|| -file <file_name>
        handler.validateValue( argv[2], 2);
        if ( argc > 3 && std::string(argv[3]).compare("-file") == 0 ) handler.validateValue( argv[4], 3);
        handler.takeAction( 2, true );

    }else if ((argc == 7 || argc == 9) && std::string(argv[1]).compare("-t") == 0 && std::string(argv[3]).compare("-s") == 0 && std::string(argv[5]).compare("-k") == 0 ) {
        //i -> pg -t <text> -s <seed> -k <key> || -file <file_name>
        handler.validateValue( argv[2], 0);
        handler.validateValue( argv[4], 1);
        handler.validateValue( argv[6], 2);
        if ( argc > 7 && std::string(argv[7]).compare("-file") == 0 ) handler.validateValue( argv[8], 3);
        handler.takeAction( 3, true );

    } else if ((argc == 3 || argc == 5) && std::string(argv[1]).compare("-delete") == 0 ){
        //i-> pg -delete <key> || -file <file_name>
        handler.validateValue( argv[2], 2);
        if ( argc > 3 && std::string(argv[3]).compare("-file") == 0 ) handler.validateValue( argv[4], 3);
        handler.takeAction( 4, true );

    } else if ((argc == 2 || argc == 4) && std::string(argv[1]).compare("-delete") == 0 ){
        //i-> pg -delete || -file <file_name>
        if ( argc > 2 && std::string(argv[2]).compare("-file") == 0 ) {
            handler.validateValue( argv[3], 3);
            handler.takeAction( 5, false );
        } else handler.takeAction( 6, false );

    } else if ((argc == 2 || argc == 4) && std::string(argv[1]).compare("-list") == 0 ) {
        //i-> pg -list || -file <file_name>
        if ( argc > 2 && std::string(argv[2]).compare("-file") == 0 ) {
            handler.validateValue( argv[3], 3);
            handler.takeAction( 8, false );
        }else handler.takeAction( 7, false );

    } else if (argc == 2 && (std::string(argv[1]).compare("-h") == 0 || std::string(argv[1]).compare("-help") == 0)) {
        std::cout
        << "\n\033[1;36m   ---   PARAMS USE   ---\n\n"
        << "   <key>\n \u2192 \033[0mLooks for a key in the default file \033[1;90m~/.pg-jsons/default.json\033[0m, returns its encrypted value, and copies it to the clipboard.\033[1;36m\n\n"
        << "   <key> -file <file_name>\n \u2192 \033[0mLooks for a key in the specified file \033[1;90m~/.pg-jsons/file_name.json\033[0m, returns its encrypted value, and copies it to the clipboard.\033[1;36m\n\n"
        << "   -t <password> -s <seed> -k <key>\n \u2192 \033[0mAdds a new item in the default file \033[1;90m~/.pg-jsons/default.json\033[0m, returns its value, and copies it to the clipboard.\033[1;36m\n\n"
        << "   -t <password> -s <seed> -k <key> -file <file_name>\n \u2192 \033[0mAdds a new item in the specified file \033[1;90m~/.pg-jsons/file_name.json\033[0m, returns its value, and copies it to the clipboard.\033[1;36m\n\n"
        << "   -delete <key>\n \u2192 \033[0mLooks for a key in \033[1;90m~/.pg-jsons/default.json\033[0m and delete it.\033[1;36m\n\n"
        << "   -delete <key> -file <file_name>\n \u2192 \033[0mLooks for a key in \033[1;90m~/.pg-jsons/file_name.json\033[0m and delete it.\033[1;36m\n\n"
        << "   -delete\n \u2192 \033[0mDeletes \033[1;90m~/.pg-jsons/\033[0m folder and its content.\033[1;36m\n\n"
        << "   -delete -file <file_name>\n \u2192 \033[0mDeletes \033[1;90m~/.pg-jsons/file_name.json\033[1;36m\n\n"
        << "   -list\n \u2192 \033[0mReads all keys stored in \033[1;90m~/.pg-jsons/\033[1;36m\n\n"
        << "   -list -file <file_name>\n \u2192 \033[0mReads all keys stored in \033[1;90m~/.pg-jsons/file_name.json\033[1;36m\n\n"
        << "   <key> -u\n \u2192 \033[0mLooks for a key in \033[1;90m~/.pg-jsons/default.json\033[0m updates it (seed[0]+1,seed[1]+1...) return its encrypted value and copies it to the clipboard.\n\n\033[1;36m"
        << "   <key> -u -file <file_name>\n \u2192 \033[0mLooks for a key in \033[1;90m~/.pg-jsons/file_name.json\033[0m updates it (seed[0]+1,seed[1]+1...) return its encrypted value and copies it to the clipboard.\n\n\033[0m";
    } else {
        std::cout << "\n\033[1;31m \u2718 \033[0mparam combination not found, enter \033[1;90m-h\033[0m or \033[1;90m-help\033[0m for help.\n\n";
    }

    return 0;
}
// g++ -std=c++20 -o pg main.cpp handler.cpp file_actions.cpp encrypter.cpp clipboard.cpp item.cpp