#include "rooms.h"

Room* room(char* description, Item* items, Scene place,
	Room* north, Room* south,
	Room* east, Room* west,
	Room* up, Room* down) {
	Room* pR = (Room*)malloc(sizeof(Room));
	if (pR == NULL) {
		printf("cannot allocate space.\n");
		free(pR);
		exit(1);
	}
	pR->description = description;
	pR->event = 0;
	pR->omen = 0;
	pR->visited = 0;
	pR->place = place;
	pR->items = items;
	pR->north = north;
	pR->south = south;
	pR->east = east;
	pR->west = west;
	pR->up = up;
	pR->down = down;
	return pR;
}

Room* room_init_default(char* description, Item* items, Scene place) {
	Room* pR = (Room*)malloc(sizeof(Room));
	if (pR == NULL) {
		printf("cannot allocate space.\n");
		free(pR);
		exit(1);
	}
	pR->description = description;
	pR->items = items;
	pR->place = place;
	pR->event = 0;
	pR->omen = 0;
	pR->condition = 0;
	pR->visited = 0;
	pR->north = NULL;
	pR->south = NULL;
	pR->east = NULL;
	pR->west = NULL;
	pR->up = NULL;
	pR->down = NULL;
}

void room_items(Room* pR) {
	Item* temp = pR->items;
	while (temp != NULL) {
		if (!(pR->place == Memory && strcmp(temp->name, "book")==0 && pR->condition==0))
			printf("you saw %s in this room. %s\n", temp->name, temp->description);
		temp = temp->next;
	}
}

void room_exit_north(Room** current, Room** other) {
	(*current)->north = (*other);
	(*other)->south = (*current);
}

void room_exit_south(Room** current, Room** other) {
	(*current)->south = (*other);
	(*other)->north = (*current);
}

void room_exit_east(Room** current, Room** other) {
	(*current)->east = (*other);
	(*other)->west = (*current);
}

void room_exit_up(Room** current, Room** other) {
	(*current)->up = (*other);
	(*other)->down = (*current);
}

void room_exit_west(Room** current, Room** other) {
	(*current)->west = (*other);
	(*other)->east = (*current);
}

void room_exit_down(Room** current, Room** other) {
	(*current)->down = (*other);
	(*other)->up = (*current);
}

void room_destroy(Room** ppR) {
	item_destroy(&((*ppR)->items));
	free(*ppR);
	*ppR = NULL;
}
