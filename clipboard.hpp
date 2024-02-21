#pragma once
#ifndef CLIPBOARD
#define CLIPBOARD

#include <string>

class Clipboard{
public:
    std::string exec(const char* cmd);
    std::string paste();
    std::string copy(const char* new_clipboard);
};

#endif