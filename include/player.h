#pragma once
#include "rooms.h"

namespace dungeon{

    class Room; // forward declaration?

    class player{

        private:

            Room* current_room;

        public:
            // initializes and constructs a player and a room at position (x, y)
            player(Room* starting_room) : current_room(starting_room) {};
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