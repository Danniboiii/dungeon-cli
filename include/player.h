#pragma once
#include "rooms.h"
#include "inventory.h"

namespace dungeon{

    class Room; // forward declaration?
    class item;

    class player{

        private:

            Room* current_room;
            item* inventory_head;

        public:
            // initializes and constructs a player and a room at position (x, y)
            player(Room* starting_room) : current_room(starting_room), inventory_head(nullptr) {};
            // default destructor
            ~player();

            void move_north();
            void move_south();
            void move_east();
            void move_west();
            void print_coordinates() const;

            // adds an item to the player's inventory, needs an item reference
            void add_item_to_p_inventory(const item& new_item);
            void print_p_inventory();
            void clear_p_inventory();

            void pickup_all_items_from(Room* room);
            void pickup_one_item(Room* room, int item_index);

            // gets the current x-coordinate of the player
            int get_x();
            // gets the current y-coordinate of the player
            int get_y();
            // gets the current room of the player
            Room* get_room();
    };
}