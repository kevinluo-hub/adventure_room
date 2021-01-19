#include "keyword.h"

//initializing the rooms before the game starts
void room_setup(Player* pP);
//function to take string with scanning each char at a time for safety
void scan_word(char word[30]);
//reseting string for the next scan
void reset_string(char first[30], char second[30]);
//cleaning up the line in cases of invalid input
void clear_keyboard_buffer();
//the function that constructs the game play
void play(Player* pP);

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int temp[7] = { 0,0,1,1,0,0,0 };
	Player* p1 = player_init_default(room_init_default("You are at the Pigtsy Valley.",
		item_init_default("paperclip", "Locking picking is one of your skill, this might help you later.",
			temp, NULL), Pigsty));
	room_setup(p1);
	printf("This game used part of the storyline in \"Kung Fu Hustle\", a Hong Kong classic movie.\n");
	printf("You found yourself in a small town of 1930s Shanghai, which was controlled by the notorious Axe Gang.\n");
	printf("You start as a petty crook, it might sound unrealistic, but the goal is to become the best Kung Fu artist around and restore the peace in town.\n");
	printf("The keywords are \"look\", \"inventory\", \"go + direction\", \"take/drop/use + item\". Good luck!\n\n");
	play(p1);
	player_destroy(&p1);
	return 0;
}

