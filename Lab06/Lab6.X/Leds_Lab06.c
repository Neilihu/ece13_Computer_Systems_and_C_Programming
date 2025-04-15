/* 
 * File:   Leds_Lab06.c
 * Author: Neili Hu 1752639
 *
 * Created on February 8, 2022, 9:50 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Leds_Lab06.h"
#include "BOARD.h"

/*
 * 
 */


//--------------------------------------------------------------------------------------------------

void LEDS_INIT(void)
{
    TRISE = 0x00; //1) Use the appropriate SFRs to set each LED pin to "output" mode.
    LATE = 0x00; //2) Use the appropriate SFRs to set each LED pin's output value to 0 (low voltage).
}
//--------------------------------------------------------------------------------------------------

void LEDS_SET(char newPattern)
{
    LATE = newPattern;
}
//--------------------------------------------------------------------------------------------------

char LEDS_GET(void)
{
    return LATE;
}