#ifndef KEYWORD_H
#define KEYWORD_H
#include "rooms.h"

struct keyword {
	//first part of the keyword
	char* first;
	//second part of the keyword
	char* second;
};
typedef struct keyword Keyword;

struct player {
	//items held by the player
	Item* inventory;
	//amount of items in the inventory
	int i_count;
	//the room player is in currently
	Room* current;
	//the array of all rooms that were set up for easy access
	Room** room_list;
	//indicates if the player has reached the win condition
	int success;
	//record the number of omen that the player has collected
	int omen;
};
typedef struct player Player;

//function to initialize the player
Player* player_init_default(Room* current);
//function to initialize the keyword
Keyword* keyword_init_default(char* first, char* second);
//editing the keyword by passing in two strings
void keyword_set(Keyword* pK, char* first, char* second);
//determines if the user is entering a direction
int is_direction(Keyword* pK);
//functions to move the player to another room
int move(Player* pP, Keyword* pK);
//check if the user is trying to take an item in the room
int is_take(Keyword* pK);
//take an item from the room
void take(Player* pP, Keyword* pK);
//check if the user is trying to drop an item in the room
int is_drop(Keyword* pK);
//drop an item into the room
void drop(Player* pP, Keyword* pk);
//check if the user is trying to look
int is_look(Keyword* pK);
//prints the room description
void look(Room* pR);
//check if the user is trying to see their inventory
int is_inventory(Keyword* pK);
//prints the items that the player has on them
void print_inventory(Player* pP);
//check if the player is trying to use an item
int is_use(Keyword* pK);
//return the item if the user has it can it can be used in the current room, otherwise returns NULL
Item* use_inventory(Player* pP, char* name);
//free the space allocated by the player
void player_destroy(Player** ppP);
//free the space allocated by a keyword
void keyword_destroy(Keyword** ppK);
//pick out a random, unvisited room in the room list and connect it to the map when the user prompt to discover a new room
Room* random_room(Room* list[7]);

#endif
