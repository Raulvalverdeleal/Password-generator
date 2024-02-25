#pragma once
#ifndef handler_hpp
#define handler_hpp

#include <string>

class Handler
{

public:
    void validateValue(const std::string& value, int mode);
    void takeAction(int x, bool search);
};

#endif
