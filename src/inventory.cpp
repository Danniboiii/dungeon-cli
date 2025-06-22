
#include "inventory.h"
#include "rooms.h"
#include <string>
#include <iostream>


namespace dungeon{


    // appends an item to the inventory, first_item is the head of the list
    item* item::add_item(item* inventory_head, const item& item_to_add){

        if(inventory_head == nullptr){ // if list empty

            item* new_item = new item(item_to_add); // calls the copy constructor
            inventory_head = new_item;
            return inventory_head; // the now has one item
        }

        item* new_item = new item(item_to_add);
        item* last_item = inventory_head; 
        while(last_item->next != nullptr){

            last_item = last_item->next; // go to the next node
        } // after this loop, last_item->next == nullptr
        last_item->next = new_item;
        new_item->next = nullptr;
        return inventory_head;
    }


    item* item::clear_inventory(item* inventory_head){

        while(inventory_head != nullptr){

            item* temp = inventory_head->next; // zeiger auf den nächsten knoten MERKEN!
            delete inventory_head; // aktuellen knoten löschen
            inventory_head = temp; // der kopf ist jetzt der zeiger auf den nächsten knoten
        }
        return nullptr;
    }

    item* item::get_Next() {return next;}

    void item::print_inventory(item* inventory_head){

        item* current_item = inventory_head;
        if(current_item == nullptr){

            std::cout << "No items in this inventory." << std::endl;
            return;
        }

        std::cout << "Items: ";
        while(current_item != nullptr){

            std::cout << current_item->name << "(" << current_item->quantity << ")";
            if(current_item->next != nullptr) std::cout << ", ";
            current_item = current_item->next;
        }
        std::cout << std::endl;
    }

    item* item::search_inventory(item* inventory_head, const std::string& search_name){

        item* current_item = inventory_head;
        if(current_item == nullptr){

            std::cout << "The inventory is empty" << std::endl;
            return nullptr;
        }

        while(current_item != nullptr){

            if(current_item->name == search_name){

                return current_item;
            }
            current_item = current_item->next;
        }
        std::cout << "<"<< search_name << "> is not in this inventory." << std::endl;
        return nullptr;
    }
    item* item::copy_inventory(item* &source_list_head, item* target_list_head){

        item* current_item = source_list_head;
        while(current_item != nullptr){

            target_list_head = add_item(target_list_head, *current_item); 
            // because add item expects a reference to an item object, the pointer to current_item needs to be derefferenced
            current_item = current_item->next;
        }
        return target_list_head;
    }
}