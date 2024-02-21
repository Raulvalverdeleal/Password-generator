//
//  file_actions.cpp
//  pw
//
//  Created by Raul Valverde leal on 20/2/24.
//

#include "file_actions.hpp"
#include "item.hpp"

extern Item item;
File_actions file_actions;

void File_actions::getContent(){

    std::ifstream file(this->getFileName());
    if (!file.is_open()) {
        std::ofstream create_file(this->getFileName());
    }

    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (jsonData.empty())
        this->m_doc.SetObject();
    
    this->m_doc.Parse(jsonData.c_str());
    file.close();
}
void File_actions::setContent(){
    std::ofstream file((this->getFileName()));

    // TODO: manejar errores
    // if (!file.is_open()) {
    //     throw std::runtime_error("setContent.");
    // }
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    this->m_doc.Accept(writer);
    file << buffer.GetString();
    file.close();
}

bool File_actions::findItem(){
    this->getContent();
    auto search = this->m_doc.FindMember(item.getKey().c_str());
    if (search != this->m_doc.MemberEnd()){
        return true;
    } else return false;
}
void File_actions::getItem(){
    this->getContent();
    auto search = this->m_doc.FindMember(item.getKey().c_str());
    if (search != this->m_doc.MemberEnd()) {
        item.setText(search->value["text"].GetString());
        item.setSeed({
            search->value["seed"].GetArray()[0].GetInt(),
            search->value["seed"].GetArray()[1].GetInt(),
            search->value["seed"].GetArray()[2].GetInt()
        });
    }
    // state after this will be 2 if finded.
}

void File_actions::addItem(){
    this->getContent();

    Value new_member(kObjectType);
    new_member.AddMember("text",
        Value().SetString(item.getText().c_str(), item.getText().size(), this->m_doc.GetAllocator()),
        this->m_doc.GetAllocator()
    );
    Value seed_arr(kArrayType);
    for (int seed : item.getSeed()){
        seed_arr.PushBack(seed, this->m_doc.GetAllocator());
    }
    new_member.AddMember("seed", seed_arr, this->m_doc.GetAllocator());

    this->m_doc.AddMember(Value(item.getKey().c_str(), this->m_doc.GetAllocator()), new_member, this->m_doc.GetAllocator());
    this->setContent();
}
void File_actions::updateItem(){
    this->getContent();
}

void File_actions::deleteItem(){
    this->getContent();
    this->m_doc.RemoveMember(item.getKey().c_str());
    this->setContent();
}
void File_actions::deleteAll(){ std::filesystem::remove(this->m_file_name); }
