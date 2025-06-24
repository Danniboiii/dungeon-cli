
#include "inventory.h"
#include "rooms.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>



namespace dungeon{

    item& item::operator=(const item &item_to_copy){

        if(this == &item_to_copy) return *this;
        this->name = item_to_copy.name;
        this->quantity = item_to_copy.quantity;
        this->next = nullptr;
        return *this;
    }

    item::item(item&& other) noexcept : name(std::move(other.name)), quantity(other.quantity), next(other.next){

    other.name.clear();
    other.quantity = 0;
    other.next = nullptr;
    }

    item& item::operator=(item&& other) noexcept{

        if(this != &other){ // 1. Check for self-assignment

            delete next; // 2. Clean up current resources (avoid memory leak)
            name = std::move(other.name); // 3. Move the name string from (other) to (this)
            quantity = other.quantity; // 4. Copy the quantity
            next = other.next; // 5. Steal the next pointer (linked list)
            other.next = nullptr; // 6. Leave other in a valid, empty state
            other.quantity = 0;
            other.name.clear();
        }
        return *this; // 7. Return *this for chaining
    }

    // appends an item to the inventory, first_item is the head of the list
    item* item::add_item(item* inventory_head, const item& item_to_add){

        if(inventory_head == nullptr){ // if list empty

            item* new_item = new item(item_to_add); // calls the copy constructor
            inventory_head = new_item;
            return inventory_head; // the inventory now has one item
        }

        item* current_item = inventory_head;
        item* previous_item = nullptr;

        while(current_item != nullptr){

            if(current_item->get_name() == item_to_add.get_name()){

                // if the item already is in the inventory, increase quantity
                current_item->quantity += item_to_add.get_quantity();
                return inventory_head;
            }
            previous_item = current_item;
            current_item = current_item->get_next();
        }
        previous_item->next = new item(item_to_add);
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

        delete inventory_head;
        return nullptr;
    }

    std::string item::get_name() const {return name;}
    int item::get_quantity() const {return quantity;}
    item* item::get_next() const {return next;}

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
        using namespace std;

        item* current_item = inventory_head;
        if(current_item == nullptr){

            cout << "No items in this inventory." << endl;
            return;
        }

        int index = 1;
        while(current_item != nullptr){

            std::cout << endl << "[" << index << "]: " << current_item->name << "(" << current_item->quantity << ");";
            //if(current_item->next != nullptr) cout << "; ";  
            current_item = current_item->next;
            index++;
        }
        cout << endl << endl;
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

    item* item::copy_inventory(item* source_list_head, item* target_list_head){

        if (source_list_head == target_list_head && source_list_head != nullptr) {
            std::cerr << "Error: Attempt to copy inventory into itself!" << std::endl;
            return target_list_head;
        }
        item* current_item = source_list_head;
        while(current_item != nullptr){
            // because add item expects a reference to an item object, the pointer to current_item needs to be derefferenced
            target_list_head = add_item(target_list_head, *current_item); 
            current_item = current_item->next;
        }
        return target_list_head;
    }


    /*cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
        istringstream iss(line);
        string item_name;

        while(iss >> item_name){

            item* new_item = new item(item_name);
            int x = dist(gen);
            int y = dist(gen);
            World_Grid[y][x]->add_item_to_r_inventory(*new_item);
            delete new_item; // delete the object ater copying it to avoid memory
        }*/

    void distribute_each_item_randomly(item* item_to_place, std::vector<std::vector<Room*>> &World_Grid){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 4);
        

        for(int i = 0; i < item_to_place->get_quantity(); i++){

            int x = dist(gen);
            int y = dist(gen);
            item new_item(item_to_place->get_name());
            World_Grid[y][x]->add_item_to_r_inventory(new_item);
        }
    }

    void item::init_items_from_file(std::string filename, std::vector<std::vector<Room*>> &World_Grid){

        std::ifstream file(filename);

        if(!file.is_open()){

            std::cerr << "Couldn't open file: " << filename << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 4);
        std::string line;
        getline(file, line); // ignore first line of the file

        while(getline(file, line)){

            std::istringstream iss(line);
            std::string name;
            int quantity;
            if(!(iss >> name >> quantity)){

                std::cerr << "Skipping malformated line: " << line << std::endl;
                continue;
            }
            iss >> name >> quantity;
            item* new_item = new item(name, quantity);
            distribute_each_item_randomly(new_item, World_Grid);
            /*
            int x = dist(gen);
            int y = dist(gen);
            World_Grid[y][x]->add_item_to_r_inventory(*new_item);
            delete new_item; */
        }
    }
}