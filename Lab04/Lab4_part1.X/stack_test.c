// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

//define variables
double i = 0, counter = 0;
struct Stack stack2 = {};

int main()
{
    BOARD_Init();

    printf("\n###### Beginning 1752639's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
/*************************************************************************************************
 *********************************** StackInit Test **********************************************
 *************************************************************************************************/
    
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1 && stack.initialized == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
/*************************************************************************************************
 *********************************** StackPush Test **********************************************
 *************************************************************************************************/
    double counter;
    struct Stack stack2 = {};
    int i;
    printf("\nStackPush Test\n");
    counter = 0;
    StackInit(&stack2);
    for (i = 0; i < STACK_SIZE; i++) {                //change the STACK_SIZE to change total
        if (StackPush(&stack2, i) == 0) {             // input numbers also STACK_SIZE below
            printf("Stack is not initialized or is full.\n\n");
            counter++;
            break;
        }
    }
    if (counter == 0) {
        printf("Numbers in stack: ");
        for (i = 0; i < STACK_SIZE; i++) {           
            printf("%.2f, ",stack2.stackItems[STACK_SIZE - 1 - i]);   
        }
        printf("\nThe total number should be: %d\n", STACK_SIZE);
        printf("The total number I got is: %d\n\n",stack2.currentItemIndex + 1);
    }
/*************************************************************************************************
 ************************************ StackPop Test **********************************************
 *************************************************************************************************/
    struct Stack stack3 = {};
    double a;
    int c;
    
    printf("StackPop Test\n");
    //------------------->>>>>>>>>>>>>>>>> add push here if you want more number in stack
    StackInit(&stack3);
    StackPush(&stack3, 3);                           
    StackPush(&stack3, 2);
    
    
    //------------------------------------
    if (stack3.initialized != TRUE) {
        printf("The push is not initialized.\n");
        counter++;
    }
    if (counter == 0) {
        printf("Numbers in the Stack before pop: ");
        for (c = 0; c < stack3.currentItemIndex + 1; c++) {
            printf("%0.2f, ", stack3.stackItems[c]);
        }
    printf("\n");
    }
    //------------------->>>>>>>>>>>>>>>>> add pop here if you want less number in stack
    StackPop(&stack3, &a);               
    
    
    //------------------------------------
    if (stack3.initialized != TRUE) {
        printf("The pop is also not initialized.\n\n");
        counter++;
    } else {
        counter = 0;
    }
    if (counter == 0) {
        printf("Numbers in the Stack after pop: ");
        for (c = 0; c < stack3.currentItemIndex + 1; c++) {
            printf("%0.2f", stack3.stackItems[c]);
        }
        printf("\nThe number in current output holder is: %0.4f\n\n", a);
    }    

/*************************************************************************************************
 ******************************** StackIsEmpty Test/ **********************************************
 *************************************************************************************************/
    struct Stack stack4 = {};
    double b;
    
    printf("StackIsEmpty Test\n");
    //------------------->>>>>>>>>>>>>>>>> add push/pop if you want more/less number in stack
    StackInit(&stack4);
    StackPush(&stack4, 1);
    StackPop(&stack4, &b);
    
    
    //------------------------------------
    if (StackIsEmpty(&stack4) == 1) {
        printf("The stack is empty.\n\n");
    } else {
        printf("The stack is not empty or not initialized.\n\n");
    }
/*************************************************************************************************
 ******************************** StackIsFull Test/ **********************************************
 *************************************************************************************************/
    struct Stack stack5 = {};
    double w = 0;
    
    printf("StackIsFull Test\n");
    StackInit(&stack5);
    for (; w < STACK_SIZE; w++) {           //change STACK_SIZE to change total input numbers
        StackPush(&stack5, w);
    }
    if (StackIsFull(&stack5) == 1) {
        printf("The stack is full.\n\n");
    } else {
        printf("The stack is not full or not initialized.\n\n");
    }

/*************************************************************************************************
 ******************************** StackGetSize Test/ **********************************************
 *************************************************************************************************/
    struct Stack stack6 = {};
    
    printf("StackGetSize Test\n");
    //------------------->>>>>>>>>>>>>>>>> add push/pop if you want more/less number in stack
    StackInit(&stack6);
    StackPush(&stack6, 1);
    
    
    //------------------------------------
    if (StackGetSize(&stack6) == -1) {
        printf("The stack is not initialized.\n"); 
    } else {
        printf("The stack size is: %d.\n", StackGetSize(&stack6) + 1);
    }
    StackPush(&stack6, 1);
    StackPush(&stack6, 1);

/*************************************************************************************************
 ***************************************** End ***************************************************
 *************************************************************************************************/
    
    BOARD_End();
    while (1);
    return 0;
}


