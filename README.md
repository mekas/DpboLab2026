# Instruction
There are two tags
1. base_case which implement Base case scenario which was defined in case 1
2. limited_stock which implement base_case with improvement on Quantity menu as constraint

## Class diagram

```mermaid
classDiagram
    class MenuOption {
        +unsigned long id
        +string name
        +long price
        +MenuOption()
        +MenuOption(long id, string name, long price)
    }

    class InventoryMenu {
        +long quantity
        +InventoryMenu()
        +InventoryMenu(MenuOption menu)
        +InventoryMenu(unsigned long id, string name, long price, long quantity)
        +InventoryMenu(MenuOption menu, long quantity)
    }

    class BillPart {
        +long quantity
        +BillPart()
        +BillPart(long id, string name, long price)
        +BillPart(long id, string name, long price, long quantity)
    }

    class Bill {
        +unordered_map~long, BillPart~ bill_items
        +vector~MenuOption~ order
        +long total_price
        +Bill()
        +Bill(vector~MenuOption~ order)
        +computeBill(Bill order) Bill
        +computeBill() void
        +printBill() void
    }

    MenuOption <|-- InventoryMenu
    MenuOption <|-- BillPart
    Bill *-- "0..*" BillPart : bill_items
    Bill *-- "0..*" MenuOption : order
```

## Sequence diagram

```mermaid
sequenceDiagram
    actor User
    participant Main as main()
    participant Offer as offerMenu()
    participant Display as print_menu()
    participant Offers as offers inventory
    participant Order as order Bill
    participant Compute as Bill::computeBill()
    participant Print as current_bill.printBill()

    Main->>Offer: offerMenu(options), passing a copy
    activate Offer
    Offer->>Display: print_menu(offers)
    Display-->>User: Display menu items
    Offer-->>User: Prompt for menu ID

    loop While user answers y/Y
        User->>Offer: Enter menu ID
        Offer->>Offers: Look up ID
        alt ID exists and quantity > 0
            Offers-->>Offer: Return inventory item
            Offer->>Offers: Decrement stock
            Offer->>Order: Add item or increment its quantity
            Offer-->>User: Ask whether to order more
            User->>Offer: Enter y/Y or n
        else ID exists but stock is exhausted
            Offers-->>Offer: Return inventory item
            Offer-->>User: Show exhausted-item message
            Offer-->>User: Ask whether to order more
            User->>Offer: Enter y/Y or n
        else ID does not exist
            Offers-->>Offer: Throw out_of_range
            Offer-->>User: Show invalid-ID message
        end
    end

    Offer-->>Main: Return order
    deactivate Offer
    Main->>Compute: computeBill(order)
    Compute-->>Main: Return order with total_price
    Main->>Print: printBill()
    Print-->>User: Display items and final price
```