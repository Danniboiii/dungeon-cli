#pragma once
#include <vector>
#include <string>
#include "player.h"
#include "inventory.h"

// everything inside this dungeon namespace must be used with dungeon::xyz
// or one can use 'using namespace dungeon' to avoid all that
namespace dungeon{ 

    class player;
    class item;

    //class definition
    class Room {
    
    private:
        
        int x_coordinate;
        int y_coordinate;
        bool is_edge;
        bool is_corner;
        item* inventory_head;

    public:

        Room* north;
        Room* south;
        Room* east;
        Room* west;

        // deault constructor, make sure to keep the order of the member variables
        Room();
        // make a new room on xy coordinates, make sure to keep the order of the member variables
        Room(int x, int y);

        // delete the room and its inventory
        ~Room();

        // gets the x-coordiante of the room current room
        int const get_x() { return x_coordinate; }
        // gets the y-coordiante of the room current room
        int const get_y() { return y_coordinate; }

        // declared in rooms.h
        void print_coordinates() const; 

        // adds an item to a room's inventory, needs an item reference
        void add_item_to_r_inventory(const item& new_item);
        void print_single_r_inventory();
        void clear_r_inventory();
        static void print_inventory_of_all_rooms(std::vector<std::vector<Room*>> &World_Grid);

        // subject to change!!! it's manual now but will be automatic!
        static void place_items_in_rand_rooms(std::vector<std::vector<Room*>> &World_Grid);
    };
}