/*Name: Neili Hu
 *ID:1752639
 */
// **** Include libraries here ****
#include "Game.h"
#include "Player.h"
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>


//CSE013E Support Library
#include "UNIXBOARD.h"



// User libraries


// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****

int main()
{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1] = "",
            desc[GAME_MAX_ROOM_DESC_LENGTH + 1] = "",
            input1[2] = "";
    int where = 0, i = 0, word = 0, j = 0;

    /******************************** Your custom code goes below here ********************************/

    if (GameInit() == STANDARD_ERROR) {
        FATAL_ERROR();
        i = 1;
    }
    while ((i == 0)) {
        memset(title, 0, GAME_MAX_ROOM_TITLE_LENGTH);
        memset(desc, 0, GAME_MAX_ROOM_DESC_LENGTH);
        GameGetCurrentRoomTitle(title);
        GameGetCurrentRoomDescription(desc);
        printf("|*|%s\n|*|", title);
        for (; word < GAME_MAX_ROOM_DESC_LENGTH + 1; word++) {
            if (word % (GAME_MAX_ROOM_TITLE_LENGTH + 51) == 0) {
                printf("\n|*|");
            }
            printf("%c", desc[word]);
        }
        word = 0;
        printf("\n|*|\n|*|You can go to ");
        where = GameGetCurrentRoomExits();
        if (where & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("North(n) ");
        }
        if (where & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("East(e) ");
        }
        if (where & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("South(s) ");
        }
        if (where & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("West(w) ");
        }
        printf("or leave the dungeon(q)\n");
        while ((j == 0)) {
            printf("|*|Please choose one direction:");
            j = 1;
            scanf("%s", input1);
            scanf("%*[^\n]");
            scanf("%*c");
            if (input1[1] == 0) {
                switch(input1[0]){
                case 'w':
                    if (GameGoWest() == STANDARD_ERROR) {
                        printf("|*|Please choose a valid direction!!!!\n");
                        j = 0;
                    }
                    break;
                case 's':
                    if (GameGoSouth() == STANDARD_ERROR) {
                        printf("|*|Please choose a valid direction!!!!\n");
                        j = 0;
                    }
                    break;
                case 'e':
                    if (GameGoEast() == STANDARD_ERROR) {
                        printf("|*|Please choose a valid direction!!!!\n");
                        j = 0;
                    }
                    break;
                case 'n':
                    if (GameGoNorth() == STANDARD_ERROR) {
                        printf("|*|Please choose a valid direction!!!!\n");
                        j = 0;
                    }
                    break;
                case 'q':
                    i = 1;
                    break;
                default:
                    printf("|*|Please choose a valid direction!!!!\n");
                    j = 0;
                }
            } else {
                printf("|*|Please choose a valid direction!!!!\n");
                j = 0;
            }
        }
        j = 0;
        printf("|*|");
        for (; word < GAME_MAX_ROOM_TITLE_LENGTH + 51; word++) {
            printf("-");
        }
        word = 0;
        printf("\n");
    }
    exit(SUCCESS);
    /**************************************************************************************************/
}

