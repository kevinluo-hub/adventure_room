#include "items.h"

Item * item_init_default(char * name, char * description, int use[7], Item * next) {
	Item * new_item = (Item*)malloc(sizeof(Item));
	new_item->name = name;
	new_item->description = description;
	new_item->next = next;
	for (int i = 0; i < 7; i++) {
		(new_item->use)[i] = use[i];
	}
	return new_item;
}


int item_is_empty(Item * pI) {
	if (pI == NULL)
	{
		return 1;
	}
	return 0;
}

Item * item_take(Item ** ppI, char * name)
{
	if (strcmp((*ppI)->name, name) == 0)
	{
		Item* temp = *ppI;
		*ppI = (*ppI)->next;
		temp->next = NULL;
		return temp;
	}

	Item * iterator = *ppI;
	while (iterator->next != NULL && strcmp(iterator->next->name, name) != 0)
	{
		iterator = iterator->next;
	}
	if (iterator->next == NULL) {
		return NULL;
	}
	Item * temp = iterator->next;
	iterator->next = iterator->next->next;
	temp->next = NULL;
	return temp;
}

void item_destroy(Item ** ppI)
{
	if (*ppI != NULL)
	{
		item_destroy(&((*ppI)->next));
		free(*ppI);
		*ppI = NULL;
	}

}

char * item_name(Item * pI)
{
	return pI->name;
}

char * item_description(Item * pI)
{
	return pI->description;
}

Item * item_next(Item * pI)
{
	return pI->next;
}
void print_item(Item * pI)
{
	while (pI != NULL) {
		printf("%s \n%s \n", pI->name, pI->description);
		pI = pI->next;
	}
}
