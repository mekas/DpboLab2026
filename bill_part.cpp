#ifndef BILL_PART_H
#define BILL_PART_H

#include "menu_option.cpp"

using namespace std;

class BillPart : public MenuOption {
public:
    long quantity;
    BillPart(){
        quantity = 0;
    }

    BillPart(long id, string name, long price) : MenuOption(id, name, price){
        quantity = 0;
    }

    BillPart(long id, string name, long price, long quantity) :
        MenuOption(id, name, price), quantity(quantity){
    }
};

#endif