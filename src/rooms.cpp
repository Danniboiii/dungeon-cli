#include "rooms.h"
#include <vector>
#include <string>
#include <iostream>



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

namespace dungeon{

    Room::Room() : x_coordinate(0), y_coordinate(0), is_edge(false), is_corner(false), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}
    Room::Room(int x, int y) : x_coordinate(x), y_coordinate(y), is_edge(false), is_corner(false), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {

        if(x == 0 || y == 0) is_edge = true;
        if(x == 4 || y == 4) is_edge = true;
        if((x == 0 && y == 0) || (x == 0 && y == 4) || (x == 4 && y == 0) || (x == 4 && y == 4)) is_corner = true;
    }

    void Room::print_coordinates() const{

        std::cout << "Room Location (x:" << x_coordinate << ", " << "y:" << y_coordinate << ")" << std::endl << std::endl;
    }

    void print_vertical_lines_with_player(player& player){

    using namespace std;
    for(int i = 0; i < 5; i++){

        if(i == 0) cout << "|";
        for(int j = 0; j < 5; i++){

            //if(player.get_x() == World_Grid[i][j]->get_x && )
            cout << " ";
        }
        cout << "|";
    }
}

    // prints the world grid template
    void Room::print_worldgrid_without_player(){

        using namespace std;

        cout << " _____________________________" << "" << endl;
        for(int i = 1; i < 16; i++){

            if((i != 0) & (i % 3 == 0)) print_horizontal_lines();
            else print_vertical_lines_without_player();
            cout << endl;
            }
        cout << endl;
    }

    // prints the world grid with the players location
    void print_worldgrid_with_player(player& player){

        using namespace std;

        cout << " _____________________________" << "" << endl;
        for(int i = 1; i < 16; i++){

            if((i != 0) & (i % 3 == 0)) print_horizontal_lines();
            else print_vertical_lines_with_player(player);
            cout << endl;
            }
    
    }



    // print the world grid with the player location
    //

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
