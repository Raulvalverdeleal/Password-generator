#include <iostream>
#include "encrypter.hpp"
#include "item.hpp"

extern Item item;

std::ostream& operator<<(std::ostream& out, Encrypter &encrypter){
    out << "\033[32;1m \u2714 \033[90;1m" << encrypter.getPassword() << "\033[0m copied to your clipboard.\n\n";
    return out;
}

int Encrypter::gessIndex(int i, int s){
    int newIndex{ i + item.getSeedInt(s) };
    while (newIndex >= 36) newIndex -= 36;
    return newIndex;
}
void Encrypter::setPassword(){

    for (int i{0}; i < item.getText().length(); i++)
    {
        auto it = std::find(val_chars.begin(), val_chars.end(), item.getText()[i]);
        int index = std::distance(val_chars.begin(), it);

        m_password += chars_1[gessIndex(index, 0)];
        m_password += chars_2[gessIndex(index, 1)];
        m_password += chars_3[gessIndex(index, 2)];
    }
}

Encrypter encrypter;
