#ifndef BILL_PART_H
#define BILL_PART_H

#include "menu_option.cpp"
#include <unordered_map>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

using namespace std;

class BillPart : public MenuOption {
public:
    long quantity;
    long part_price; //accummulated price based on quantity
};

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

    static Bill computeBill(const vector<MenuOption>& order);
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
            bill_item.part_price += bill_item.price;
        }
        catch(out_of_range &error){
            //if id not found, make new BillPart entry
            BillPart bill_item;
            bill_item.id = item.id;
            bill_item.name = item.name;
            bill_item.price = item.price;
            bill_item.quantity = 1;
            bill_item.part_price = item.price;
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

Bill Bill::computeBill(const vector<MenuOption>& order){
    long total_price = 0;
    unordered_map<long, BillPart> bill_items;
    for(auto item: order){
        try{
            //obtain the original bill_item reference so any modif copied back
            BillPart& bill_item = bill_items.at(item.id);
            //only update the quantity and part_price
            bill_item.quantity++;
            bill_item.part_price += bill_item.price;
        }
        catch(out_of_range &error){
            //if id not found, make new BillPart entry
            BillPart bill_item;
            bill_item.id = item.id;
            bill_item.name = item.name;
            bill_item.price = item.price;
            bill_item.quantity = 1;
            bill_item.part_price = item.price;
            //then put it into Bill map
            bill_items.emplace(item.id, bill_item);
        }
    }

    //loop once more to recalculate final price, this is preferred due to safety
    for (const auto& [id, bill_item] : bill_items){
        total_price += bill_item.quantity * bill_item.price;
    }
    Bill bill;
    bill.bill_items = bill_items;
    bill.total_price = total_price;

    return bill;
}

#endif