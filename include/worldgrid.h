#pragma once
#include <iostream>
#include <vector>
#include "rooms.h"
#include "player.h"

void print_vertical_lines_without_player();
void print_horizontal_lines();
void print_worldgrid_without_player();
void print_vertical_lines_with_player(dungeon::player& player, int line);
// prints the world grid with the players location
void print_worldgrid_with_player(dungeon::player& player, std::vector<std::vector<dungeon::Room*>> &World_Grid);

void link_rooms(std::vector<std::vector<dungeon::Room*>> &World_Grid);
std::vector<std::vector<dungeon::Room*>> create_world();
void delete_world(std::vector<std::vector<dungeon::Room*>>& World_Grid);