#ifndef ROOMS_H
#define ROOMS_H
#include "items.h"

struct room {
	//strings that contains the room desciption
	char* description;
	//items in the room
	Item* items;
	//indicates if it's an event room
	int event;
	//indicates if the room contains an omen
	int omen;
	//indicates if the room has been visited
	int visited;
	//indicates different stages of the room
	int condition;
	//an enum used to indicates what is the room and also for organizing
	Scene place;

	//pointers to all directions of the room
	struct room* north;
	struct room* south;
	struct room* east;
	struct room* west;
	struct room* up;
	struct room* down;
};

typedef struct room Room;

//function to initialize the room with specific exits to other rooms
Room* room(char* description, Item* items, Scene place,
	Room* north, Room* south,
	Room* east, Room* west,
	Room* up, Room* down);
//function to initialize an isolated room with no exit passed in
Room* room_init_default(char* description, Item* items, Scene place);
//prints out the items contained in the room
void room_items(Room* pR);

//functions to set exit to current rooom in different directions
void room_exit_north(Room** current, Room** other);
void room_exit_south(Room** current, Room** other);
void room_exit_east(Room** current, Room** other);
void room_exit_up(Room** current, Room** other);
void room_exit_west(Room** current, Room** other);
void room_exit_down(Room** current, Room** other);

//free the memory allocated by a room
void room_destroy(Room** ppR);

#endif 