void play(Player* pP) {
	char first[30];
	char second[30];
	int status;
	Keyword* kw = keyword_init_default(NULL, NULL);
	printf("\n\n");
	look(pP->current);
	while (pP->success == 0) {
		printf("\n\n");
		printf("enter your action: \n");
		scan_word(first);
		// add "what?"
		if (!(strcmp(first, "take") && strcmp(first, "drop") && strcmp(first, "go") && strcmp(first, "use")))
			scan_word(second);
		clear_keyboard_buffer();
		keyword_set(kw, first, second);
		if (strcmp(first, "kevin")==0) {
			if (pP->room_list[(int)Temple]->visited != 0) {
				pP->current = pP->room_list[(int)Temple];
				printf("\n\n");
				look(pP->current);
				if (pP->current->condition == 1) {
					if (use_inventory(pP, "book")) {
						printf("The top killer has been waiting for you here!\n");
						printf("He does not care if you are part of Axe Gang, and he claims that you should make a worthy opponent beacause of your potiential.\n");
						printf("He has started his attack!!\n");
					}
					else {
						printf("The top killer said hi to you with a smile on his face, with no intention of fighting you what so ever because you are a nobody.\n");
					}
				}
			}
			else {
				printf("What are you talking about?\n");
			}
		}
		else if (is_direction(kw)) {
			if (pP->current->place == Axeland && pP->current->condition == 0) {
				printf("\n\nYou are captured! You will have to free yourself first!!\n\n");
			}
			else if ((pP->current->place == Temple && pP->current->condition == 1)
				&& use_inventory(pP, "book")) {
				printf("\n\nYou are not going anywhere! You are in the middle of a fight!!\n\n");
			}
			else
			{
				if (move(pP, kw)) {
					printf("You lost!!\n");
					break;
				}
				printf("\n\n");
				look(pP->current);
				if (pP->current->omen) {
					printf("\nYou found an omen in this Room!\n");
					(pP->omen)++;
					pP->current->omen = 0;
				}
			}
			if (pP->current->place == Axeland) {
				if (pP->current->condition == 0) {
					printf("You are captured and handcuffed by gang members, and the cold blooded leader of the Axe Gang, Brother Sen, is about to throw an Axe at you.\n");
					if (use_inventory(pP, "paperclip") == NULL) {
						printf("There is no possible way to escape. You are killed by Brother Sen.\n");
						printf("\n\nAND I HAD TO REVIVE YOU DUE TO THE REQUIRED LOSING CONDITION OF THIS PROJECT!!\n\n");
						printf("As a punishment, all your items are dropped off.\n\n");
						while (pP->inventory != NULL) {
							Keyword* ktemp;
							 ktemp = keyword_init_default("drop", pP->inventory->name);
							 drop(pP, ktemp);
							 keyword_destroy(&ktemp);
						}
						pP->current = pP->room_list[(int)Pigsty];
						look(pP->current);
					}
				}
				else if (pP->current->condition == 1) {
					printf("Brother Sen was impressed by your lock-picking skill and asked you to free the top killer of the world at the psychiatric hospital/prison.\n");
				}
				else if (pP->current->condition == 2) {
					printf("Brother Sen heard that you have freed the top killer and welcomes you to the family.\n");
					printf("You are officially part of the Axe Gang, who controls the town.\n");
				}
			} 
			else if (pP->current->place == Temple) {
				if (pP->current->condition == 1) {
					if (use_inventory(pP, "book")) {
						printf("The top killer has been waiting for you here!\n");
						printf("He does not care if you are part of Axe Gang, and he claims that you should make a worthy opponent beacause of your potiential.\n");
						printf("He has started his attack!!\n");
					}
					else {
						printf("The top killer said hi to you with a smile on his face, with no intention of fighting you what so ever because you are a nobody.\n");
					}
				}
			}
			else if (pP->current->place == Pigsty && pP->current->condition == 1) {
				if (pP->i_count==2 && pP->omen==2) {
					printf("The top killer has been waiting for you here, hoping that you have fulfilled the potential he sensed in you and finally become a worthy opponent of his.\n");
					printf("Somehow, you feel an energy in your body.\n");
					printf("You jumped into the sky, back flipped, then fall down and blew a huge hit towards the ground.\n");
					printf("You have successfully perform the godly martial art, the Buddha Palm.\n");
					
					pP->success = 1;
				}
				else {
					printf("The top killer said hi to you with a smile on his face, acting like nothing happened two weeks ago.\n");
					printf("He has no intention of fighting you.\n");
					printf("HINT: You need to have 2 items and 2 omens to win the game.\n");
				}
			}
		}
		else if (is_take(kw)) {
			take(pP, kw);
		}
		else if (is_drop(kw)){
			if ((use_inventory(pP, "book")) && (pP->current->place == Temple && pP->current->condition == 1 ||
				pP->current->place == Pigsty && pP->current->condition == 1) &&
				strcmp(kw->second, "book")==0) {
				printf("\nWho are you kidding? The Buddha Palm is your only chance to beat the top killer!!!\n");
				printf("Dropping a book right now is not an option.\n");
			}
			else {
				drop(pP, kw);
			}
		}
		else if (is_look(kw)) {
			printf("\n\n");
			look(pP->current);
		}
		else if (is_use(kw)) {
			Item* temp = use_inventory(pP, kw->second);
			if (temp == NULL) {
				printf("You either don't have this inventory or it can't be used in this room.\n");
			}
			else if (temp->name == "$10") 
			{
				Keyword* ktemp = keyword_init_default("take", "book");
				Item* itemp = item_take(&(pP->inventory), "$10");
				item_destroy(&itemp);
				(pP->i_count)--;
				printf("You have bought the book from the old homeless man.\n");
				printf("The old man slowly faded away and disappeared.\n");
				pP->current->condition = 1;
				take(pP, ktemp);
				keyword_destroy(&ktemp);
				printf("\nHINT: You should take good care of the book.\n\n");
			}
			else if (temp->name == "book") {
				if (pP->current->place == Temple && pP->current->condition == 1) {
					printf("You did exact what the book says, hoping that some kind of miracle will happen.\n");
					printf("But nothing happened. You took a punch from the top killer and got knocked out.\n");
					printf("\n//---------------------------------  TWO WEEKS LATER ---------------------------------\\\\\n\n");
					printf("You finally woke up. And surprisingly, you have completely recovered and you are now feeling like a whole new person.\n");
					printf("You saw the top killer's footprints going towards the north direction.\n");					pP->current->condition = 0;
					pP->current->north->condition = 1;
				}
				else {
					printf("You opened the book and saw demostration of how to use the godly martial art, the Buddha Palm.\n");
					printf("You did the exact same motion as the demonstration, but nothing happened.\n");
					printf("You flipped to the last page, there is a price tag marking \"$2\"\n");
				}
			}
			else if (temp->name == "paperclip") {
				if (pP->current->place == Axeland) { 
					if (pP->current->condition == 0) {
						int use[7] = { 0,0,1,0,0,0,0 };
						printf("You unlocked the handcuff right before the Axe hits you and saved your own life.\n");
						printf("Brother Sen was impressed by your lock-picking skill and asked you to free the top killer of the world at the psychiatric hospital / prison.\n");
						pP->current->condition = 1;
						pP->room_list[(int)Hospital]->items = item_init_default("map",
							"This is the map that shows you the way to room that contains the top killer in the world.",
							use, NULL);
					}
					else if (pP->current->condition == 1) {
						printf("You have already freed yourself.\n");
					}
				}
				else if (pP->current->place == Hospital) {
					if (pP->current->condition==2){
						printf("You unlocked the door, the top killer is out!\n");
						printf("The top killer escaped and ran to the temple.\n");
						pP->current->condition=3;
						pP->room_list[(int)Axeland]->condition = 2;
						pP->room_list[(int)Temple]->condition = 1;
					}
					else if (pP->current->condition == 3) {
						printf("You have already unlocked the room and let the top killer out.\n");
					}
					else {
						printf("There's way to many locks and doors in the hospital, you have no clue what to unlock.\n");
					}
				}
			}
			else if (temp->name == "map") {
				printf("You have found your way to the room that contains the top killer of the world.\n");
				pP->current->condition=2;
			}
		}
		else if (is_inventory(kw)) {
			print_inventory(pP);
		}
		else {
			printf("????????????? INVALID INPUT ????????????????\n");
		}
	}
	if (pP->success != 0) {
		printf("\n\nYou have defeated the top killer and became the strongest kungfu artist.\n");
		printf("You became the biggest fear of the Axe Gang.\n");
		printf("The peace of the town have been restored with the protection from you, the Axe Gang no longer takes control.\n");
		printf("YOU WON!!!");
	}
	keyword_destroy(&kw);
}

