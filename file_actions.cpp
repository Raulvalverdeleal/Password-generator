#include "file_actions.hpp"
#include "item.hpp"
#include <iostream>

extern Item item;
File_actions file_actions;

void File_actions::getContent(const std::string& filename){

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream create_file(filename);
    }

    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (jsonData.empty())
        m_doc.SetObject();
    
    m_doc.Parse(jsonData.c_str());
    file.close();
}
void File_actions::setContent(){
    std::ofstream file(m_full_name);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    m_doc.Accept(writer);
    file << buffer.GetString();
    file.close();
}
void File_actions::readContent(const std::string& filename){
    getContent(filename);
    for (Value::ConstMemberIterator itr = m_doc.MemberBegin(); itr != m_doc.MemberEnd(); ++itr){
        std::cout << "\t\033[1;32m\u2192  " << itr->name.GetString() << "\t\033[0m" << itr->value["text"].GetString() << '\n';
    }
}


bool File_actions::findItem(){
    getContent(m_full_name);
    auto search = m_doc.FindMember(item.getKey().c_str());
    if (search != m_doc.MemberEnd()){
        return true;
    } else return false;
}
void File_actions::getItem(bool update){
    getContent(m_full_name);
    auto search = m_doc.FindMember(item.getKey().c_str());
    if (search != m_doc.MemberEnd()) {
        item.setText(search->value["text"].GetString());
        item.setSeed({
            search->value["seed"].GetArray()[0].GetInt(),
            search->value["seed"].GetArray()[1].GetInt(),
            search->value["seed"].GetArray()[2].GetInt()
        });
    }
    if (update && search != m_doc.MemberEnd()) {
        rapidjson::Value& seedArray = search->value["seed"];
        std::cout << "\n\033[1;32m \u2714 \033[0mUpdated from: \033[1;90m" << item.getSeedInt(0) << '.' << item.getSeedInt(1) << '.' << item.getSeedInt(2) << "\033[0m To: " ;
        for (int i = 0; i < 3; i++) {
            int newValue = item.getSeedInt(i) + 1 > 99 ? 0 : item.getSeedInt(i) + 1;
            seedArray[i].SetInt(newValue);
            item.setSeedInt(i, newValue);
        }
        std::cout << "\033[1;90m" << item.getSeedInt(0) << '.' << item.getSeedInt(1) << '.' << item.getSeedInt(2) << "\033[0m In: \033[1;90m" << file_actions.getFileName() << "\033[0m" ;
        setContent();
    }
}
void File_actions::addItem(){
    getContent(m_full_name);

    Value new_member(kObjectType);
    new_member.AddMember("text",
        Value().SetString(item.getText().c_str(), item.getText().size(), m_doc.GetAllocator()),
        m_doc.GetAllocator()
    );
    Value seed_arr(kArrayType);
    for (int seed : item.getSeed()){
        seed_arr.PushBack(seed, m_doc.GetAllocator());
    }
    new_member.AddMember("seed", seed_arr, m_doc.GetAllocator());

    m_doc.AddMember(Value(item.getKey().c_str(), m_doc.GetAllocator()), new_member, m_doc.GetAllocator());
    setContent();
}
void File_actions::deleteItem(){
    getContent(m_full_name);
    m_doc.RemoveMember(item.getKey().c_str());
    setContent();
}