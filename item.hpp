//
//  item.hpp
//  pw
//
//  Created by Raul Valverde leal on 20/2/24.
//

#ifndef item_hpp
#define item_hpp

//
//  item.h
//  get
//
//  Created by Raul Valverde leal on 19/2/24.
//

#include <string>
#include <array>

class Item
{
private:
    std::string m_text;
    std::array<int, 3> m_seed;
    std::string m_key;
    int m_state{0};

public:
    Item() : m_text{""}, m_seed{0,0,0}, m_key{""} {}

    const std::string& getText(){ return m_text; }
    const std::array<int, 3>& getSeed(){ return m_seed; }
    const std::string& getKey(){ return m_key; }
    const int getState(){ return m_state; }

    void setText ( std::string text ){ m_text = text; updateState();}
    void setSeed ( std::array<int, 3> seed ){ m_seed = seed;}
    void setKey ( std::string key ){ m_key = key; updateState();}

    void updateState();


    friend std::ostream& operator<<(std::ostream &out, Item& item);
};


#endif /* item_hpp */