void scan_word(char word[30]) {
	int i = 0;
	char c;
	for (int j = 0; j < 30; j++) {
		word[j] = '\0';
	}
	c = (char) getc(stdin);
	while (!isspace(c) && i<29) {
		word[i] = c;
		c = (char)getc(stdin);
		if (c == '\n') {
			ungetc((int)c, stdin);
		}
		i++;
	}
}

void reset_string(char first[30], char second[30])
{
	for (int i = 0; i < 30; i++) {
		first[i] = '\0';
		second[i] = '\0';
	}
}

void clear_keyboard_buffer()
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}

void room_setup(Player* pP) {
	(pP->room_list)[0] = pP->current;
	int temp[7] = {1,1,1,1,1,1,1};
	(pP->room_list)[1] = room_init_default("You are in your memory.",
		item_init_default("book", "The title says \"Buddha Palm\".", 
			temp, NULL), Memory);
	for (int i = 0; i < 7; i++) {
		temp[i] = 0;
	}
	temp[(int)Hospital] = 1;
	(pP->room_list)[2] = room_init_default("You are inside a psychiatric hospital.", 
		NULL, Hospital);
	(pP->room_list)[3] = room_init_default("You are at the base of the Axe Gang, the Largest gang in Shanghai",
		NULL, Axeland);
	pP->room_list[3]->omen = 1;
	temp[(int)Hospital] = 0;
	temp[(int)Memory] = 1;
	(pP->room_list)[4] = room_init_default("You are on the street.",
		item_init_default("$10", "It's free money!!",
			temp, NULL), Pigsty);
	(pP->room_list)[4]->event = 1;
	(pP->room_list)[5] = room_init_default("You are at your secret hideout.", NULL, Hideout);
	pP->room_list[5]->omen = 1;
	(pP->room_list)[6] = room_init_default("You are inside a temple, on the wall of the temple, it says \"kevin\"", NULL, Temple);
	(pP->room_list)[6]->event = 1;
}