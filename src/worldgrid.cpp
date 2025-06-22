#include <iostream>
#include <vector>
#include "rooms.h"
#include "worldgrid.h"
#include "player.h"



void print_vertical_lines_without_player(){

    using namespace std;
    for(int i = 0; i < 5; i++){

        if(i == 0) cout << "|";
        cout << "     |";
    }
}

void print_horizontal_lines(){

    using namespace std;
    for(int i = 0; i < 5; i++){

        if(i == 0) cout << "|";
        cout << "_____|";
    }
}

void print_worldgrid_without_player(){

    using namespace std;

    cout << " _____________________________" << "" << endl;
    for(int i = 1; i < 16; i++){

        if((i != 0) & (i % 3 == 0)) print_horizontal_lines();
        else print_vertical_lines_without_player();
        cout << endl;
        }
    cout << endl;
}

// prints one line, either with player ("  *  |"), or without player ("     |")
void print_vertical_lines_with_player(dungeon::player& player, int line){

    using namespace std;
    using namespace dungeon;
    cout << "|";

    for(int x = 0; x < 5; x++){

        if(player.get_x() == x && player.get_y() == line) cout << "  *  |";
        else cout << "     |";
    }
}

void print_worldgrid_with_player(dungeon::player& player, std::vector<std::vector<dungeon::Room*>> &World_Grid){

        using namespace std;

        cout << " _____________________________" << "" << endl;

        for (int line = 0; line < 5; line++){

            for(int subline = 0; subline < 3; subline++){

                if (subline == 0) print_vertical_lines_without_player();
                else if(subline == 1){

                    print_vertical_lines_with_player(player, line);
                    continue;
                }
                cout << endl; // important endl
            }
            print_horizontal_lines();
            cout << endl;
        }
    }

void link_rooms(std::vector<std::vector<dungeon::Room*>> &World_Grid){

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

std::vector<std::vector<dungeon::Room*>> create_world(){

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

            World_Grid[y][x]->Room::clear_r_inventory();
            delete World_Grid[y][x];
        }
    }
    return;
}