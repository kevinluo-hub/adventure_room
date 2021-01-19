#include "keyword.h"

Keyword* keyword_init_default(char* first, char* second)
{
	Keyword* pK = (Keyword*)malloc(sizeof(Keyword));
	if (pK == NULL) {
		printf("failed to allocate memory.\n");
		free(pK);
		exit(1);
	}
	pK->first = first;
	pK->second = second;
	return pK;
}

Player* player_init_default(Room* current) {
	Player* pP = (Player*)malloc(sizeof(Player));
	pP->inventory = NULL;
	pP->i_count = 0;
	pP->current = current;
	pP->room_list = (Room**)malloc(sizeof(Room*) * 7);
	pP->success = 0;
	pP->omen = 0;
	return pP;
}

void keyword_set(Keyword* pK, char* first, char* second) {
	pK->first = first;
	pK->second = second;
}

int is_direction(Keyword* pK) {
	if (strcmp(pK->first, "go")==0)
		return 1;
	return 0;
}

int move(Player* pP, Keyword* pK) {
	if (strcmp(pK->second, "south") == 0) {
		printf("You can't go south in this game.\n");
		return 0;
	}
	else if (strcmp(pK->second, "north") == 0) {
		if (pP->current->north != NULL) {
			pP->current = pP->current->north;
		}
		else {
			Room* temp = random_room(pP->room_list);
			if (temp == NULL) {
				printf("There is no more new room to discover.\n");
				return 1;
			} 
			else if (temp->event == 1 && temp->place==Temple) {
				printf("\n\nYou have entered an event room. The Pigsty valley are now on your north and going every other direction will result in discovering a new room.\n");
				pP->current = temp;
				room_exit_south(&(pP->room_list[(int)Pigsty]), &temp);
			}
			else if (temp->event == 1) {
				if (pP->room_list[Pigsty]->north == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your south and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_south(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->up == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now below you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_down(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->down == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now above you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_up(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->west == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your east and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_east(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->east == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your west and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_west(&temp, &(pP->room_list[(int)Pigsty]));
				}
			}
			else {
				room_exit_north(&(pP->current), &temp);
				pP->current = temp;
			}
		}
	}
	else if (strcmp(pK->second, "east") == 0) {
		if (pP->current->east != NULL) {
			pP->current = pP->current->east;
		}
		else {
			Room* temp = random_room(pP->room_list);
			if (temp == NULL) {
				printf("There is no more new room to discover.\n");
				return 1;
			}
			else if (temp->event == 1 && temp->place == Temple) {
				printf("\n\nYou have entered an event room. The Pigsty valley are now on your north and going every other direction will result in discovering a new room.\n");
				pP->current = temp;
				room_exit_south(&(pP->room_list[(int)Pigsty]), &temp);
			}
			else if (temp->event == 1) {
				if (pP->room_list[Pigsty]->north == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your south and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_south(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->up == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now below you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_down(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->down == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now above you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_up(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->west == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your east and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_east(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->east == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your west and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_west(&temp, &(pP->room_list[(int)Pigsty]));
				}
			}
			else {
				room_exit_east(&(pP->current), &temp);
				pP->current = temp;
			}
		}
	}
	else if (strcmp(pK->second, "west") == 0) {
		if (pP->current->west != NULL) {
			pP->current = pP->current->west;
		}
		else {
			Room* temp = random_room(pP->room_list);
			if (temp == NULL) {
				printf("There is no more new room to discover.\n");
				return 1;
			}
			else if (temp->event == 1 && temp->place == Temple) {
				printf("\n\nYou have entered an event room. The Pigsty valley are now on your north and going every other direction will result in discovering a new room.\n");
				pP->current = temp;
				room_exit_south(&(pP->room_list[(int)Pigsty]), &temp);
			}
			else if (temp->event == 1) {
				if (pP->room_list[Pigsty]->north == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your south and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_south(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->up == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now below you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_down(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->down == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now above you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_up(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->west == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your east and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_east(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->east == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your west and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_west(&temp, &(pP->room_list[(int)Pigsty]));
				}
			}
			else {
				room_exit_west(&(pP->current), &temp);
				pP->current = temp;
			}
		}
	}
	else if (strcmp(pK->second, "up") == 0) {
		if (pP->current->up != NULL) {
			pP->current = pP->current->up;
		}
		else {
			Room* temp = random_room(pP->room_list);
			if (temp == NULL) {
				printf("There is no more new room to discover.\n");
				return 1;
			}
			else if (temp->event == 1 && temp->place == Temple) {
				printf("\n\nYou have entered an event room. The Pigsty valley are now on your north and going every other direction will result in discovering a new room.\n");
				pP->current = temp;
				room_exit_south(&(pP->room_list[(int)Pigsty]), &temp);
			}
			else if (temp->event == 1) {
				if (pP->room_list[Pigsty]->north == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your south and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_south(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->up == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now below you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_down(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->down == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now above you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_up(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->west == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your east and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_east(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->east == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your west and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_west(&temp, &(pP->room_list[(int)Pigsty]));
				}
			}
			else {
				room_exit_up(&(pP->current), &temp);
				pP->current = temp;
			}
		}
	}
	else if (strcmp(pK->second, "down") == 0) {
		if (pP->current->down != NULL) {
			pP->current = pP->current->down;
		}
		else {
			Room* temp = random_room(pP->room_list);
			if (temp == NULL) {
				printf("There is no more new room to discover.\n");
				return 1;
			}
			else if (temp->event == 1 && temp->place == Temple) {
				printf("\n\nYou have entered an event room. The Pigsty valley are now on your north and going every other direction will result in discovering a new room.\n");
				pP->current = temp;
				room_exit_south(&(pP->room_list[(int)Pigsty]), &temp);
			}
			else if (temp->event == 1) {
				if (pP->room_list[Pigsty]->north == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your south and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_south(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->up == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now below you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_down(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->down == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now above you and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_up(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->west == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your east and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_east(&temp, &(pP->room_list[(int)Pigsty]));
				}
				else if (pP->room_list[Pigsty]->east == NULL) {
					printf("\n\nYou have entered an event room. The Pigsty valley are now on your west and going every other direction will result in discovering a new room.\n");
					pP->current = temp;
					room_exit_west(&temp, &(pP->room_list[(int)Pigsty]));
				}
			}
			else {
				room_exit_down(&(pP->current), &temp);
				pP->current = temp;
			}
		}
	}
	else {
		printf("You have entered an invalid direction.");
	}
	return 0;
}

int is_take(Keyword* pK) {
	if (strcmp(pK->first, "take") == 0) {

		return 1;
	}
	return 0;
}

void take(Player* pP, Keyword* pK) {
	if (pP->current->items == NULL) {
		printf("There is no item in this room.\n");
		return;
	}
	if (pP->current->place == Memory && pP->current->condition == 0 && strcmp(pK->second, "book")==0) {
		printf("The old man asked for $10.\n");
		return;
	}
	if (pP->i_count >= 2) {
		printf("Your inventory is full, you must drop something before taking anything else.\n");
		return;
	}
	if (pP->inventory == NULL) {
		pP->inventory = item_take(&(pP->current->items), pK->second);
		if (pP->inventory==NULL) {
			printf("There is no such item in this room.\n");
			return;
		}
	}
	else {
		Item* temp = pP->inventory;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = item_take(&(pP->current->items), pK->second);
		if (temp->next == NULL) {
			printf("There is no such item in this room.\n");
			return;
		}
	}
	(pP->i_count)++;
	printf("\nYou have taken the %s.\n", pK->second);
}

int is_drop(Keyword* pK) {
	if (strcmp(pK->first, "drop") == 0) {
		return 1;
	}
	return 0;
}

void drop(Player* pP, Keyword* pK) {
	if (pP->inventory == NULL) {
		printf("Your inventory is empty, you have nothing to drop.\n");
		return;
	}
	Item* temp = pP->current->items;
	if (temp == NULL) {
		temp = item_take(&(pP->inventory), pK->second);
		pP->current->items = temp;
		if (temp == NULL) {
			printf("you don't have this item in your inventory.\n");
			return;
		}
	}
	else
	{
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = item_take(&(pP->inventory), pK->second);
		if (temp->next == NULL) {
			printf("you don't have this item in your inventory.\n");
			return;
		}
	}
	(pP->i_count)--;
	printf("\nYou have dropped the %s.\n", pK->second);
}

int is_look(Keyword* pK) {
	if (strcmp(pK->first, "look") == 0) {
		return 1;
	}
	return 0;
}

void look(Room* pR) {
	printf("%s\n", pR->description);
	if (pR->place==Memory && pR->condition ==0) {
		printf("You see an old, homeless man, with a book on his hand, asking for money in exchange for the book, saying the book can teach you kungfu.\n");
	}
	room_items(pR);
}

int is_inventory(Keyword* pK) {
	if (strcmp(pK->first, "inventory") == 0) {
		return 1;
	}
	return 0;
}

void print_inventory(Player* pP) {
	Item* temp = pP->inventory;
	while (temp != NULL) {
		printf("%s\n", temp->name);
		temp = temp->next;
	}
}

int is_use(Keyword* pK) {
	if (strcmp(pK->first, "use") == 0) {
		return 1;
	}
	return 0;
}

Item* use_inventory(Player* pP, char* name) {
	Item* temp = pP->inventory;
	while (temp != NULL) {
		if (strcmp(temp->name, name) == 0) {
			if (temp->use[(int)pP->current->place])
				return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


void player_destroy(Player** ppP) {
	item_destroy(&((*ppP)->inventory));
	(*ppP)->inventory = NULL;
	(*ppP)->current = NULL;
	for (int i = 0; i < 7; i++) {
		room_destroy(&(((*ppP)->room_list)[i]));
	}
	free((*ppP)->room_list);
	free(*ppP);
	*ppP = NULL;
}

void keyword_destroy(Keyword** ppK) {
	free(*ppK);
	*ppK = NULL;
}

Room* random_room(Room* list[7]) {
	Room* temp;
	int count = 0;
	int unvisited[7];
	for (int i = 1; i < 7; i++) {
		if (list[i]->visited == 0) {
			unvisited[count] = i;
			count++;
		}
	}
	if (count>0)
		printf("\nyou have %d rooms left in the room pile.\n", count-1);
	if (count == 0) {
		return NULL;
	}
	int r = rand() % count;
	list[unvisited[r]]->visited = 1;
	return list[unvisited[r]];
}