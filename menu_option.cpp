#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <string>
using namespace std;

class MenuOption {
public:
    unsigned long id;
    string name;
    long price;

    MenuOption(){}
    MenuOption(long id2, string name2, long price2) : id(id2), name(name2), price(price2){}
};

class InventoryMenu : public MenuOption {
public:
    long quantity;

    InventoryMenu(){}
    InventoryMenu(MenuOption m){
        id = m.id;
        name = m.name;
        price = m.price;
    }
    InventoryMenu(unsigned long id, string name, long price,long quantity2) :
    MenuOption(id, name, price), quantity(quantity2){}
    InventoryMenu(MenuOption m, long quantity){
        id = m.id;
        name = m.name;
        price = m.price;
        this->quantity = quantity;
    }
};

#endif