//
//  encrypter.h
//  get
//
//  Created by Raul Valverde leal on 19/2/24.
//

#ifndef encrypter_h
#define encrypter_h

#include <array>
#include <string>

constexpr std::array<char, 36> val_chars{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};
constexpr std::array<char, 36> chars_1{'@', '!', 'i', 'a', 'v', '?', '(', 'f', ',', 'P', 'n', '8', 'E', 'W', '0', 'c', 'g', 'D', 'Q', 'q', '$', 'A', 'x', 'U', ':', 'K', 'p', 'r', '6'};
constexpr std::array<char, 36> chars_2{'5', '?', '7', '1', 'L', 'D', '%', ':', 'M', 'X', 'A', 'y', 'V', 'i', '(', '/', 'Z', ',', 'G', 'r', '@', 'F', 'O', '8', 'W', 'B', 'E', '*', 'U'};
constexpr std::array<char, 36> chars_3{'H', ',', 'h', 'O', 'B', 'b', 'f', '+', 'R', 'i', ')', 'C', 'T', '?', 'c', '0', 'Q', '@', 'm', 'e', '9', 'F', 'Z', 'E', '7', 'M', 'l', 'o', 'L'};

class Encrypter
{
    std::string m_password{""};
public:
    std::string getPassword(){ return m_password; };
    void setPassword();
    int gessIndex(int i, int s);

    friend std::ostream& operator<<(std::ostream& out, Encrypter &encrypter);
};

#endif /* encrypter_h */
