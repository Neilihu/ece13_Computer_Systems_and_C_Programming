all: rpg

rpg: Player.o Game.o Lab08_main.c
	gcc -Wall Player.o Game.o Lab08_main.c -o rpg
Player.o: Player.c
	gcc -Wall -c Player.c
Game.o: Game.c
	gcc -Wall -c Game.c
clean:
	rm *.o rpg