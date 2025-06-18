#include <iostream>
#include "player.h"
#include "rooms.h"


namespace dungeon{

    player::~player() {

        while(inventory_head != nullptr){

            item* temp = inventory_head->get_Next(); // zeiger auf den nächsten knoten MERKEN!
            delete inventory_head; // aktuellen knoten leeren
            inventory_head = temp; // der kopf ist jetzt der zeiger auf den nächsten knoten
        }
    }

    void player::move_north(){

        if(current_room->north != nullptr) current_room = current_room->north;
        else std::cout << "A wall prevents you from moving north" << std::endl;
    }

    void player::move_south(){

        if(current_room->south != nullptr) current_room = current_room->south;
        else std::cout << "A wall prevents you from moving south" << std::endl;
    }

    void player::move_east(){

        if(current_room->east != nullptr) current_room = current_room->east;
        else std::cout << "A wall prevents you from moving east" << std::endl;
    }

    void player::move_west(){

        if(current_room->west != nullptr) current_room = current_room->west;
        else std::cout << "A wall prevents you from moving west" << std::endl;
    }
    
    void player::print_coordinates() const{
        if(current_room) current_room->print_coordinates();
    }

    int player::get_x(){ return current_room->get_x(); }
    int player::get_y(){ return current_room->get_y(); }
}