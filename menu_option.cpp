#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <string>

class MenuOption {
public:
    unsigned long id;
    std::string name;
    long price;
};

class InventoryMenu : public MenuOption {
public:
    long quantity;
};

#endif