#include "rooms.h"
#include "inventory.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>



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

    Room::~Room(){

        while(inventory_head != nullptr){

            item* temp = inventory_head->get_Next(); // zeiger auf den nächsten knoten MERKEN!
            delete inventory_head; // aktuellen knoten leeren
            inventory_head = temp; // der kopf ist jetzt der zeiger auf den nächsten knoten
        }
    }

    void Room::print_coordinates() const{

        std::cout << std::endl << std::endl << std::endl << "Room Location (x:" << x_coordinate << ", " << "y:" << y_coordinate << ")" << std::endl;
    }

    // prints one line, either with player ("  *  |"), or without player ("     |")
    void Room::print_vertical_lines_with_player(player& player, int line){

        using namespace std;
        cout << "|";

        for(int x = 0; x < 5; x++){

            if(player.get_x() == x && player.get_y() == line) cout << "  *  |";
            else cout << "     |";
        }
    }

    // prints the world grid with the players location
    void Room::print_worldgrid_with_player(player& player, std::vector<std::vector<Room*>> &World_Grid){

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


    void Room::add_item_to_r_inventory(const std::string& item_name){

        inventory_head = item::add_item(inventory_head, item_name);
    }

    void Room::print_single_r_inventory(){

        item::print_inventory(inventory_head);
    }

    void Room::clear_r_inventory(){

        inventory_head = item::clear_inventory(inventory_head);
    }

    void Room::print_inventory_of_all_rooms(std::vector<std::vector<Room*>> &World_Grid){

        using namespace std;
        for(int y = 0; y < 5; y++){
            for (int x = 0; x < 5; x++){

                // wrong: cout << World_Grid[y][x]->item::print_inventory(inventory_head);
                // only prints the items of a room, if there are any.
                if(World_Grid[y][x]->inventory_head != nullptr){
                    cout << "Items in Room (" << y << ", " << x << "): ";
                    item::print_inventory(World_Grid[y][x]->inventory_head);
                    //cout << endl;
                }

            }
        }
    }

    void Room::place_items_in_rand_rooms(std::vector<std::vector<Room*>> &World_Grid){

        using namespace std;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 4);
        cout << "Enter items that will be placed in the World Grid: <item> <item> <item> etc." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

        string line;
        getline(cin, line);
        istringstream iss(line);
        string item_name;

        while(iss >> item_name){

            int x = dist(gen);
            int y = dist(gen);
            World_Grid[y][x]->add_item_to_r_inventory(item_name);
        }
    }


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
