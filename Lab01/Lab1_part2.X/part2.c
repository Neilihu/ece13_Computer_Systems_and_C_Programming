// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"


// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    // Declare Variables
    float fahr, celsius;
    int lower, upper, step;

    // Initialize Variables
    lower = 0; // lower limit of temperature
    upper = 300; // upper limit
    step = 20; // step size
    fahr = lower;
    
    //the way I print words F and C.
    printf("%5F %5C\n");
    
    // Print out table
    while (fahr <= upper) {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    
    //set variable for K-F
    float kelv, f;
    
    //new header with one empty line
    printf("\n %5K %5F\n");
    
    //reset date
    kelv = lower;

    // Print out table
    while (kelv <= upper) {
        f = (9.0 / 5.0)*(kelv - 273.0) + 32.0;
        printf("%3.3f %5f\n", (double) kelv, (double) f);
        kelv = kelv + step;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}
