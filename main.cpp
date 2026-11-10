#include <iostream>
#include "menu_option.cpp"
#include "bill_part.cpp"
#include "bill.cpp"
#include <stdexcept>
#include <unordered_map>

using namespace std;
using std::endl;

void print_menu(unordered_map<long, InventoryMenu>);
Bill offerMenu(unordered_map<long, InventoryMenu>);

int main() {
    //cout << "Hello, World!" << endl;
    /**
    Simulation:
    1. Start by preparing list of menu to offers
    */

    MenuOption option1;
    option1.id = 1;
    option1.name = "Burger";
    option1.price = 10'000l;
    InventoryMenu im1(option1, 2);

    MenuOption option2;
    option2.id = 2;
    option2.name = "Pizza";
    option2.price = 15'000l;
    InventoryMenu im2(option2, 2);

    MenuOption option3;
    option3.id = 3;
    option3.name = "Pasta";
    option3.price = 12'000l;
    InventoryMenu im3(option3, 2);

    unordered_map<long, InventoryMenu> options;
    options.emplace(im1.id, im1);
    options.emplace(im2.id, im2);
    options.emplace(im3.id, im3);

    Bill order = offerMenu(options);
    cout << order.bill_items.size() << endl;
    Bill current_bill = Bill::computeBill(order);
    current_bill.printBill();

    return 0;
}

void print_menu(unordered_map<long, InventoryMenu> offers){
    for(const auto& [ids, item]: offers){
        cout << item.id << ". " << item.name << " : " << item.price << endl;
    }
    return;
}


/**
* Notice offers is copy by value so the passed data is cloned
* This is important since we'll going to be reduced the stock count as
* order processed
*/
Bill offerMenu(unordered_map<long, InventoryMenu> offers){
    print_menu(offers);
    Bill order;

    string is_repeat = "y";
    while(is_repeat=="y" || is_repeat == "Y"){
        cout << "Pick menu id to order foods! : ";
        int id;
        cin >> id;
        try{
            InventoryMenu &new_order = offers.at(id );
            //check quantity
            if(new_order.quantity > 0){
                new_order.quantity--; //decrement stock
                auto item = order.bill_items.try_emplace(
                    new_order.id, new_order.id, new_order.name, new_order.price).first;
                ++item->second.quantity;
            } else{
                //will be switch to throw later
                cout << "Sorry this offer item is exhausted, please pick different one" << endl;
            }
            cout << "Do you wish order more?(y/n): ";
            cin >> is_repeat;
        }
        catch(out_of_range &error){
            //id not found
            cout << "Please enter correct item ID!" << endl;
        }
    }
    return order;
}
