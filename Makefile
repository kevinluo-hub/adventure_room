OBJECTS = adventure.o items.o rooms.o keyword.o

p2: $(OBJECTS)
	gcc -o p2 $(OBJECTS)
adventure.o: adventure.c
	gcc -c adventure.c -o adventure.o
items.o: items.c items.h
	gcc -c items.c -o items.o
rooms.o: rooms.c rooms.h
	gcc -c rooms.c -o rooms.o
keyword.o: keyword.c keyword.h
	gcc -c keyword.c -o keyword.o
clean:
	rm p2 $(OBJECTS)
