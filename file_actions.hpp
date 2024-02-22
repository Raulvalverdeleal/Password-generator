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
#include <cstdlib>
#include "./rapidjson/writer.h"
#include "./rapidjson/stringbuffer.h"
#include "./rapidjson/istreamwrapper.h"
#include "./rapidjson/document.h"

using namespace rapidjson;

class File_actions{
    private:
        std::string m_home;
        std::string m_file_name { m_home + "/default.json" };
        std::string m_full_name;
        Document m_doc {};
        bool m_name_setted { false };

    public:
        File_actions() {
            const char *homeDir = getenv("HOME");
            if (homeDir != nullptr)
                m_home = std::string(homeDir) + "/pw-jsons";
            else
                m_home = "./pw-jsons";
            m_full_name = m_home + m_file_name;
        }

        void getContent(const std::string& filename);
        void setContent();

        bool findItem();
        void getItem();
        void addItem();
        void deleteItem();
        void readContent(const std::string& filename);

        void setFileName( std::string new_file_name ){
            m_file_name =  m_home + new_file_name + ".json";
            m_name_setted = true;
        }
        const std::string& getFileName(){ return m_file_name; }
        const std::string& getHomeDir(){ return m_home; }
        const std::string& getFullName(){ return m_full_name; }
        const bool getNameSetted(){ return m_name_setted; }
};

#endif /* file_actions_hpp */
