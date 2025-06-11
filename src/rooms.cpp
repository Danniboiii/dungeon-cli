#include "rooms.h"
#include <vector>
#include <string>


namespace dungeon{

void link_rooms(std::vector<std::vector<Room*>> &World_Grid){

    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){

            if(y > 0) World_Grid[y][x]->north = World_Grid[y-1][x]; // north neighbour
            if(y < 4) World_Grid[y][x]->south = World_Grid[y+1][x]; // south neighbour
            if(x < 4) World_Grid[y][x]->east = World_Grid[y][x+1]; // east neighbour
            if(x > 0) World_Grid[y][x]->west = World_Grid[y][x-1]; // west neighbour
        }
    }
    return;
}

std::vector<std::vector<Room*>> create_world(){

    std::vector<std::vector<dungeon::Room*>> World_Grid(5, std::vector<dungeon::Room*>(5, nullptr));
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){

            World_Grid[y][x] = new dungeon::Room(x,y);
        }
    }
    link_rooms(World_Grid);
    return World_Grid;
}

void delete_world(std::vector<std::vector<dungeon::Room*>>& World_Grid){

    for (int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){

            delete World_Grid[y][x];
        }
    }
    return;
}





} // namespace dungeon
