/* 
 * File:   Player.c
 * Author: Neili Hu
 *
 * Created on February 24, 2022, 10:49 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "UNIXBOARD.h"

static struct Inventory {
    char item[8];
    uint8_t number;
} inventory = {"", 0};

/*
 * 
 */
int AddToInventory(uint8_t item)
{
    if (inventory.number < INVENTORY_SIZE + 1) {
        inventory.item[inventory.number] = item;
        inventory.number++;
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item)
{
    int i = 0, k = 0;
    for (; i < inventory.number + 1; i++) {
        if (inventory.item[i] == item) {
            k = SUCCESS;
        }
    }
    if (k != SUCCESS) {
        k = STANDARD_ERROR;
    }
    return k;
}