#include "pg2.h"
#include "rooms.h"
#include "player.h"


int main(int argc, char** argv){

    std::vector<std::vector<dungeon::Room*>> World_Grid = dungeon::create_world();

    dungeon::Room* start = World_Grid[2][2];
    dungeon::player player1(start);

    std::string input;

    while(true){

        std::cout << "Where do you want do go? (n/s/e/w) or quit (q)" << std::endl;
        std::cin >> input;
        
        if(input == "n"){
            player1.move_north();
            player1.print_coordinates();
        }
        else if(input == "s"){
            player1.move_south();
            player1.print_coordinates();
        }
        else if(input == "e"){
            player1.move_east();
            player1.print_coordinates();
        }
        else if(input == "w"){
            player1.move_west();
            player1.print_coordinates();
        }
        else if(input == "q") break;
        else std::cout << "invalid input" << std::endl << std::endl;
    }

    dungeon::delete_world(World_Grid);
    return 0;
}