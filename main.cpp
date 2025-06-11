#include "pg2.h"
#include "rooms.h"
int main(int argc, char** argv){

    std::vector<std::vector<dungeon::Room*>> World_Grid = dungeon::create_world();
    dungeon::delete_world(World_Grid);
    return 0;
}