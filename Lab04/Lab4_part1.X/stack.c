/* 
 * File:   stack.c
 * Author: Neili Hu
 *
 * Created on January 24, 2022, 1:41 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "BOARD.h"
/*
 * 
 */
void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

//--------------------------------------------------------------------------------

int StackPush(struct Stack *stack, double value)
{
    int i = STACK_SIZE;
    if (stack->initialized != TRUE || StackIsFull(stack) == 1) {
        return STANDARD_ERROR;
    } else {
        for (i = STACK_SIZE - 1; i > 0; i--) {
            stack->stackItems[i] = stack->stackItems[i - 1];
        }
        stack->stackItems[0] = value;
        stack->currentItemIndex++;
        return SUCCESS;
    }
}

//--------------------------------------------------------------------------------

int StackPop(struct Stack *stack, double *value)
{
    int i = 0, j;
    if (stack->initialized != TRUE || StackIsEmpty(stack) == 1) {
        return STANDARD_ERROR;
    } else {
        j = stack->currentItemIndex + 1;
        *value = stack->stackItems[0];
        for (; i < j; i++) {
            stack->stackItems[i] = stack->stackItems[i + 1];
        }
        stack->stackItems[i + 1] = 0;
        stack->currentItemIndex = stack->currentItemIndex - 1;
        return SUCCESS;
    }
}

//--------------------------------------------------------------------------------

int StackIsEmpty(const struct Stack *stack)
{
    if (stack->currentItemIndex == -1 && stack->initialized == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//--------------------------------------------------------------------------------

int StackIsFull(const struct Stack *stack)
{
    if (stack->currentItemIndex == STACK_SIZE - 1 && stack->initialized == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

//--------------------------------------------------------------------------------

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized != TRUE) {
        return SIZE_ERROR;
    } else {
        return stack->currentItemIndex + 1;
    }
}