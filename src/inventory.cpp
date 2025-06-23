
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

    // removes n items from the inventory and deletes the item node if quantity == 0
    item* item::remove_item(item* inventory_head, const std::string& item_to_remove, int amount){

        // if the list is empty, return nullptr
        if(inventory_head == nullptr) return nullptr;

        //if the first item is the one to be removed... the head is now the "second" item, could be nullptr
        if(inventory_head->name == item_to_remove){

            inventory_head->quantity -= amount;
            if(inventory_head->quantity <= 0){

                item* new_inventory_head = inventory_head->next;
                delete inventory_head;
                return new_inventory_head;
            }
        }

        item* previous_item = inventory_head;
        item* current_item = inventory_head->next;

        // current item is now the second item, because the first item was handled in the case above
        while(current_item != nullptr){

            if(current_item->name == item_to_remove) {

                current_item->quantity -= amount;
                if(current_item->quantity <= 0){
                    //delete the node "in between" the previous and next item (so the current item)
                    previous_item->next = current_item->next;
                    delete current_item;
                    break;
                }
            }
            previous_item = current_item;
            current_item = current_item->next;
        }
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

    std::string item::get_name() {return name;}
    int item::get_quantity() {return quantity;}
    item* item::get_next() {return next;}

    item* item::get_item_by_index(item* inventory_head, int index){

        if(inventory_head == nullptr){

            std::cout << "This inventory is empty, or you picked a wrong index" <<std::endl;
            return nullptr;
        }

        item* current_item = inventory_head;
        int counter = 1;

        while(current_item != nullptr){

            if(counter == index) return current_item;
            current_item = current_item->next;
            counter++;
        }
        std::cout << "Invalid Index" << std::endl;
        return nullptr;
    }


    void item::print_inventory(item* inventory_head){

        item* current_item = inventory_head;
        if(current_item == nullptr){

            std::cout << "No items in this inventory." << std::endl;
            return;
        }

        int index = 1;
        while(current_item != nullptr){

            std::cout << "[" << index << "]: " << current_item->name << "(" << current_item->quantity << ")";
            if(current_item->next != nullptr) std::cout << ", ";
            current_item = current_item->next;
            index++;
            std::cout << std::endl;
        }
    }

    item* item::search_inventory(item* inventory_head, const std::string &search_name){

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

        if (source_list_head == target_list_head && source_list_head != nullptr) {
            std::cerr << "Error: Attempt to copy inventory into itself!" << std::endl;
            return target_list_head;
        }
        item* current_item = source_list_head;
        while(current_item != nullptr){

            target_list_head = add_item(target_list_head, *current_item); 
            // because add item expects a reference to an item object, the pointer to current_item needs to be derefferenced
            current_item = current_item->next;
        }
        return target_list_head;
    }
}