/* 
 * File:   Player.c
 * Author: ????
 *
 * Created on February 24, 2022, 10:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Player.h"

/*
 * 
 */

static struct Game {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north_room;
    uint8_t south_room;
    uint8_t east_room;
    uint8_t west_room;
    uint8_t current_room;
} game;

int GameGoNorth(void)
{
    FILE *file;
    char name[25] = "";
    if (game.north_room) {
        game.current_room = game.north_room;
        sprintf(name, "RoomFiles/room%d.txt", game.current_room);
        file = fopen(name, "rb");
        if (file == NULL) {
            FATAL_ERROR();
            fclose(file);
            return STANDARD_ERROR;
        } else {
            memset(game.title, 0, GAME_MAX_ROOM_TITLE_LENGTH + 1);
            memset(game.description, 0, GAME_MAX_ROOM_DESC_LENGTH + 1);
            fseek(file, 3, SEEK_SET);
            fread(game.title, fgetc(file), 1, file);
            if ((fgetc(file) != 0) && (FindInInventory(fgetc(file)) == STANDARD_ERROR)) {
                fseek(file, 3, SEEK_SET);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, 5, SEEK_CUR);
            }
            fread(game.description, fgetc(file), 1, file);
            if (fgetc(file) != 0) {
                AddToInventory(fgetc(file));
            }
            game.north_room = fgetc(file);
            game.east_room = fgetc(file);
            game.south_room = fgetc(file);
            game.west_room = fgetc(file);
            fclose(file);
            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoEast(void)
{
    FILE *file;
    char name[25] = "";
    if (game.east_room) {
        game.current_room = game.east_room;
        sprintf(name, "RoomFiles/room%d.txt", game.current_room);
        file = fopen(name, "rb");
        if (file == NULL) {
            FATAL_ERROR();
            fclose(file);
            return STANDARD_ERROR;
        } else {
            memset(game.title, 0, GAME_MAX_ROOM_TITLE_LENGTH + 1);
            memset(game.description, 0, GAME_MAX_ROOM_DESC_LENGTH + 1);
            fseek(file, 3, SEEK_SET);
            fread(game.title, fgetc(file), 1, file);
            if ((fgetc(file) != 0) && (FindInInventory(fgetc(file)) == STANDARD_ERROR)) {
                fseek(file, 3, SEEK_SET);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, 5, SEEK_CUR);
            }
            fread(game.description, fgetc(file), 1, file);
            if (fgetc(file) != 0) {
                AddToInventory(fgetc(file));
            }
            game.north_room = fgetc(file);
            game.east_room = fgetc(file);
            game.south_room = fgetc(file);
            game.west_room = fgetc(file);
            fclose(file);
            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoSouth(void)
{
    FILE *file;
    char name[25] = "";
    if (game.south_room) {
        game.current_room = game.south_room;
        sprintf(name, "RoomFiles/room%d.txt", game.current_room);
        file = fopen(name, "rb");
        if (file == NULL) {
            FATAL_ERROR();
            fclose(file);
            return STANDARD_ERROR;
        } else {
            memset(game.title, 0, GAME_MAX_ROOM_TITLE_LENGTH + 1);
            memset(game.description, 0, GAME_MAX_ROOM_DESC_LENGTH + 1);
            fseek(file, 3, SEEK_SET);
            fread(game.title, fgetc(file), 1, file);
            if ((fgetc(file) != 0) && (FindInInventory(fgetc(file)) == STANDARD_ERROR)) {
                fseek(file, 3, SEEK_SET);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, 5, SEEK_CUR);
            }
            fread(game.description, fgetc(file), 1, file);
            if (fgetc(file) != 0) {
                AddToInventory(fgetc(file));
            }
            game.north_room = fgetc(file);
            game.east_room = fgetc(file);
            game.south_room = fgetc(file);
            game.west_room = fgetc(file);
            fclose(file);
            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoWest(void)
{
    FILE *file;
    char name[25] = "";
    if (game.west_room) {
        game.current_room = game.west_room;
        sprintf(name, "RoomFiles/room%d.txt", game.current_room);
        file = fopen(name, "rb");
        if (file == NULL) {
            FATAL_ERROR();
            fclose(file);
            return STANDARD_ERROR;
        } else {
            memset(game.title, 0, GAME_MAX_ROOM_TITLE_LENGTH + 1);
            memset(game.description, 0, GAME_MAX_ROOM_DESC_LENGTH + 1);
            fseek(file, 3, SEEK_SET);
            fread(game.title, fgetc(file), 1, file);
            if ((fgetc(file) != 0) && (FindInInventory(fgetc(file)) == STANDARD_ERROR)) {
                fseek(file, 3, SEEK_SET);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, fgetc(file), SEEK_CUR);
                fseek(file, 5, SEEK_CUR);
            }
            fread(game.description, fgetc(file), 1, file);
            if (fgetc(file) != 0) {
                AddToInventory(fgetc(file));
            }
            game.north_room = fgetc(file);
            game.east_room = fgetc(file);
            game.south_room = fgetc(file);
            game.west_room = fgetc(file);
            fclose(file);
            return SUCCESS;
        }
    } else {
        return STANDARD_ERROR;
    }
}

int GameInit(void)
{
    FILE *file;
    char name[25] = "";

    game.current_room = STARTING_ROOM;
    sprintf(name, "RoomFiles/room%d.txt", game.current_room);

    file = fopen(name, "rb");
    if (file == NULL) {
        FATAL_ERROR();
        fclose(file);
        return STANDARD_ERROR;
    } else {
        fseek(file, 3, SEEK_SET);
        fread(game.title, fgetc(file), 1, file);
        if ((fgetc(file) != 0) && (FindInInventory(fgetc(file)) == STANDARD_ERROR)) {
            fseek(file, 3, SEEK_SET);
            fseek(file, fgetc(file), SEEK_CUR);
            fseek(file, fgetc(file), SEEK_CUR);
            fseek(file, fgetc(file), SEEK_CUR);
            fseek(file, fgetc(file), SEEK_CUR);
            fseek(file, 5, SEEK_CUR);
        }

        fread(game.description, fgetc(file), 1, file);
        if (fgetc(file) != 0) {
            AddToInventory(fgetc(file));
        }

        game.north_room = fgetc(file);
        game.east_room = fgetc(file);
        game.south_room = fgetc(file);
        game.west_room = fgetc(file);
        fclose(file);
        return SUCCESS;
    }
}

int GameGetCurrentRoomTitle(char *title)
{
    int j = 0, i = strlen(game.title);
    if (i != 0) {
        for (; i > j; j++) {
            title[j] = game.title[j];
        }
        title[i] = '\0';
    } else {
        title[0] = '\0';
    }
    return i;
}

int GameGetCurrentRoomDescription(char *desc)
{
    int j = 0, i = strlen(game.description);
    if (i != 0) {
        for (; i > j; j++) {
            desc[j] = game.description[j];
        }
        desc[i] = '\0';
    } else {
        desc[0] = '\0';
    }
    return i;
}

uint8_t GameGetCurrentRoomExits(void)
{
    int exit = 0;

    if (game.north_room) {
        exit = exit | GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (game.east_room) {
        exit = exit | GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (game.south_room) {
        exit = exit | GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (game.west_room) {
        exit = exit | GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return exit;
}