#include "Item.hpp"
#include "NonTool.hpp"
#include "Tool.hpp"

int main()
{
    //Tool Testing
    // Tool t1(WOODEN_SWORD, "WOODEN_SWORD", "-", 10);
    // t1.show();
    // Tool* t2 = new Tool();
    // t2->show();
    // cout<<t2->getDurability()<<endl;
    // t2->setDurability(1);
    // t2->show();
    // delete t2;

    //NonTool Testing
    NonTool nt1(OAK_PLANK, "OAK_PLANK", "OAK", 3);
    NonTool* nt2 = new NonTool(IRON_INGOT, "IRON_INGOT", "-", 5);
    NonTool nt3(nt1);
    NonTool nt4;
    NonTool nt5;
    nt4 = *nt2;
    // nt1.show();
    // nt2->show();
    // nt3.show();
    // nt4.show();
    // nt5.show();
    nt1.setQuantity(5);
    cout<<nt1.getQuantity()<<endl;
    delete nt2;

    return 0;
}