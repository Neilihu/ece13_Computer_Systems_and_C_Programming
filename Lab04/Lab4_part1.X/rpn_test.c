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
#define MAX_INPUT_LENGTH 60
int error,counter,pass;
double result;

int main()
{
    BOARD_Init();

    printf("\n###### Beginning 1752639's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
 /************************************************************************************************
 ********************************RPNEvaluate Test*************************************************
 *************************************************************************************************/   
    //test for error 0 RPN_NO_ERROR
    char test0_1[] = "1 1 +",
         test0_2[] = "123";
    
    printf("Testing error 0 RPN_Evaluate with \"%s\"\n...\n", test0_1);
    pass = 0;
    counter = 0;
    
    error = RPN_Evaluate(test0_1, &result);
    counter += error;
    if (error != 0 ) {
        printf("Example1 error%d not error0\n",error);
    }
    error = RPN_Evaluate(test0_2, &result);
    counter += error;
    if (error != 0 ) {
        printf("Example2 error%d not error0\n",error);
    }
    
    if (counter == 0) {
        printf("Error0 pass\n");
        pass++;
    } else {
        printf("Error0 Fail\n");
    } 
    
 //-----------------------------------------------------------------------------------------------
    //test for error 1 RPN_ERROR_STACK_OVERFLOW
    char test1[MAX_INPUT_LENGTH]; // please update the MAX_INPUT_LENGTH to simulate user's input
    int i;
    
    for (i = 0; i < STACK_SIZE * 2 + 2; i = i + 2) {
        test1[i] = '1';
        test1[i + 1] = 32;
    }
    printf("Testing error 1 RPN_ERROR_STACK_OVERFLOW\n...\n");
    error = RPN_Evaluate(test1, &result);
    if (error == 1) {
        printf("Error1 pass\n");
        pass++;
    } else {
        printf("Error1 Fail\n");
    }
    
 //-----------------------------------------------------------------------------------------------
    //test for error 2 RPN_ERROR_STACK_UNDERFLOW
    char test2_1[] = "\0",     //you can change input here
         test2_2[0];
    
    printf("Testing error 2 RPN_ERROR_STACK_UNDERFLOW\n...\n");
    counter = 0;
    
    error = RPN_Evaluate(test2_1, &result);
    counter += error;
    if (error != 2 ) {
        printf("Example1 error%d not error2\n",error);
    }
    error = RPN_Evaluate(test2_2, &result);
    counter += error;
    if (error != 2 ) {
        printf("Example2 error%d not error2\n",error);
    }
    
    if (counter == 4) {
        printf("Error2 pass\n");
        pass++;
    } else {
        printf("Error2 Fail\n");
    }   
//-----------------------------------------------------------------------------------------------
    //test for error 3 RPN_ERROR_INVALID_TOKEN
    char test3_1[] = "1 1 \\",  //you can change input here
         test3_2[] = "1 0k  +",
         test3_3[] = "1..",
         test3_4[] = "1 1 --";

    printf("Testing error 3 RPN_ERROR_INVALID_TOKEN\n...\n");
    counter = 0;
    
    error = RPN_Evaluate(test3_1, &result);
    counter += error;
    if (error != 3 ) {
        printf("Example1 error%d not error3\n",error);
    }
    error = RPN_Evaluate(test3_2, &result);
    counter += error;
    if (error != 3 ) {
        printf("Example2 error%d not error3\n",error);
    }
    error = RPN_Evaluate(test3_3, &result);
    counter += error;
    if (error != 3 ) {
        printf("Example3 error%d not error3\n",error);
    }
    error = RPN_Evaluate(test3_4, &result);
    counter += error;
    if (error != 3 ) {
        printf("Example4 error%d not error3\n",error);
    }

    if (counter == 12) {
        printf("Error3 pass\n");
        pass++;
    } else {
        printf("Error3 Fail\n");
    }  
//-----------------------------------------------------------------------------------------------
    //test for error 4 RPN_ERROR_DIVIDE_BY_ZERO
    char test4_1[] = "1 0 /",     //you can change input here
         test4_2[] = "1 1 1 - /";
    
    printf("Testing error 4 RPN_ERROR_DIVIDE_BY_ZERO\n...\n");
    counter = 0;
    
    error = RPN_Evaluate(test4_1, &result);
    counter += error;
    if (error != 4 ) {
        printf("Example1 error%d not error4\n",error);
    }
    error = RPN_Evaluate(test4_2, &result);
    counter += error; 
    if (error != 4 ) {
        printf("Example2 error%d not error4\n",error);
    }
    
    if (counter == 8) {
        printf("Error4 pass\n");
        pass++;
    } else {
        printf("Error4 Fail\n");
    }     
//-----------------------------------------------------------------------------------------------
    //test for error 5 RPN_ERROR_TOO_FEW_ITEMS_REMAIN
    char test5_1[] = "1 /",        //you can change input here
         test5_2[] = "1 1 + *";
    
    printf("Testing error 5 RPN_ERROR_TOO_FEW_ITEMS_REMAIN\n...\n");
    counter = 0;
    
    error = RPN_Evaluate(test5_1, &result);
    counter += error;
    if (error != 5 ) {
        printf("Example1 error%d not error5\n",error);
    }
    error = RPN_Evaluate(test5_2, &result);
    counter += error;
    if (error != 5 ) {
        printf("Example2 error%d not error5\n",error);
    }
    
    if (counter == 10) {
        printf("Error5 pass\n");
        pass++;
    } else {
        printf("Error5 Fail\n");
    }  
//-----------------------------------------------------------------------------------------------
    //test for error 6 RPN_ERROR_TOO_MANY_ITEMS_REMAIN
    char test6_1[] = "1 1",          //you can change input here
         test6_2[] = "1 1 1 1 1 - - - ";
    
    printf("Testing error 6 RPN_ERROR_TOO_MANY_ITEMS_REMAIN\n...\n");
    counter = 0;
    
    error = RPN_Evaluate(test6_1, &result);
    counter += error;
    if (error != 6 ) {
        printf("Example1 error%d not error6\n",error);
    }
    error = RPN_Evaluate(test6_2, &result);
    counter += error;
    if (error != 6 ) {
        printf("Example2 error%d not error6\n",error);
    }
    
    if (counter == 12) {
        printf("Error6 pass\n");
        pass++;
    } else {
        printf("Error6 Fail\n");
    }
//-----------------------------------------------------------------------------------------------
    //Sum of RPNEvaluate
    printf("Total tests 7 / Passed tests %d\n*******************************\n", pass);
/*************************************************************************************************
 *******************************ProcessBackspaces Test********************************************
 *************************************************************************************************/
    char test_pb1[] = "123 4 5\n",     //you can change input here
         test_pb2[] = "12\b\b\b\b3\n",
         test_pb3[] = "12\b\b\b\n",
         test_pb4[] = " \n";
    
    printf("\nTesting ProcessBackspaces:\n\n");
    
    printf("original test1  :123 4 5\\n\n");
    printf("test1 should be :123 4 5\n");
    printf("new string contains %d characters.\n",ProcessBackspaces(test_pb1));
    printf("result of test1 :%s\n", test_pb1);
    
    printf("-------------------------------\n");
    
    printf("original test2  :12\\b\\b\\b\\b3\\n\n");
    printf("test2 should be :3\n");
    printf("new string contains %d characters.\n",ProcessBackspaces(test_pb2));
    printf("result of test2 :%s\n", test_pb2);
    
    printf("-------------------------------\n");
    
    printf("original test3  :12\\b\\b\\b\\n\n");
    printf("test3 should be :(NULL) \n");
    printf("new string contains %d characters.\n",ProcessBackspaces(test_pb3));
    printf("result of test3 :%s\n", test_pb3);
    
    printf("-------------------------------\n");
    
    printf("original test4  : \\n\n");
    printf("test4 should be : \n");
    printf("new string contains %d characters.\n",ProcessBackspaces(test_pb4));
    printf("result of test4 :%s\n", test_pb4);
    
    BOARD_End();
    //while (1);
}


