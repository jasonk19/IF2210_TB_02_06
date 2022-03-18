#include "Class.hpp"

int main()
{
    //Tool Testing
    Tool t1(WOODEN_SWORD, "WOODEN_SWORD", "-", 10);
    t1.show();
    Tool* t2 = new Tool();
    t2->show();
    cout<<t2->getDurability()<<endl;
    t2->setDurability(1);
    t2->show();
    delete t2;

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

    //Log testing
    // Log l1;
    // Log* l2 = new Log(BIRCH_LOG, "BIRCH_PLANK", 8);
    // Log l4(OAK_LOG, "OAK_LOG",4);
    // l1.show();cout<<endl;
    // l2->show();
    // l1 = *l2;
    // l1.show();
    // Log L3 = Log(*l2);
    // l2->show();
    // l4.show();
    // L3.show();
    // delete l2;

    //Axe Testing
    // Axe a1;
    // a1.show();

    // Axe a2(DIAMOND_AXE, 5);
    // Axe a4(WOODEN_AXE, 3);
    // Axe a6(IRON_AXE, 8);
    // a4.show();
    // a2.show();

    // a1 = a2;
    // a1.show();
    // Axe a7(a6);
    // a7.show();

    //Sword testing
    // Sword s1;
    // Sword s2(IRON_SWORD, 3);
    // Sword s3(DIAMOND_SWORD, 5);
    // Sword s4(s3);
    // s1 = s2;

    // s1.show();
    // s2.show();
    // s3.show();
    // s4.show();

    //Pickaxe testing
    // Pickaxe p1;
    // Pickaxe p2;
    // Pickaxe p3(DIAMOND_PICKAXE, 8);
    // Pickaxe p4(IRON_PICKAXE, 3);
    // Pickaxe p5(p3);
    // p2 = p4;

    // p1.show();
    // p2.show();
    // p3.show();
    // p4.show();
    // p5.show();






    return 0;
}