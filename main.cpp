#include <iostream>
#include "menu_option.cpp"
#include "bill_part.cpp"
#include <vector>

using namespace std;
using std::endl;

void print_menu(vector<MenuOption>);
vector<MenuOption> offerMenu(vector<MenuOption>);

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

    MenuOption option2;
    option2.id = 2;
    option2.name = "Pizza";
    option2.price = 15'000l;

    MenuOption option3;
    option3.id = 3;
    option3.name = "Pasta";
    option3.price = 12'000l;

    vector<MenuOption> options;
    options.push_back(option1);
    options.push_back(option2);
    options.push_back(option3);

    vector<MenuOption> order = offerMenu(options);
    cout << order.size() << endl;
    Bill current_bill = Bill::computeBill(order);
    current_bill.printBill();

    return 0;
}

void print_menu(vector<MenuOption> offers){
    for(auto item: offers){
        cout << item.id << ". " << item.name << " : " << item.price << endl;
    }
    return;
}

vector<MenuOption> offerMenu(vector<MenuOption> offers){
    print_menu(offers);
    vector<MenuOption> order;
    string is_repeat = "y";
    while(is_repeat=="y" || is_repeat == "Y"){
        cout << "Pick menu id to order foods! : ";
        int id;
        cin >> id;
        MenuOption new_order = offers.at(id - 1);
        order.push_back(new_order);
        cout << "Do you wish order more?(y/n): ";
        cin >> is_repeat;
    }
    return order;
}
