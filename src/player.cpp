#include <iostream>
#include "player.h"
#include "rooms.h"


namespace dungeon{

    player::~player() {

        while(inventory_head != nullptr){

            item* temp = inventory_head->get_next(); // zeiger auf den nächsten knoten MERKEN!
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
    
    void player::add_item_to_p_inventory(const item& new_item){

        inventory_head = item::add_item(inventory_head, new_item);
    }

    void player::print_p_inventory(){

        std::cout << "Your inventory contains these items:" << std::endl;
        item::print_inventory(inventory_head);
    }

    void player::clear_p_inventory(){

        inventory_head = item::clear_inventory(inventory_head);
    }

    void player::pickup_all_items_from(Room* room){

        if(room->get_inventory() == nullptr){

            std::cout << "There are no items in the room" << std::endl;
            return;
        }
        item* source_list_head = room->get_inventory(); // important because room->get_inventory() is not an lvalue! look into lvalue & rvalues
        inventory_head = item::copy_inventory(source_list_head, inventory_head);
        room->clear_r_inventory();
    }

    


    void player::pickup_one_item(Room* room, int item_index){

        item* room_inventory_head = room->get_inventory();
        item* current_item = room_inventory_head;
        int safe_index = item_index -1;
        
        for(int i = 0; i < safe_index; i++){

            if(current_item == nullptr){

                std::cout << "There are no items in the room" << std::endl;
                return;
            }
            current_item = current_item->get_next();
        }
        if(current_item == nullptr){

            std::cout << "You picked an invalid item index" << std::endl;
            return;
        }
        add_item_to_p_inventory(*current_item);
        item::remove_item(room_inventory_head, current_item->get_name(), current_item->get_quantity()); 
    }


    int player::get_x(){ return current_room->get_x(); }
    int player::get_y(){ return current_room->get_y(); }
    Room* player::get_room(){ return current_room; }

}