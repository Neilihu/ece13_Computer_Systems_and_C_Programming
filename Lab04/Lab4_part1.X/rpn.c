/* 
 * File:   rpn.c
 * Author: Neili Hu
 *
 * Created on January 24, 2022, 1:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BOARD.h"
#include "rpn.h"
#include "stack.h"

/*
 * 
 */


int RPN_Evaluate(char * rpn_string, double * result)
{
    int length, counter = 0, c = 7,e;
    char *token;
    double value, trush;
    struct Stack stack;
    

    StackInit(&stack);
    token = strtok(rpn_string, " \n");   //initialized string and cut it into token.
    
    while (token != NULL && c == 7){
        length = strlen(token);    
        if (length == 1) {          //below is for input is a character
            if ( token[0] >= '0' && token[0] <= '9') {
                if (StackIsFull(&stack)) {
                    c = RPN_ERROR_STACK_OVERFLOW;
                    counter = 2;
                    break;
                }
                StackPush(&stack, atof(token));
            } else if ( token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' ) {
                if (stack.currentItemIndex > 0){
                    if (stack.stackItems[0] == 0 && token[0] == '/'){
                        c = RPN_ERROR_DIVIDE_BY_ZERO;
                        counter = 2;
                        break;
                    } else {
                        if (StackIsFull(&stack)) {
                            c = RPN_ERROR_STACK_OVERFLOW;
                            counter = 2;
                            break;
                        }
                        StackPush(&stack, token[0]);
                    }
                } else if (stack.currentItemIndex <= 0) {
                    c = RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
                    counter = 2;
                    break;
                }
            } else {
                c = RPN_ERROR_INVALID_TOKEN;
                counter = 2;
                break;
            }
        } else {                    // below is for input contains characters
            if (strspn(token, "0123456789") == strlen(token)) {
                if (StackIsFull(&stack)) {
                    c = RPN_ERROR_STACK_OVERFLOW;
                    counter = 2;
                    break;
                }
                StackPush(&stack, atof(token)); 
            } else if (token[0] == '+' || token[0] == '-' || (token[0] >= '0' && token[0] <= '9')) {
                counter = 0;
                for ( e = 1; e < length; e++) {
                    if (token[e] == '.') {
                        counter ++;
                    } else if (token[e] >= '0' && token[e] <= '9') {                       
                    } else {
                        counter = 2;
                        c = RPN_ERROR_INVALID_TOKEN;
                        break; 
                    }
                    if (counter == 2) {
                        c = RPN_ERROR_INVALID_TOKEN;
                        break; 
                    }
                }
                if (counter <= 1) {
                    if (StackIsFull(&stack)) {
                        c = RPN_ERROR_STACK_OVERFLOW;
                        counter = 2;
                        break;
                    }
                    StackPush(&stack, atof(token));
                }
            } else if (token[0] == '.') {
                for ( e = 1; e < length; e++) {
                    if (token[e] == '.') {
                        counter = 2;
                        c = RPN_ERROR_INVALID_TOKEN;
                        break;
                    }    
                } 
                if (StackIsFull(&stack)) {
                    c = RPN_ERROR_STACK_OVERFLOW;
                    counter = 2;
                    break;
                }
                StackPush(&stack, atof(token));
            } else {
                c = RPN_ERROR_INVALID_TOKEN;
                counter = 2;
                break;
            }
            if (counter == 2) {
                break;
            }
        }
 /************************************************************************************************ 
  *********************************calculation part***********************************************
  ************************************************************************************************/      
        if (stack.currentItemIndex > 1 && (stack.stackItems[0] == '+'
                || stack.stackItems[0] == '-' || stack.stackItems[0] == '*'
                || stack.stackItems[0] == '/')) {
            if ( stack.stackItems[0] == '+') {
                value = stack.stackItems[2] + stack.stackItems[1];
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPush(&stack, value);
            } else if (stack.stackItems[0] == '-') {
                value = stack.stackItems[2] - stack.stackItems[1];
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPush(&stack, value);
            } else if (stack.stackItems[0] == '*') {
                value = stack.stackItems[2] * stack.stackItems[1];
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPush(&stack, value);
            } else if (stack.stackItems[0] == '/') {
                value = stack.stackItems[2] / stack.stackItems[1];
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPop(&stack, &trush);
                StackPush(&stack, value);
            }   
        }
        token = strtok (NULL, " \n");
    }
    
    
    if (counter == 2) {                              //ending finish
    } else if (stack.currentItemIndex > 0 && counter < 2) {
        c = RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    } else if (stack.currentItemIndex == 0 && counter < 2) {
        StackPop(&stack, result);
        c = RPN_NO_ERROR;
    } else if (stack.currentItemIndex < 0 && counter < 2){    
        c = RPN_ERROR_STACK_UNDERFLOW;
    }
    return c;
}

//---------------------------------------------
int ProcessBackspaces(char *rpn_sentence)
{
    int length, i, a;
    
    length = strlen(rpn_sentence);
    a = 0;
    
    for (i = 0; i < length - 1; i++) {
        if (rpn_sentence[i] == '\b') {
            if (a > 0) {
                rpn_sentence[a] = '\0';
                a--;
            } else if (a == 0) {
                rpn_sentence[a] = '\0';
            }
        } else {
            rpn_sentence[a] = rpn_sentence[i];
            a++;
        }
    }
    for (i = a + 1; i < length - 1; i++) {
        rpn_sentence[i] = '\0';
    }
    return a;
}
