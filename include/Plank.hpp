#ifndef _PLANK_HPP_
#define _PLANK_HPP_

#include <iostream>
#include <string>
#include "NonTool.hpp"

using namespace std;

class Plank : public NonTool{    
    public:
        //CTOR, CCTOR, operator=, DTOR
        Plank();
        Plank(int id, int quantity);
        Plank(const Plank& plank);
        Plank& operator=(const Plank& plank);
        virtual ~Plank();

};

#endif