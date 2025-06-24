#include "pg2.h"
#include "rooms.h"
#include "inventory.h"
#include "player.h"
#include "worldgrid.h"
#include <string>

void game_turn(dungeon::player& player1);


int main(int argc, char** argv){

    std::vector<std::vector<dungeon::Room*>> World_Grid = create_world();

    std::cout << "Choose your starting room! (x = 0-4 & y = 0-4)" << std::endl;
    std::string start_coordinates; int x, y;

    std::getline(std::cin, start_coordinates);
    std::stringstream ss(start_coordinates);
    if(!(ss >> x >> y) || !(ss.eof())){

        std::cout << "Bruh, enter two integers (0-4) seperated by space: <x> <space> <y>" << std::endl;
        exit(4);
    }

    if((x < 0 || x > 4) || (y < 0 || y > 4)){

        std::cout << "Bruh, choose values between 0 and 4 for x and y..." << std::endl;
        exit(5);
    }


    dungeon::Room* starting_room = World_Grid[x][y];
    dungeon::player player1(starting_room);

    dungeon::item::init_items_from_file("items.txt", World_Grid);
    //dungeon::Room::place_items_in_rand_rooms(World_Grid);
    dungeon::Room::print_inventory_of_all_rooms(World_Grid);
    print_worldgrid_with_player(player1, World_Grid);

    std::string input;

    
    while(true){
        
        std::cout << "Where do you want do go? (w/a/s/d) or quit (q)" << std::endl;
        std::cin >> input;
        
        if(input == "w"){
            player1.move_north();
            player1.print_coordinates();
            game_turn(player1);
        }
        else if(input == "s"){
            player1.move_south();
            player1.print_coordinates();
            game_turn(player1);
        }
        else if(input == "d"){
            player1.move_east();
            player1.print_coordinates();
            game_turn(player1);
        }
        else if(input == "a"){
            player1.move_west();
            player1.print_coordinates();
            game_turn(player1);
        }
        else if(input == "q") break;
        else std::cout << "invalid input" << std::endl << std::endl;

        print_worldgrid_with_player(player1, World_Grid);
    } 

    delete_world(World_Grid);
    return 0;
}



void game_turn(dungeon::player& player1){
    using namespace std;

    dungeon::Room* current_room = player1.get_room();
    if(current_room->get_inventory() != nullptr){

        current_room->print_single_r_inventory();
        cout << "Choose an item to pickup (by number), or pick up all (a)" << endl;
        string input; cin >> input;
        if(input == "a" || input == "A"){

            player1.pickup_all_items_from(current_room);
        }
        else{
            try{
                int item_index = stoi(input);
                dungeon::item* room_inventory_head = current_room->get_inventory();
                dungeon::item* item_to_pickup = dungeon::item::get_item_by_index(room_inventory_head, item_index);
                if(item_to_pickup){
                    string picked_item_name = item_to_pickup->get_name();
                    int picked_item_quantity = item_to_pickup->get_quantity();
                    player1.add_item_to_p_inventory(*item_to_pickup);
                    current_room->set_inventory(
                        dungeon::item::remove_item(
                            current_room->get_inventory(),
                            picked_item_name,
                            picked_item_quantity
                        )
                    ); // copilot magic...
                    //cout << "You picked up <" << item_to_pickup->get_name() << ">" << endl;
                    // i'm keeping this error in. i've spent almost 2h degbugging it.....
                    cout << "You picked up <" << picked_item_name << ">" << endl;
                }
                else cout << "Invalid Item Index" << endl;
            }
            catch(std::invalid_argument&) {
                std::cout << "Invalid input – enter a number or 'a' to pick up all." << std::endl;
            }
        }
    }
        player1.print_p_inventory();
}

/*
explaination for ll 103-110:
What's wrong?
dungeon::item::remove_item(...) returns the new head of the list, but you are not assigning it back to the room's inventory.
So, if the removed item was the head, the room's inventory_head will still point to the deleted item, causing undefined behavior.

You must update the room's inventory head after removing the item:

But:
inventory_head is a private member of Room, so you can't access it directly from outside.
You need to add a setter in your Room class:
*/