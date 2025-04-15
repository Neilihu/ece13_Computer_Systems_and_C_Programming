/* 
 * Every file you submit should start with a header like this
 *
 * File:   part0.c
 * Author: Neili Hu (nehu@ucsc.edu)
 *
 * Created on January 4, 2022, 6:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"BOARD.h"

/*
 * 
 */
struct F {
  double a;
  signed short int b;
};
int main(void)
{

struct F m = {1.0, 2};
m->b = 7;
    

    BOARD_End(); // handles cleanup of the system
    while(1); // if embedded we should never exit.
}

