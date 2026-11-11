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