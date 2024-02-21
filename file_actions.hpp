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
        std::string m_file_name { "./pw-jsons/default.json" };
        Document m_doc {};
        bool m_name_setted { false };

    public:

        void getContent(const std::string& filename);
        void setContent();

        bool findItem();
        void getItem();
        void addItem();
        void deleteItem();
        void readContent(const std::string& filename);

        void setFileName( std::string new_file_name ){
            m_file_name = "./pw-jsons/" + new_file_name + ".json";
            m_name_setted = true;
        }
        const std::string& getFileName(){ return m_file_name; }
        const bool getNameSetted(){ return m_name_setted; }
};

#endif /* file_actions_hpp */
