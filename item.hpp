#pragma once
#ifndef item_hpp
#define item_hpp

#include <string>
#include <array>

class Item
{
private:
    std::string m_text;
    std::array<int, 3> m_seed;
    std::string m_key;

public:
    Item() : m_text{""}, m_seed{0,0,0}, m_key{""} {}

    const std::string& getText(){ return m_text; }
    const std::array<int, 3>& getSeed(){ return m_seed; }
    const int getSeedInt(int i){ return m_seed[i]; }
    const std::string& getKey(){ return m_key; }

    void setText ( const std::string& text ){ m_text = text; }
    void setSeed ( const std::array<int, 3>& seed ){ m_seed = seed; }
    void setSeedInt ( const int i, int newValue ){ m_seed[i] = newValue; }
    void setKey ( const std::string& key ){ m_key = key; }

    friend std::ostream& operator<<(std::ostream &out, Item& item);
};

#endif
