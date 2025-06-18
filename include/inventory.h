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
        item* initialize_inventory();
        item* add_item(const std::string& name, item* first_item);
        void free_list(item* inventory_head);

        // gets the next item from the inventory list
        item* get_Next();

        static void print_inventory(item* inventory_head);
        static item* search_inventory(item* inventory_head, const std::string& search_name);
    };
}


