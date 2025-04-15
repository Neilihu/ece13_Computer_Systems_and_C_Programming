// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "stack.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!
    int error,counter;
    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to 1752639'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("\nEnter floats and + - / * in RPN format:\n");
        for (counter = 0; counter <= MAX_INPUT_LENGTH; counter++) { 
            rpn_sentence[counter] = '\0';                    //clean rpn_sentence after use
        }
        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);     //to get rid of extra inputs
        while( getchar() != '\n');                  // but need extra "Enter" for "valid" inputs
                                                     
        if (rpn_sentence[MAX_INPUT_LENGTH] != '\n' &&          //show output
            rpn_sentence[MAX_INPUT_LENGTH] != '\0') {
            printf("you typed too much characters(including space). please try again.\n");
        } else {
            ProcessBackspaces(rpn_sentence);
            error = RPN_Evaluate(rpn_sentence, &result);
            if (error == 0) {
                printf("result = %f\n", result);
            } else if (error == 1) {
                printf("result = Error 1: you left too much number on the stack.\n");
            } else if (error == 2) {
                printf("result = Error 2: you left no number on the stack.\n");
            } else if (error == 3) {
                printf("result = Error 3: you put invalid characters in RPN.\n");
            } else if (error == 4) {
                printf("result = Error 4: your RPN is divided by zero.\n");
            } else if (error == 5) {
                printf("result = Error 5: you need more numbers to finish calculation.\n");
            } else if (error == 6) {
                printf("result = Error 6: your need more operators to finish calculation.\n");
            }
        }
    }
    while (1);
}

