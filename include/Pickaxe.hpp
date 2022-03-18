#ifndef _PICKAXE_HPP_
#define _PICKAXE_HPP_

#include "Tool.hpp"

class Pickaxe : public Tool{
    private:
        string material;
    public:
        //CTOR, CCTOR, operator=, DTOR
        Pickaxe();
        Pickaxe(int id, int durability);
        Pickaxe(const Pickaxe& p);
        Pickaxe& operator=(const Pickaxe& p);
        virtual ~Pickaxe();

        virtual void show();


};


#endif