#ifndef _SWORD_HPP_
#define _SWORD_HPP_

#include "Tool.hpp"

class Sword : public Tool{
    private:
        string material;
    public:
        //CTOR, CCTOR, operator=, DTOR
        Sword();
        Sword(int id, int durability);
        Sword(const Sword& sword);
        Sword& operator=(const Sword& sword);
        virtual ~Sword();

        virtual void show();


};


#endif