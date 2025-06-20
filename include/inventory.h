#pragma once

#include "rooms.h"
#include "player.h"
#include <string>

namespace dungeon{

    class item{

        private:
            std::string name;
            item* next;

        public:
        // constructor for an item object, it's not in a list, thus has no next-ptr
        item(const std::string& item_name) : name(item_name), next(nullptr) {}
        // creates an empty inventory
        item* initialize_inventory();

        // clears and deletes every item, and returns nullptr
        static item* clear_inventory(item* inventory_head);

        // gets the next item from the inventory list
        item* get_Next();

        // adds an item to the inventory, but needs the first item as a list head
        static item* add_item(item* first_item, const std::string& name);
        static void print_inventory(item* inventory_head);
        static item* search_inventory(item* inventory_head, const std::string& search_name);
    };
}


