#pragma once

#include "rooms.h"
#include "player.h"
#include <string>

namespace dungeon{

    class item{

        private: // structure these after importance (best practice)
            std::string name;
            int quantity;
            item* next;

        public:
        // constructor for an item object, it's not in a list, thus has no next-ptr
        item(const std::string &item_name, int num_of_item = 1) : name(item_name), quantity(num_of_item), next(nullptr) {}

        //copy constructor that takes an item reference and creates a new item with the values of item_to_copy, but sets next to nullptr
        item(const item &item_to_copy) : name(item_to_copy.name), quantity(item_to_copy.quantity), next(nullptr) {}

        // clears and deletes every item, and returns nullptr
        static item* clear_inventory(item* inventory_head);

        std::string get_name() const;
        int get_quantity() const;
        item* get_next() const;
        static item* get_item_by_index(item* inventory_head, int index);

        // adds an item to the inventory, but needs the first item as a list head
        static item* add_item(item* first_item, const item& new_item);
        static item* remove_item(item* inventory_head, const std::string& item_to_remove, int amount = 1);

        static void print_inventory(item* inventory_head);
        // searches the inventory for a certain item
        static item* search_inventory(item* inventory_head, const std::string& search_name);
        // copys the contents of source_list_head to target_list_head, returns the (updated) target_list_head
        static item* copy_inventory(item* &source_list_head, item* target_list_head);
    };
}


