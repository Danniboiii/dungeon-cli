#include "rooms.h"
#include "inventory.h"
#include "worldgrid.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>


namespace dungeon{

    Room::Room() : x_coordinate(0), y_coordinate(0), is_edge(false), is_corner(false), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}
    Room::Room(int x, int y) : x_coordinate(x), y_coordinate(y), is_edge(false), is_corner(false), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {

        if(x == 0 || y == 0) is_edge = true;
        if(x == 4 || y == 4) is_edge = true;
        if((x == 0 && y == 0) || (x == 0 && y == 4) || (x == 4 && y == 0) || (x == 4 && y == 4)) is_corner = true;
    }

    Room::~Room(){delete inventory_head; }

    void Room::print_coordinates() const{

        std::cout << std::endl << std::endl << std::endl << "Room Location (x:" << x_coordinate << ", " << "y:" << y_coordinate << ")" << std::endl;
    }

    void Room::add_item_to_r_inventory(const item& new_item){

        inventory_head = item::add_item(inventory_head, new_item);
    }

    void Room::print_single_r_inventory(){

        std::cout << "This room contains the following items" << std::endl;
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
                if(World_Grid[y][x]->get_inventory() != nullptr){
                    cout << "Items in Room (" << x << ", " << y << "): ";
                    item::print_inventory(World_Grid[y][x]->get_inventory());
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

        string line;
        getline(cin, line);
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
        istringstream iss(line);
        string item_name;

        while(iss >> item_name){

            item* new_item = new item(item_name);
            int x = dist(gen);
            int y = dist(gen);
            World_Grid[y][x]->add_item_to_r_inventory(*new_item);
            delete new_item; // delete the object ater copying it to avoid memory leaks
        }
    }
} // namespace dungeon
