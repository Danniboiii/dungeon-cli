
#include "inventory.h"
#include "rooms.h"
#include <string>
#include <iostream>


namespace dungeon{

    item* item::initialize_inventory(){

        item* inventory_head = nullptr; // empty list
        return inventory_head;
    }

    // appends an item to the inventory, first_item is the head of the list
    item* item::add_item(item* inventory_head, const std::string& name){

        if(inventory_head == nullptr){ // if list empty

            item* new_item = new item(name);
            new_item->name = name;
            new_item->next = nullptr;
            inventory_head = new_item;
            return inventory_head;
        }

        item* new_item = new item(name);
        item* last_item = inventory_head;
        while(last_item->next != nullptr){

            last_item = last_item->next; // go to the next node
        } // after this loop, last_item->next == nullptr
        last_item->next = new_item;
        new_item->next = nullptr;
        return inventory_head;
    }


    item* item::clear_inventory(item* inventory_head){

        while(inventory_head->next != nullptr){

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

            std::cout << current_item->name;
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
}