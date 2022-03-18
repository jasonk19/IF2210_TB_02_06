#ifndef _STONE_HPP_
#define _STONE_HPP_

#include <iostream>
#include <string>
#include "NonTool.hpp"

using namespace std;

class Stone : public NonTool{    
    public:
        //CTOR, CCTOR, operator=, DTOR
        Stone();
        Stone(int id, int quantity);
        Stone(const Stone& stone);
        Stone& operator=(const Stone& stone);
        virtual ~Stone();

};

#endif