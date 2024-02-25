#include "item.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream &out, Item& item) {
    out << "\033[0mText: \033[1;90m" << item.getText() << " \033[0mSeed: \033[1;90m" << item.getSeedInt(0) << '.' << item.getSeedInt(1) << '.' << item.getSeedInt(2) << " \033[0mKey: \033[1;90m" << item.m_key << "\033[0m";
    return out;
}

Item item;
