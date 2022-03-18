#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <iostream>
#include <string>
#include "NonTool.hpp"

using namespace std;

class Log : public NonTool{    
    public:
        //CTOR, CCTOR, operator=, DTOR
        Log();
        Log(int id, int quantity);
        Log(const Log& log);
        Log& operator=(const Log& log);
        virtual ~Log();

};

#endif