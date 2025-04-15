#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Field.h"
#include "FieldOled.h"
#include "BOARD.h"
#include <time.h>

#define on 1
#define off 0
static int i = 0, j = 0, change = 0, place=0,ii=0;

typedef enum {
    none = -1,
    up = 0,
    down = 1,
    left = 2,
    right = 3,
} LastHit;

static struct HIT {
    int i;
    int j;
    int search;
    int around;
    int go;
    int status;
    LastHit lastdirection;

} hit = {0, 0, off, off, off};

void FieldInit(Field *own_field, Field * opp_field)
{
    int i = 0, j = 0;
    for (; i < FIELD_ROWS; i++) {
        for (; j < FIELD_COLS; j++) {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }
        j = 0;
    }

    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    i = 0;
    j = 0;
    change = 0;
    hit.i = 0;
    hit.j = 0;
    hit.status = FieldGetBoatStates(opp_field);
    hit.search = off;
    hit.lastdirection = none;
    place=0;
}

SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if ((row >= FIELD_ROWS) || (col >= FIELD_COLS)) {
        return FIELD_SQUARE_INVALID;
    } else {
        return f->grid[row][col];
    }
}

SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    int i = -1;
    i = f->grid[row][col];
    f->grid[row][col] = p;
    return i;
}

uint8_t FieldAddBoat(Field *own_field, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    int i = 0, j = 0, k = -1, result = SUCCESS, l = 0;
    if ((row > FIELD_ROWS - 1) || (col > FIELD_COLS - 1)) {
        return STANDARD_ERROR;
    } else {
        switch (boat_type) { //give size to boat
        case FIELD_BOAT_TYPE_SMALL:
            k = FIELD_BOAT_SIZE_SMALL;
            l = FIELD_SQUARE_SMALL_BOAT;
            break;
        case FIELD_BOAT_TYPE_MEDIUM:
            k = FIELD_BOAT_SIZE_MEDIUM;
            l = FIELD_SQUARE_MEDIUM_BOAT;
            break;
        case FIELD_BOAT_TYPE_LARGE:
            k = FIELD_BOAT_SIZE_LARGE;
            l = FIELD_SQUARE_LARGE_BOAT;
            break;
        case FIELD_BOAT_TYPE_HUGE:
            k = FIELD_BOAT_SIZE_HUGE;
            l = FIELD_SQUARE_HUGE_BOAT;
        }
        if (dir == FIELD_DIR_SOUTH) {
            for (; row + i < row + k; i++) {
                if (own_field->grid[row + i][col] != FIELD_SQUARE_EMPTY) {
                    result = STANDARD_ERROR;
                    break;
                }
            }
            if (result == SUCCESS) {
                for (i=0; row + i < row + k; i++) {
                    own_field->grid[row + i][col] = l;
                }
                switch (boat_type) {
                case FIELD_BOAT_TYPE_SMALL:
                    own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                    break;
                case FIELD_BOAT_TYPE_MEDIUM:
                    own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                    break;
                case FIELD_BOAT_TYPE_LARGE:
                    own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                    break;
                case FIELD_BOAT_TYPE_HUGE:
                    own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                }
            }
        } else {
            for (; col + i < col + k; i++) {
                if (own_field->grid[row][col + i] != FIELD_SQUARE_EMPTY) {
                    result = STANDARD_ERROR;
                    break;
                }
            }
            if (result == SUCCESS) {
                i = 0;
                for (; col + i < col + k; i++) {
                    own_field->grid[row][col + i] = l;
                }
                switch (boat_type) {
                case FIELD_BOAT_TYPE_SMALL:
                    own_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
                    break;
                case FIELD_BOAT_TYPE_MEDIUM:
                    own_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
                    break;
                case FIELD_BOAT_TYPE_LARGE:
                    own_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
                    break;
                case FIELD_BOAT_TYPE_HUGE:
                    own_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
                }
            }
        }
    }
    return result;
}

