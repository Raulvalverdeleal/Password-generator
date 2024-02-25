#include <regex>
#include <filesystem>
#include <iostream>

#include "handler.hpp"
#include "item.hpp"
#include "file_actions.hpp"
#include "encrypter.hpp"
#include "clipboard.hpp"

extern Item item;
extern File_actions file_actions;
extern Encrypter encrypter;
extern Clipboard clipboard;

Handler handler;

void Handler::validateValue(const std::string& value, int mode){

    std::array<std::regex, 4> regexes = {
        std::regex("[a-z\\d]{8,}"),
        std::regex("(\\d{2}\\.){2}\\d{2}"),
        std::regex("[a-zñ]{1,3}"),
        std::regex("[a-zA-Z\\d_-]{0,20}")
    };

    if (!std::regex_match(value, regexes[mode]))
    {
        std::string newValue;
        std::cout << "\n\033[1;31m \u2718 \033[1;90m" << value << "\033[0m does not match: \033[1;36m" <<
        (
        mode == 0 ? "[a-z\\d]{8,20}" :
        mode == 1 ? "(\\d{2}\\.){2}\\d{2}" :
        mode == 2 ? "[a-z]{1,3}" :
        "[a-zA-Z\\d-_]{0,20}"
        )
        << "\n \u2192 \033[0mInsert the value correctly: ";

        std::getline(std::cin >> std::ws, newValue);
        this->validateValue(newValue, mode);
        return;
    }

    switch (mode)
    {
    case 0:
        item.setText( value );
        break;
    case 1:
        item.setSeed({
            std::stoi( value.substr(0,2) ),
            std::stoi( value.substr(3,2) ),
            std::stoi( value.substr(6,2) )
        });
        break;
    case 2:
        item.setKey( value );
        break;
    case 3:
        file_actions.setFileName( value );
    default:
        break;
    }
}

void Handler::takeAction(int x, bool search){

    if(!std::filesystem::exists(file_actions.getHomeDir()))
        std::filesystem::create_directory(file_actions.getHomeDir());

    bool itemFinded { false };
    if(search) itemFinded = file_actions.findItem();

    switch (x) {
    case 1:
    case 2:
        // search for a key, (updates or not its seed) and return its encripted value.
        if (itemFinded) {
            file_actions.getItem(x==1?false:true);
            encrypter.setPassword();
            clipboard.copy(encrypter.getPassword().c_str());
            std::cout << '\n' << encrypter;

        } else std::cout << "\n\033[1;31m \u2718 \033[0m" << item.getKey() << " not found.\n\n";
        break;
    
    case 3:
        // adds item.
        if (itemFinded){
            std::cout << "\n\033[1;31m \u2718 \033[1;90m" << item.getKey() << " \033[0malready exists.\n" << 
            "\033[1;36m \u2192 \033[0mInsert a \033[1;90mnew key\033[0m or enter \033[1;90m-force \033[0mto overwrite: \033[0m";
            std::string newKey;
            std::getline(std::cin >> std::ws, newKey);
            if (newKey.compare("-force") == 0){
                file_actions.deleteItem();
                goto insert_item;
            } else {
                this->validateValue( newKey, 2 );
                this->takeAction( 3, true );
                break;
            }
        } else goto insert_item;

        insert_item:
            file_actions.addItem();
            encrypter.setPassword();
            clipboard.copy(encrypter.getPassword().c_str());

            std::cout << "\n\033[1;32m \u2714 "
            << item << " \033[0minserted into: \033[1;90m" << file_actions.getFileName()
            << "\n\033[0m" << encrypter;
        break;
    
    case 4:
        // deletes item.
        if (itemFinded) {
            file_actions.deleteItem();
            std::cout << "\n\033[1;32m \u2714 \033[0mKey: \033[1;90m" << item.getKey() << " \033[0mdeleted from: \033[1;90m" << file_actions.getFullName() << "\n\n";
        } else std::cout << "\n\033[1;31m \u2718 \033[1;90m" << item.getKey() << " \033[0mnot found.\n";
        break;

    case 5:
        // deletes specific file.
        if (std::filesystem::exists(file_actions.getFullName())){
            std::filesystem::remove(file_actions.getFullName());
            std::cout << "\n\033[1;32m \u2714 \033[1;90m " << file_actions.getFileName() << " \033[0mdeleted\n\n";
        } else std::cout << "\n\033[1;31m \u2718 \033[1;90m " << file_actions.getFileName() << " \033[0mnot found.\n\n";
        break;
    
    case 6:
        // deletes folder.
        std::filesystem::remove_all(file_actions.getHomeDir());
        std::cout << "\n\033[1;32m \u2714 \033[1;90m" << file_actions.getHomeDir() << " \033[0mdeleted\n\n";   
        break;
    
    case 7:
        // reads content from folder.
        for (auto const& dir_entry : std::filesystem::directory_iterator(std::string(file_actions.getHomeDir()))){
            std::cout << "\n\033[1;36m \u25c9 \033[1;90m" << dir_entry.path() << '\n';
            file_actions.readContent(dir_entry.path());
        }
        std::cout << '\n';
        break;
    case 8:
        // reads content from a specific file.
        if (std::filesystem::exists(file_actions.getFullName())){
            std::cout << "\n\033[1;36m \u25c9 \033[1;90m" << file_actions.getFullName() << '\n';
            file_actions.readContent(file_actions.getFullName());
        } else std::cout << "\n\033[1;31m \u2718 \033[1;90m " << file_actions.getFileName() << " \033[0mnot found.\n";
        std::cout << '\n';
        break;

    default:
        break;
    }
    //reset terminal style
    std::cout << "\033[0m";
}
