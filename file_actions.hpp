//
//  file_actions.hpp
//  pw
//
//  Created by Raul Valverde leal on 20/2/24.
//

#ifndef file_actions_hpp
#define file_actions_hpp

#include <fstream>
#include <string>
#include "./rapidjson/writer.h"
#include "./rapidjson/stringbuffer.h"
#include "./rapidjson/istreamwrapper.h"
#include "./rapidjson/document.h"

using namespace rapidjson;

class File_actions{
    private:
        std::string m_file_name { "" };
        Document m_doc {};

    public:

        void getContent();
        void setContent();

        bool findItem();
        void getItem();
        void addItem();
        void updateItem();
        void deleteItem();
        void deleteAll();

        void setFileName( std::string new_file_name ){
            m_file_name = "./jsons/" + new_file_name + ".json";
        }
        const std::string& getFileName(){
            return (m_file_name.empty() ? "./jsons/default.json" : m_file_name);
        }
};


#endif /* file_actions_hpp */
