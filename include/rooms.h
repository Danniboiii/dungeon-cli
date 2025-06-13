#pragma once
#include <vector>
#include <string>
#include "player.h"

// everything inside this dungeon namespace must be used with dungeon::xyz
// or one can use 'using namespace dungeon' to avoid all that
namespace dungeon{ 

    class player;

    //class definition
    class Room {
    
    private:
        
        int x_coordinate;
        int y_coordinate;
        bool is_edge;
        bool is_corner;

    public:

        Room* north;
        Room* south;
        Room* east;
        Room* west;

        // deault constructor, make sure to keep the order of the member variables
        Room();
        // make a new room on xy coordinates, make sure to keep the order of the member variables
        Room(int x, int y);

        // gets the x-coordiante of the room current room
        int const get_x() { return x_coordinate; }
        // gets the y-coordiante of the room current room
        int const get_y() { return y_coordinate; }

        // declared in rooms.h
        void print_coordinates() const; 
        // prints the world_grid onto the console
        static void print_worldgrid_without_player();
        static void print_vertical_lines_with_player(player& player, int line);
        static void print_worldgrid_with_player(player& player, std::vector<std::vector<Room*>> &World_Grid);
    };

    void link_rooms(std::vector<std::vector<Room*>>& World_Grid);
    std::vector<std::vector<Room*>> create_world();
    void delete_world(std::vector<std::vector<Room*>>& World_Grid);
}