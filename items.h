#ifndef ITEMS_H
#define ITEMS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum scene { Pigsty, Memory, Hospital, Axeland, Street, Hideout, Temple };
typedef enum scene Scene;


struct item {  
	//string containing the item name
	char * name;
	//string containing the item description
	char * description;
	//int array intdicating what room can the item be used in
	int use[7];
	//item pointer to the next item
	struct item* next;
};

typedef struct item Item;

//function to initialize an item
Item * item_init_default(char * name, char * description, int use[7], Item * next);
//check if there's item
int item_is_empty(Item *pI);
//returns the name of the item
char * item_name(Item *pI);
//returns the description of the item
char * item_description(Item *pI);
//return the next item
Item * item_next(Item *pI);
//remove an item from an item list and returns it, returns NULL if the item that matches the string name cannot be find in the list
Item * item_take(Item **ppI, char* name);
//free the spaces allocated by a list of items
void item_destroy(Item **ppI);
//prints the description of an item
void print_item(Item * pI);

#endif // !ITEMS_H

