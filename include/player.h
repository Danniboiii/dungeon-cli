#include "rooms.h"

namespace dungeon{

    class player{

        private:

            Room* current_room;

        public:
            // initializes and constructs a player and a room at position (x, y)
            player(Room* start) : current_room(start) {};
            // default destructor
            ~player();

            void move_north();
            void move_south();
            void move_east();
            void move_west();
            void print_coordinates() const{
                if(current_room) current_room->print_coordinates();
            }
        
    };


}