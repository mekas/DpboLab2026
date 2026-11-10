#ifndef BILL_H
#define BILL_H

#include "menu_option.cpp"
#include "bill_part.cpp"
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

class Bill{
public:
    unordered_map<long, BillPart> bill_items;
    vector<MenuOption> order;
    long total_price;

    Bill(){
        this->total_price = 0;
    }

    //notice how to pass the reference
    Bill(vector<MenuOption>& order){
        this->order = order;
        this->total_price = 0;
    }

    static Bill computeBill(Bill &order);
    void computeBill();
    void printBill() const;
};

void Bill::printBill() const{
        cout << "====Billing Information===" << endl;
        for(const auto& [id, bill_item]: this->bill_items){
            cout << "Item " << id << ". " << bill_item.name << "    x   "
            << bill_item.quantity << "    "
            << bill_item.quantity * bill_item.price << endl;
        }
        cout << "Final Price: " << this->total_price << endl;
        cout << " THANK YOU" << endl;
    }

void Bill::computeBill(){
    long total_price = 0;
    for(auto item: this->order){
        try{
            //obtain the original bill_item reference so any modif copied back
            BillPart& bill_item = this->bill_items.at(item.id);
            //only update the quantity and part_price
            bill_item.quantity++;
        }
        catch(out_of_range &error){
            //if id not found, make new BillPart entry
            BillPart bill_item;
            bill_item.id = item.id;
            bill_item.name = item.name;
            bill_item.price = item.price;
            bill_item.quantity = 1;
            //then put it into Bill map
            bill_items.emplace(item.id, bill_item);
        }
    }

    //loop once more to recalculate final price, this is preferred due to safety
    for (const auto& [id, bill_item] : bill_items){
        total_price += bill_item.quantity * bill_item.price;
    }
    this->total_price = total_price;
}

Bill Bill::computeBill(Bill &order){
    long total_price = 0;
    for (const auto& [id, bill_item] : order.bill_items){
        total_price += bill_item.quantity * bill_item.price;
    }
    order.total_price = total_price;

    return order;
}

#endif