SquareStatus FieldRegisterEnemyAttack(Field *own_field, GuessData *opp_guess)
{
    if (FieldGetSquareStatus(own_field, opp_guess->row, opp_guess->col) == FIELD_SQUARE_EMPTY) {
        opp_guess->result = RESULT_MISS;
        return FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_MISS);
    } else {
        switch (own_field->grid[opp_guess->row][opp_guess->col]) {
        case FIELD_SQUARE_SMALL_BOAT:
            own_field->smallBoatLives--;
            if (own_field->smallBoatLives == 0) {
                opp_guess->result = RESULT_SMALL_BOAT_SUNK;
            } else if (own_field->smallBoatLives > 0){
                opp_guess->result = RESULT_HIT;
            }
            break;
        case FIELD_SQUARE_MEDIUM_BOAT:
            own_field->mediumBoatLives--;
            if (own_field->mediumBoatLives == 0) {
                opp_guess->result = RESULT_MEDIUM_BOAT_SUNK;
            } else if (own_field->mediumBoatLives > 0){
                opp_guess->result = RESULT_HIT;
            }
            break;
        case FIELD_SQUARE_LARGE_BOAT:
            own_field->largeBoatLives--;
            if (own_field->largeBoatLives == 0) {
                opp_guess->result = RESULT_LARGE_BOAT_SUNK;
            } else if (own_field->largeBoatLives > 0){
                opp_guess->result = RESULT_HIT;
            }
            break;
        case FIELD_SQUARE_HUGE_BOAT:
            own_field->hugeBoatLives--;
            if (own_field->hugeBoatLives == 0) {
                opp_guess->result = RESULT_HUGE_BOAT_SUNK;
            } else if (own_field->hugeBoatLives > 0){
                opp_guess->result = RESULT_HIT;
            }
        }
        return FieldSetSquareStatus(own_field, opp_guess->row, opp_guess->col, FIELD_SQUARE_HIT);
    }
}

SquareStatus FieldUpdateKnowledge(Field *opp_field, const GuessData *own_guess)
{
    if (own_guess->result == RESULT_HIT) {
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);
    } else if (own_guess->result == RESULT_SMALL_BOAT_SUNK) {
        opp_field->smallBoatLives = 0;
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);
    } else if (own_guess->result == RESULT_MEDIUM_BOAT_SUNK) {
        opp_field->mediumBoatLives = 0;
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);
    } else if (own_guess->result == RESULT_LARGE_BOAT_SUNK) {
        opp_field->largeBoatLives = 0;
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);
    } else if (own_guess->result == RESULT_HUGE_BOAT_SUNK) {
        opp_field->hugeBoatLives = 0;
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_HIT);
    } else {
        return FieldSetSquareStatus(opp_field, own_guess->row, own_guess->col, FIELD_SQUARE_EMPTY);
    }
}

uint8_t FieldGetBoatStates(const Field *f)
{

    if (f->hugeBoatLives) {
        ii =ii ^ FIELD_BOAT_STATUS_HUGE ;
    }
    if (f->largeBoatLives) {
        ii =ii ^ FIELD_BOAT_STATUS_LARGE ;
    }
    if (f->mediumBoatLives) {
        ii =ii ^ FIELD_BOAT_STATUS_MEDIUM;
    }
    if (f->smallBoatLives) {
        ii =ii ^ FIELD_BOAT_STATUS_SMALL;
    }
    return ii;
}

