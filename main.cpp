#include "pg2.h"
#include "rooms.h"
#include "inventory.h"
#include "player.h"
#include "worldgrid.h"


int main(int argc, char** argv){

    std::vector<std::vector<dungeon::Room*>> World_Grid = create_world();

    std::cout << "Choose your starting room! (x = 0-4 & y = 0-4)" << std::endl;
    int x, y;
    std::cin >> x >> y;

    if((x < 0 || x > 4) || (y < 0 || y > 4)){

        std::cout << "Bruh, choose values between 0 and 4 for x and y..." << std::endl;
        exit(5);
    }

    dungeon::Room* starting_room = World_Grid[x][y];
    dungeon::player player1(starting_room);

    dungeon::Room::place_items_in_rand_rooms(World_Grid);
    print_worldgrid_with_player(player1, World_Grid);

    std::cout << "Now let's add and move some items" << std::endl;

    dungeon::item* sword = new dungeon::item("sword", 1);
    dungeon::item* pork = new dungeon::item("pork", 25);
    player1.add_item_to_p_inventory(*sword);
    player1.print_p_inventory();
    player1.add_item_to_p_inventory(*pork);
    player1.print_p_inventory();
    player1.clear_p_inventory();
    player1.print_p_inventory();

    delete sword;
    delete pork;

    dungeon::Room::print_inventory_of_all_rooms(World_Grid);

    /*
    std::string input;
    
    while(true){

        std::cout << "Where do you want do go? (n/s/e/w) or quit (q)" << std::endl;
        std::cin >> input;
        
        if(input == "w"){
            player1.move_north();
            player1.print_coordinates();
        }
        else if(input == "s"){
            player1.move_south();
            player1.print_coordinates();
        }
        else if(input == "d"){
            player1.move_east();
            player1.print_coordinates();
        }
        else if(input == "a"){
            player1.move_west();
            player1.print_coordinates();
        }
        else if(input == "q") break;
        else std::cout << "invalid input" << std::endl << std::endl;

        dungeon::Room::print_worldgrid_with_player(player1, World_Grid);
    } 
    */
    delete_world(World_Grid);
    return 0;
}