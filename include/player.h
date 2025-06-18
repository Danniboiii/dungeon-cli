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

            // gets the current x-coordinate of the player
            int get_x();
            // gets the current y-coordinate of the player
            int get_y();
    };
}