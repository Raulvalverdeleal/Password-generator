#pragma once
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
        std::string m_file_name;
        std::string m_full_name;
        Document m_doc {};

    public:
        File_actions() : m_file_name{ "default.json" } {
            const char *homeDir = getenv("HOME");
            if (homeDir != nullptr)
                m_home = std::string(homeDir) + "/.pg-jsons";
            else
                m_home = "./.pg-jsons";
            m_full_name = m_home + '/' + m_file_name;
        }

        void getContent(const std::string& filename);
        void readContent(const std::string& filename);
        void setContent();

        bool findItem();
        void getItem(bool update);
        void addItem();
        void deleteItem();

        void setFileName( std::string new_file_name ){
            m_file_name = new_file_name + ".json";
            m_full_name = m_home + '/' + new_file_name;
        }
        const std::string& getFileName(){ return m_file_name; }
        const std::string& getHomeDir(){ return m_home; }
        const std::string& getFullName(){ return m_full_name; }
};

#endif
