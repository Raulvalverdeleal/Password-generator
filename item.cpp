//
//  item.cpp
//  pw
//
//  Created by Raul Valverde leal on 20/2/24.
//

#include "item.hpp"
#include <iostream>

void Item::updateState(){
    if (!m_text.empty() && !m_key.empty())
        m_state = 2;
    else if (!m_key.empty())
        m_state = 1;
    else
        m_state = 0;
}

std::ostream& operator<<(std::ostream &out, Item& item) {

    if (item.getState() == 1)
        out << "\033[1;90mkey: \033[0m" << item.getKey();
    else if (item.getState() == 2)
        out << "\033[0mText: \033[1;90m" << item.getText() << " \033[0mSeed: \033[1;90m" << item.getSeed()[0] << '.' << item.getSeed()[1] << '.' << item.getSeed()[2] << " \033[0mKey: \033[1;90m" << item.m_key << "\033[0m";
    else
        out << "\033[1;31mAny item have been defined.\033[0m";
    return out;
}

Item item;
