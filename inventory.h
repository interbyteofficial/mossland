#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <vector>
#include <iostream>

#define ITEM_ID_STONE 1
#define ITEM_ID_STICK 2
#define ITEM_ID_LEAVES 3
#define ITEM_ID_LEAF 4
#define ITEM_ID_FLINT 5
#define ITEM_ID_CLAY 6

struct Item
{
    int itemid;
    string itemname;
    int itemcount;

    Item();
    Item(int itemid,string itemname,int itemcount=1);
};

#endif // INVENTORY_H_INCLUDED
