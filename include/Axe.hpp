#ifndef _AXE_HPP_
#define _AXE_HPP_

#include "Tool.hpp"

class Axe : public Tool{
    private:
        string material;
    public:
        //CTOR, CCTOR, operator=, DTOR
        Axe();
        Axe(int id, int durability);
        Axe(const Axe& axe);
        Axe& operator=(const Axe& axe);
        virtual ~Axe();

        virtual void show();


};


#endif