uint8_t FieldAIPlaceAllBoats(Field *own_field)
{
    srand((unsigned int)time(0)*2);
    switch(place){
    case 0:
        FieldAddBoat(own_field, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
        FieldAddBoat(own_field, 0, 2, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
        FieldAddBoat(own_field, 1, 8, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
        FieldAddBoat(own_field, 3, 4, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
        place = rand()%4;
    case 1:
        FieldAddBoat(own_field, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
        FieldAddBoat(own_field, 0, 2, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
        FieldAddBoat(own_field, 1, 8, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
        FieldAddBoat(own_field, 3, 4, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
        place = rand()%4;
    case 2:
        FieldAddBoat(own_field, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
        FieldAddBoat(own_field, 1, 2, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
        FieldAddBoat(own_field, 1, 8, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
        FieldAddBoat(own_field, 3, 4, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
        place = rand()%4;
    case 3:
        FieldAddBoat(own_field, 0, 9, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);
        FieldAddBoat(own_field, 0, 2, FIELD_DIR_EAST, FIELD_BOAT_TYPE_LARGE);
        FieldAddBoat(own_field, 1, 1, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
        FieldAddBoat(own_field, 3, 4, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
        place = rand()%4;
    }


    if (FieldGetBoatStates(own_field) == 0b1111) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

//GuessData FieldAIDecideGuess(const Field *opp_field)
//{
//    int i = 0, j = 0;
//    GuessData my;
//    time_t t;
//
//    srand((unsigned) time(&t));
//    i = rand() % FIELD_ROWS;
//    j = rand() % FIELD_COLS;
//    while (opp_field->grid[i][j] != FIELD_SQUARE_UNKNOWN) {
//        srand((unsigned) time(&t));
//        i = rand() % FIELD_ROWS;
//        j = rand() % FIELD_COLS;
//    }
//    my.row = i;
//    my.col = j;
//    return my;
//}

GuessData FieldAIDecideGuess(const Field *opp_field)
{
    GuessData my;

    while (opp_field->grid[hit.i][hit.j] != FIELD_SQUARE_UNKNOWN) {
        if (hit.search == on) {
            i = 0;
            j = 0;
            while (opp_field->grid[i][j] != FIELD_SQUARE_UNKNOWN) {
                i++;
                j++;
                if (i = FIELD_ROWS) {
                    change++;
                    switch (change) {
                    case 1:
                        i = 0;
                        j = 3;
                        break;
                    case 2:
                        i = 3;
                        j = 0;
                        break;
                    case 3:
                        i = 0;
                        j = 6;
                    }
                } else if (j = FIELD_COLS) {
                    change++;
                    i = 0;
                    j = 9;
                }
            }
            hit.i = i;
            hit.j = j;
            hit.search = off;
        } else if (opp_field->grid[hit.i][hit.j] == FIELD_SQUARE_MISS) {
            if ((hit.around == on) && (hit.go == off)) {
                switch (hit.lastdirection) {
                case up:
                    hit.i++;
                    i = hit.i;
                    hit.lastdirection++;
                    break;
                case down:
                    hit.i--;
                    i = hit.i;
                    hit.lastdirection++;
                    break;
                case left:
                    hit.j++;
                    j = hit.j;
                    hit.lastdirection++;
                }
            } else if ((hit.around == on)&&(hit.go == on)) {
                switch(hit.lastdirection){
                case up:
                    hit.i++;
                    i =hit.i;
                    hit.go=off;
                    hit.lastdirection=none;
                    break;
                case down:
                    hit.i--;
                    i = hit.i;
                    hit.go=off;
                    hit.lastdirection=none;
                    break;
                case left:
                    hit.j++;
                    j=hit.j;
                    hit.go=off;
                    hit.lastdirection=none;
                    break;
                case right:
                    hit.j--;
                    j=hit.j;
                    hit.go=off;
                    hit.lastdirection=none;
                    break;
                }
            } else {
                hit.search = on;
            }
        } else if (opp_field->grid[hit.i][hit.j] == FIELD_SQUARE_HIT) {
            switch (hit.lastdirection) {
            case up:
                if (hit.status == FieldGetBoatStates(opp_field)) {
                    if ((hit.i - 1)>-1
                            && (opp_field->grid[hit.i - 1][hit.j] == FIELD_SQUARE_UNKNOWN)) {
                        i--;
                        hit.i--;
                        hit.status = FieldGetBoatStates(opp_field);
                        hit.go=on;
                    } else {
                        while (opp_field->grid[hit.i][hit.j] != FIELD_SQUARE_UNKNOWN) {
                            hit.i--;
                        }
                        hit.i++;
                        i = hit.i;
                        hit.lastdirection == down;
                    }
                } else {
                    hit.search = on;
                    hit.around = off;
                    hit.go=off;
                    hit.lastdirection = none;
                }
                break;
            case down:
                if (hit.status == FieldGetBoatStates(opp_field)) {
                    if ((hit.i + 1) < FIELD_ROWS
                            && (opp_field->grid[hit.i + 1][hit.j] == FIELD_SQUARE_UNKNOWN)) {
                        i++;
                        hit.i++;
                        hit.status = FieldGetBoatStates(opp_field);
                        hit.go=on;
                    } else {
                        while (opp_field->grid[hit.i][hit.j] != FIELD_SQUARE_UNKNOWN) {
                            hit.i++;
                        }
                        hit.i--;
                        i = hit.i;
                        hit.lastdirection == up;
                    }
                } else {
                    hit.search = on;
                    hit.around = off;
                    hit.go=off;
                    hit.lastdirection = none;
                }
                break;
            case right:
                if (hit.status == FieldGetBoatStates(opp_field)) {
                    if ((hit.j + 1) < FIELD_COLS
                            && (opp_field->grid[hit.i][hit.j + 1] == FIELD_SQUARE_UNKNOWN)) {
                        j++;
                        hit.j++;
                        hit.status = FieldGetBoatStates(opp_field);
                        hit.go=on;
                    } else {
                        while (opp_field->grid[hit.i][hit.j] != FIELD_SQUARE_UNKNOWN) {
                            hit.j--;
                        }
                        hit.j++;
                        j = hit.j;
                        hit.lastdirection == left;
                    }
                } else {
                    hit.search = on;
                    hit.around = off;
                    hit.go=off;
                    hit.lastdirection = none;
                }
                break;
            case left:
                if (hit.status == FieldGetBoatStates(opp_field)) {
                    if ((hit.j - 1)<-1
                            && (opp_field->grid[hit.i][hit.j - 1] == FIELD_SQUARE_UNKNOWN)) {
                        j--;
                        hit.j--;
                        hit.status = FieldGetBoatStates(opp_field);
                        hit.go=on;
                    } else {
                        while (opp_field->grid[hit.i][hit.j] != FIELD_SQUARE_UNKNOWN) {
                            hit.j++;
                        }
                        hit.j--;
                        j = hit.j;
                        hit.lastdirection == right;
                    }
                } else {
                    hit.search = on;
                    hit.around = off;
                    hit.go=off;
                    hit.lastdirection = none;
                }
                break;
            default:
                if ((hit.i - 1)>-1
                        && (opp_field->grid[hit.i - 1][hit.j] == FIELD_SQUARE_UNKNOWN)) {
                    i--;
                    hit.i--;
                    hit.status = FieldGetBoatStates(opp_field);
                    hit.lastdirection = up;
                    hit.around == on;
                } else if ((hit.i + 1) < FIELD_ROWS
                        && (opp_field->grid[hit.i + 1][hit.j] == FIELD_SQUARE_UNKNOWN)) {
                    i++;
                    hit.i++;
                    hit.status = FieldGetBoatStates(opp_field);
                    hit.lastdirection = down;
                    hit.around == on;
                } else if ((hit.j - 1)>-1
                        && (opp_field->grid[hit.i][hit.j - 1] == FIELD_SQUARE_UNKNOWN)) {
                    j--;
                    hit.j--;
                    hit.status = FieldGetBoatStates(opp_field);
                    hit.lastdirection = left;
                    hit.around == on;
                } else if ((hit.j + 1) < FIELD_COLS) {
                    j++;
                    hit.j++;
                    hit.status = FieldGetBoatStates(opp_field);
                    hit.lastdirection = right;
                    hit.around == on;
                }
            }
        }
    }
    my.row = i;
    my.col = j;
    return my;
}