#include <vector>
#include <string>
#pragma once

// everything inside this dungeon namespace must be used with dungeon::xyz
// or one can use 'using namespace dungeon' to avoid all that
namespace dungeon{ 
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

        void print_coordinates() const; // declared in rooms.h
    };


    void link_rooms(std::vector<std::vector<Room*>>& World_Grid);
    std::vector<std::vector<Room*>> create_world();
    void delete_world(std::vector<std::vector<Room*>>& World_Grid);
}