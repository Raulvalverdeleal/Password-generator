//
//  handler.hpp
//  pw
//
//  Created by Raul Valverde leal on 20/2/24.
//

#ifndef handler_hpp
#define handler_hpp

#include <string>

class Handler
{

public:
    void validateValue(const std::string& value, int mode);
    void takeAction(int x);
};

#endif /* handler_hpp */
