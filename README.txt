Project description
Kevin Luo
Description: 

	The project consists of items.c and items.h, which contains the item structure and its implementation, rooms.c and rooms.h, which contains the room structure and its implementation, keyword.c and keyword.h, which contains the keyword structure, player structure and their implementation, and finally adventure.c, which contains the main function and the functions that construct the game play using the stuctures provided in other files. 
	The item structure is similar to a link list, as it contains strings name and description of the item, an int array which indicates which room the item can be used, and a item pointer next. 
	The room structure contains the string that describe the room, a link list of items in the room, int's to indicate if it's an event room, if it contains omen, if it's visited, and finally, different stage of the room. A enum is used for the purpose of organizing rooms with names. Then finally, a room pointer to all directions of the current room. 
	In the keyword file, the keyword structure simply stores the first and second part of the keyword using strings. And the player structure contains a item structure that indicates the player's inventory, an int to count the number of items the player has, a room pointer to indicate the current room the player is in, a room array that keep track of each room, and an int is used to record if the player has reached the win condition. 
	The game play and story is written mostly in the adventure.c file, where rooms are set up, user inputs are taken with self-written functions instead of taking string from scanner. The story is based on a movie, and in total, there is 7 rooms which includes the 2 event rooms, 4 items, and 2 omen, with some rooms having conditions to activate different stages. Besides the keyword required in the document, key word "use" is added to make the game more interactive. At the end, all memories allocated are freed. 

video demo link: https://drive.google.com/file/d/1ZkKY8EtKldgJzyWClvivaXnLTaL60aj2/view?usp=sharing
