/* 
 * File:   LinkedListTest.c
 * Author: ????
 *
 * Created on January 31, 2022, 1:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"
/*
 * 
 */
int counter1 = 0, counter2 = 0;

int main(void)
{
    printf("\n----------This is Neili Hu(1752639)'s test--------------\n");
/**************************************************************************************************
 ************************************LinkedListNew Test********************************************
 **************************************************************************************************/
    printf("Test LinkedListNew()\n");
    
    char *test1_1 = "here",
         *test1_2 = ""; 
    ListItem *a1_1, *a1_2;
    
    printf("Testing case one......");         //change the char *test and if to change test.
    a1_1 = LinkedListNew(test1_1);
    if (a1_1 != NULL && a1_1->data == test1_1 && a1_1->nextItem == NULL 
                                              && a1_1->previousItem ==NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    printf("Testing case two......");
    a1_2 = LinkedListNew(test1_2);
    if (a1_2 != NULL && a1_2->data == test1_2 && a1_2->nextItem == NULL 
                                              && a1_2->previousItem ==NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 2) {
        counter2++;
    }
    printf("******The passed number is %d/2******\n", counter1);
    counter1 = 0;
    free(a1_1);
    free(a1_2);
/**************************************************************************************************
 ********************************LinkedListCreateAfter Test****************************************
 **************************************************************************************************/
    printf("Test LinkedListCreateAfter()\n");
    char *basic = "here",
         *test2_2 = "123",
         *test2_3 = "456",
         *test2_4 = "789";
    ListItem *a2_1, *a2_2, *a2_3, *a2_4;
    
    a2_1 = LinkedListNew(basic);

    
    printf("Testing case one......");       //change the char *test and if to change test.
    a2_2 = LinkedListCreateAfter(a2_1, test2_2);
    if (a2_1->nextItem == a2_2 && a2_2->previousItem == a2_1 && a2_2->data == test2_2
                                                             && a2_2->nextItem == NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    printf("Testing case two......");
    a2_3 = LinkedListCreateAfter(a2_1, test2_3);
    if (a2_1->nextItem == a2_3 && a2_3->previousItem == a2_1 && a2_3->nextItem == a2_2 
                                                             && a2_2->previousItem == a2_3) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    printf("Testing case three......");
    a2_3 = NULL;
    a2_2->previousItem = NULL;
    a2_1->nextItem = NULL;
    a2_4 = LinkedListCreateAfter(a2_3, test2_4);
    if (a2_4->nextItem == NULL && a2_4->previousItem == NULL && a2_4->data == test2_4) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 3) {
        counter2++;
    }
    printf("******The passed number is %d/3******\n", counter1);
    counter1 = 0;
    free(a2_1);
    free(a2_2);
    free(a2_3);
    free(a2_4);
/**************************************************************************************************
 *************************************LinkedListRemove Test****************************************
 **************************************************************************************************/
    printf("Test LinkedListRemove()\n");
    char *test3_1 = "here",
         *test3_2 = "123",
         *test3_3 = "456",
         *b3_1, *b3_2, *b3_3, *b3_4;
    ListItem *a3_1, *a3_2, *a3_3, *a3_4, *a3_5, *a3_6;
    
    a3_1 = LinkedListNew(test3_1);
    a3_2 = LinkedListCreateAfter(a3_1, test3_2);
    a3_3 = LinkedListCreateAfter(a3_2, test3_3);
    
    printf("Testing case one......");              //change the char *test and if to change test.
    b3_1 = LinkedListRemove(a3_1);
    if (a3_2->previousItem == NULL && b3_1 == test3_1) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    printf("Testing case two......");
    b3_2 = LinkedListRemove(a3_3);
    if (a3_2->nextItem == NULL && b3_2 == test3_3) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a3_4 = LinkedListNew(test3_1);
    a3_5 = LinkedListCreateAfter(a3_4, test3_2);
    a3_6 = LinkedListCreateAfter(a3_5, test3_3);
    
    printf("Testing case three......");
    b3_3 = LinkedListRemove(a3_5);
    if (a3_4->nextItem == a3_6 && a3_6->previousItem == a3_4 && b3_3 == test3_2) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a3_6 = NULL;
    printf("Testing case four......");
    b3_4 = LinkedListRemove(a3_6);
    if (b3_4 == NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 4) {
        counter2++;
    }
    printf("******The passed number is %d/4******\n", counter1);
    counter1 = 0;
    free(a3_2);
    free(a3_4);
/**************************************************************************************************
 **************************************LinkedListSize Test*****************************************
 **************************************************************************************************/
    printf("Test LinkedListSize()\n");
    char *test4_1 = "here",
         *test4_2 = "123";
    int  b4_1, b4_2;
    ListItem *a4_1, *a4_2;
    
    a4_1 = LinkedListNew(test4_1);
    a4_2 = LinkedListCreateAfter(a4_1, test4_2);
    
    printf("Testing case one......");         //change the char *test and if to change test.
    b4_1 = LinkedListSize(a4_2);
    if (b4_1 == 2) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a4_2 = NULL;
            
    printf("Testing case two......");
    b4_2 = LinkedListSize(a4_2);
    if (b4_2 == 0) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 2) {
        counter2++;
    }
    printf("******The passed number is %d/2******\n", counter1);
    counter1 = 0;
    free(a4_1);
    free(a4_2);
/**************************************************************************************************
 ************************************LinkedListGetFirst Test***************************************
 **************************************************************************************************/
    printf("Test LinkedListGetFirst()\n");
    char *test5_1 = "here",
         *test5_2 = "123";
    ListItem *a5_1, *a5_2, *copy, *b5_1, *b5_2, *b5_3;
    
    a5_1 = LinkedListNew(test5_1);
    a5_2 = LinkedListCreateAfter(a5_1, test5_2);
    
    printf("Testing case one......");       //change the char *test and if to change test.
    copy = a5_2;
    b5_1 = LinkedListGetFirst(a5_2);
    if (b5_1 == a5_1 && a5_2 == copy) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a5_1 = NULL;
    a5_2->previousItem = NULL;
    copy = a5_2;
    printf("Testing case two......");       
    b5_2 = LinkedListGetFirst(a5_2);
    if (b5_2 == a5_2 && a5_2 == copy) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a5_2 = NULL;
    printf("Testing case three......"); 
    b5_3 = LinkedListGetFirst(a5_2);
    if (b5_3 == NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 3) {
        counter2++;
    }
    printf("******The passed number is %d/3******\n", counter1);
    counter1 = 0;
    free(a5_1);
    free(a5_2);
    free(copy);
/**************************************************************************************************
 ************************************LinkedListGetLast Test****************************************
 **************************************************************************************************/
    printf("Test LinkedListGetLast()\n");
    char *test6_1 = "here",
         *test6_2 = "123";
    ListItem *a6_1, *a6_2, *copy2, *b6_1, *b6_2, *b6_3;
    
    a6_1 = LinkedListNew(test6_1);
    a6_2 = LinkedListCreateAfter(a6_1, test6_2);
    
    printf("Testing case one......");          //change the char *test and if to change test.
    ;copy2 = a6_1;
    b6_1 = LinkedListGetLast(a6_1);
    if (b6_1 == a6_2 && a6_1 == copy2) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a6_2 = NULL;
    a6_1->nextItem = NULL;
    copy2 = a6_1;
    printf("Testing case two......");       
    b6_2 = LinkedListGetLast(a6_1);
    if (b6_2 == a6_1 && a6_1 == copy2) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    a6_1 = NULL;
    printf("Testing case three......"); 
    b6_3 = LinkedListGetLast(a6_1);
    if (b6_3 == NULL) {
        counter1++;
        printf("Passed\n");
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 3) {
        counter2++;
    }
    printf("******The passed number is %d/3******\n", counter1);
    counter1 = 0;
    free(a6_1);
    free(a6_2);
    free(copy);

/**************************************************************************************************
 ***********************************LinkedListSwapData Test****************************************
 **************************************************************************************************/
    printf("Test LinkedListSwapData()\n");
    char *test7_1 = "here",
         *test7_2 = "123",
         *test7_3 = "456",
         *test7_4 = NULL; 
    int  b7_1, b7_2, b7_3;
    ListItem *a7_1, *a7_2, *a7_3, *a7_4;
    
    a7_1 = LinkedListNew(test7_1);
    a7_2 = LinkedListCreateAfter(a7_1, test7_2);
    a7_3 = LinkedListCreateAfter(a7_2, test7_3);
    a7_4 = LinkedListCreateAfter(a7_3, test7_4);
    
    printf("Testing case one......");            //change the char*test and if to change test.
    b7_1 = LinkedListSwapData(a7_1,a7_3);
    if (b7_1 == SUCCESS && a7_1->data == test7_3 && a7_3->data == test7_1) {
        counter1++;
        printf("Passed\n");
        LinkedListSwapData(a7_1,a7_3);
    } else {
        printf("Failed\n");
    }
    
    printf("Testing case two......");
    b7_2 = LinkedListSwapData(a7_2,a7_4);
    if (b7_2 == SUCCESS && a7_2->data == test7_4 && a7_4->data == test7_2) {
        counter1++;
        printf("Passed\n");
        LinkedListSwapData(a7_2,a7_4);
    } else {
        printf("Failed\n");
    }
    
    a7_2 = NULL;
    printf("Testing case three......");
    b7_3 = LinkedListSwapData(a7_2,a7_4); 
    if (b7_3 == STANDARD_ERROR) {
        counter1++;
        printf("Passed\n");
        LinkedListSwapData(a7_2,a7_4);
    } else {
        printf("Failed\n");
    }
    
    if (counter1 == 3) {
        counter2++;
    }
    printf("******The passed number is %d/3******\n", counter1);
    counter1 = 0;
    free(a7_1);
    free(a7_2);
    free(a7_3);
    free(a7_4);
/**************************************************************************************************
 ************************************LinkedListPrint Test******************************************
 **************************************************************************************************/
    printf("Test LinkedListPrint()\n");
    char *test8_1 = "here",
         *test8_2 = NULL,
         *test8_3 = "123"; 
    int  b8_1, b8_2;
    ListItem *a8_1, *a8_2, *a8_3;
    
    a8_1 = LinkedListNew(test8_1);
    a8_2 = LinkedListCreateAfter(a8_1, test8_2);
    a8_3 = LinkedListCreateAfter(a8_2, test8_3);
    
    printf("Testing case one......\n\"");            //change the char*test and if to change test.
    b8_1 = LinkedListPrint(a8_2);
    printf("\"");
    if (b8_1 == SUCCESS) {
        counter1++;
        printf("......Passed\n");
    } else {
        printf("......Failed\n");
    }
    
    a8_2 = NULL;
    
    printf("Testing case two......\n\"");
    b8_2 = LinkedListPrint(a8_2);
    printf("\"");
    if (b8_2 == STANDARD_ERROR) {
        counter1++;
        printf("......Passed\n");
    } else {
        printf("......Failed\n");
    }
    
    if (counter1 == 2) {
        counter2++;
    }
    printf("******The passed number is %d/2******\n", counter1);
    printf("-------The total passed test is %d/8--------------\n", counter2);
    free(a8_1);
    free(a8_2);
    free(a8_3);
    
    return (0);
}
