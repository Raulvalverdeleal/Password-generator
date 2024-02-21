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
        std::cout << "\n\033[1;31m" << value << "\033[0m does not match: \033[1;32m" <<
        (
        mode == 0 ? "[a-z\\d]{8,20}" :
        mode == 1 ? "(\\d{2}\\.){2}\\d{2}" :
        mode == 2 ? "[a-z]{1,3}" :
        "[a-zA-Z\\d-_]{0,20}"
        )
        << "\n\033[0mInsert the value correctly: ";

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

void Handler::takeAction(int x){

    if(!std::filesystem::exists(std::string("./pw-jsons").c_str()))
        std::filesystem::create_directory(std::string("./pw-jsons").c_str());

    bool itemFinded { file_actions.findItem() };

    switch (x) {
    case 1:
        // get key
        if (item.getState() != 1) break;
        if (itemFinded) {
            file_actions.getItem();
            encrypter.setPassword();
            clipboard.copy(encrypter.getPassword().c_str());
            
            std::cout << '\n' << item << '\n' << encrypter;

        } else std::cout << "\n\033[1;31mError: \033[0m" << item.getKey() << " \033[1;90mnot found.\n\n";
        break;
    
    case 2:
        // add password
        if (item.getState() != 2) break;
        if (itemFinded){
            std::cout << "\n\033[1;31mError: \033[0m" << item.getKey() << " \033[1;90malready exists.\n" <<
            "\033[0mInsert a \033[1;90mnew key\033[0m or enter \033[1;90m-force \033[0mto overwrite: \033[0m";
            std::string response;
            std::getline(std::cin >> std::ws, response);
            if (response.compare("-force") == 0){
                file_actions.deleteItem();
                goto insert_item;
            } else {
                this->validateValue( response, 2 );
                this->takeAction( 2 );
            }
        } else goto insert_item;
            
        insert_item:
            file_actions.addItem();
            encrypter.setPassword();
            clipboard.copy(encrypter.getPassword().c_str());

            std::cout << "\n\033[1;32mSuccess: "
            << item << " \033[0minserted into: \033[1;90m" << file_actions.getFileName()
            << "\n\033[0m" << encrypter;

        break;
    
    case 3:
        // delete key
        if (item.getState() != 1) break;
        if (itemFinded) {
            file_actions.deleteItem();
            std::cout << "\n\033[1;32mSuccess: \033[0m" << item << " \033[0mdeleted from: \033[1;90m" << file_actions.getFileName() << "\n\n";
        } else std::cout << "\n\033[1;31mError: \033[0m" << item.getKey() << " \033[1;90mnot found.\n";
        break;

    case 4:
        //if file not setted: deletes folder | if file setted: deletes file in folder
        if (!file_actions.getNameSetted()) {
            std::filesystem::remove_all(std::string("./pw-jsons"));
            std::cout << "\n\033[1;32mSuccess: \033[1;90m./pw-jsons deleted\033[0m\n\n";      
        } else if (std::filesystem::exists(file_actions.getFileName())){
            std::filesystem::remove(std::string(file_actions.getFileName()));
            std::cout << "\n\033[1;32mSuccess:\033[1;90m " << file_actions.getFileName() << " deleted\033[0m\n\n";
        } else std::cout << "\n\033[1;31mError:\033[1;90m " << file_actions.getFileName() << " mnot found.\033[0m\n\n";
        break;
    
    case 5:
        if (file_actions.getNameSetted()){
            std::cout << "\n\033[1;90mFile: " << file_actions.getFileName() << '\n';
            file_actions.readContent(file_actions.getFileName());
        }else {
            for (auto const& dir_entry : std::filesystem::directory_iterator(std::string("./pw-jsons"))){
                std::cout << "\n\033[1;90mFile: " << dir_entry.path() << '\n';
                file_actions.readContent(dir_entry.path());
            }
        }
        std::cout << "\n\033[0m";
    break;

    default:
        break;
    }
}
