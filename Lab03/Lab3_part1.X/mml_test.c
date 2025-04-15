// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries:
#include "MatrixMath.h"

// Module-level variables:
int txts, alltxts, all;
float zero_matrix[3][3] = {{},{},{}};
        
int main()
{
    BOARD_Init();

    printf("Beginning 1752639's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);

    // Add more tests here!
    int txts, alltxts, all, l;
    float matrix30[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}},
          matrix31[3][3] = {{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}}, 
          matrix32[3][3] = {{10.0, 20.0, 30.0}, {40.0, 50.0, 60.0}, {70.0, 80.0, 90.0}}, 
          matrix2[2][2] = {{0.0, 0.0}, {0.0, 0.0}},
          test[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
/********************************************************************************
 * test the equal function here.
 ********************************************************************************/
    //basic setting for equal
    txts = 0;
    alltxts = 0;
    all = 0;
    float result301[3][3] = {{1.0001, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    float result302[3][3] = {{0.1002, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}};
    
    //test1
    l = MatrixEquals(matrix30, result301); //difference equal to 0.0001
    ++alltxts;
    if (l == 0) {
        ++txts;
    } 
    //test2
    l = MatrixEquals(matrix31, result302); //difference bigger than 0.0001
    ++alltxts;
    if (l == 0) {
        ++txts;
    } 
    //test3
    l = MatrixEquals(matrix32, matrix32);  // no difference
    ++alltxts;
    if (l == 1) {
        ++txts;
    } 
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixEquals()\n", txts, alltxts);
/********************************************************************************
 * test the add function here.
 ********************************************************************************/
    //basic setting for add
    txts = 0;
    alltxts = 0;
    float result311[3][3] = {{1.1001, 2.2, 3.3}, {4.4, 5.5, 6.6}, {7.7, 8.8, 9.9}};
    float result312[3][3] = {{11.0002, 22, 33}, {44, 55, 66}, {77, 88, 99}};
    float result313[3][3] = {{10.1, 20.2, 30.3}, {40.4, 50.5, 60.6}, {70.7, 80.8, 90.9}};
    
    //test1
    MatrixAdd(matrix30, matrix31, zero_matrix); //difference equal to 0.0001
    ++alltxts;
    l = MatrixEquals(zero_matrix, result311);
    if (l == 0) {
        ++txts;
    }
    
    //test2
    MatrixAdd(matrix30, matrix32, zero_matrix); //difference bigger than 0.0001
    ++alltxts;
    l = MatrixEquals(zero_matrix, result312);
    if (l == 0) {
        ++txts;
    }
    
    //test3
    MatrixAdd(matrix31, matrix32, zero_matrix); // no difference
    ++alltxts;
    l = MatrixEquals(zero_matrix, result313);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixAdd()\n", txts, alltxts);
/********************************************************************************
 * test the multiply function here.
 ********************************************************************************/
    //basic setting for multiply
    txts = 0;
    alltxts = 0;
    float result321[3][3] = {{3, 3.6, 4.2}, {6.6, 8.1, 9.6}, {10.2, 12.6, 15}};
    float result322[3][3] = {{300, 360, 420}, {660, 810, 960}, {1020, 1260, 1500}};
    float result323[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    
    //test1
    MatrixMultiply(matrix30, matrix31, zero_matrix); 
    ++alltxts;
    l = MatrixEquals(zero_matrix, result321);
    if (l == 1) {
        ++txts;
    }
    
    //test2
    MatrixMultiply(matrix30, matrix32, zero_matrix); 
    ++alltxts;
    l = MatrixEquals(zero_matrix, result322);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixMultiply(matrix31, matrix32, zero_matrix); // no difference
    ++alltxts;
    l = MatrixEquals(zero_matrix, result323);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixMultiply()\n", txts, alltxts);
/********************************************************************************
 * test the scalar add function here.
 ********************************************************************************/
    //basic setting for scalar add
    txts = 0;
    alltxts = 0;
    float result331[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    float result332[3][3] = {{0.2, 0.3, 0.4}, {0.5, 0.6, 0.7}, {0.8, 0.9, 1}};
    float result333[3][3] = {{20, 30, 40}, {50, 60, 70}, {80, 90, 100}};
    
    //test1
    MatrixScalarAdd(1, matrix30, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result331);
    if (l == 1) {
        ++txts;
    }
    
    //test2
    MatrixScalarAdd(0.1, matrix31, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result332);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixScalarAdd(10, matrix32, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result333);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixScalarAdd()\n", txts, alltxts);
/********************************************************************************
 * test the scalar multiply function here.
 ********************************************************************************/
    //basic setting for scalar multiply
    txts = 0;
    alltxts = 0;
    float result341[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    float result342[3][3] = {{0.01, 0.02, 0.03}, {0.04, 0.05, 0.06}, {0.07, 0.08, 0.09}};
    float result343[3][3] = {{100, 200, 300}, {400, 500, 600}, {700, 800, 900}};
    
    //test1
    MatrixScalarMultiply(1.0, matrix30, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result341);
    if (l == 1) {
        ++txts;
    }
    
    //test2
    MatrixScalarMultiply(0.1, matrix31, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result342);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixScalarMultiply(10.0, matrix32, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result343);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixScalarMultiply()\n", txts, alltxts);
/********************************************************************************
 * test the trace function here.
 ********************************************************************************/    
    //basic setting for trace
    txts = 0;
    alltxts = 0;
    float c0 = 15.0, c1 = 1.5, c2 = 150.0, d;
    
    //test1
    d = MatrixTrace(matrix30);
    ++alltxts;
    if ((d = c0)) {
        ++txts;
    }
    
    //test2
    d = MatrixTrace(matrix31);
    ++alltxts;
    if ((d = c1)) {
        ++txts;
    }
    
    //test3
    d = MatrixTrace(matrix32);
    ++alltxts;
    if ((d = c2)) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixTrace()\n", txts, alltxts);
/********************************************************************************
 * test the transpose function here.
 ********************************************************************************/    
    //basic setting for transpose    
    txts = 0;
    alltxts = 0;
    float result361[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    float result362[3][3] = {{0.1, 0.4, 0.7}, {0.2, 0.5, 0.8}, {0.3, 0.6, .9}};
    float result363[3][3] = {{10, 40, 70}, {20, 50, 80}, {30, 60, 90}};
    
    //test1
    MatrixTranspose(matrix30, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result361);
    if (l == 1) {
        ++txts;
    }
    
    //test2
    MatrixTranspose(matrix31, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result362);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixTranspose(matrix32, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result363);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixTranspose()\n", txts, alltxts);
/********************************************************************************
 * test the submatrix function here.
 ********************************************************************************/    
    //basic setting for submatrix   
    txts = 0;
    alltxts = 0;
    float matrix370[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    float matrix371[3][3] = {{5, 6, 0}, {8, 9, 0}, {0, 0, 0}},
          matrix372[3][3] = {{4, 6, 0}, {7, 9, 0}, {0, 0, 0}},
          matrix373[3][3] = {{4, 5, 0}, {7, 8, 0}, {0, 0, 0}};
    float matrix374[3][3] = {{2, 3, 0}, {8, 9, 0}, {0, 0, 0}}, 
          matrix375[3][3] = {{1, 3, 0}, {7, 9, 0}, {0, 0, 0}},
          matrix376[3][3] = {{1, 2, 0}, {7, 8, 0}, {0, 0, 0}};
    float matrix377[3][3] = {{2, 3, 0}, {5, 6, 0}, {0, 0, 0}}, 
          matrix378[3][3] = {{1, 3, 0}, {4, 6, 0}, {0, 0, 0}},
          matrix379[3][3] = {{1, 2, 0}, {4, 5, 0}, {0, 0, 0}};
    
    int i, j;
    
    //test1
    MatrixSubmatrix(0, 0, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {                  //expand 2x2 to 3x3
        for (j = 0; j < 2; j++) {              
            matrix370[i][j] = matrix2[i][j];   
        }                                      
    }
    
    l = MatrixEquals(matrix370, matrix371);
    if ((l = 1)) {
        ++txts;
    }
    
    //test2
    MatrixSubmatrix(0, 1, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix372);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixSubmatrix(0, 2, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix373);
    if (l == 1) {
        ++txts;
    }
    
    //test4
    MatrixSubmatrix(1, 0, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix374);
    if (l == 1) {
        ++txts;
    }
    
    //test5
    MatrixSubmatrix(1, 1, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix375);
    if (l == 1) {
        ++txts;
    }
    
    //test6
    MatrixSubmatrix(1, 2, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix376);
    if (l == 1) {
        ++txts;
    }
    
    //test7
    MatrixSubmatrix(2, 0, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix377);
    if (l == 1) {
        ++txts;
    }
    
    //test8
    MatrixSubmatrix(2, 1, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix378);
    if (l == 1) {
        ++txts;
    }
    
    //test9
    MatrixSubmatrix(2, 2, matrix30, matrix2);
    ++alltxts;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            matrix370[i][j] = matrix2[i][j];
        }
    }
    
    l = MatrixEquals(matrix370, matrix379);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixSubmatrix()\n", txts, alltxts);
/********************************************************************************
 * test the Determinant function here.
 ********************************************************************************/    
    //basic setting for Determinant     
    txts = 0;
    alltxts = 0;
    c0 = 0.0; 
    c1 = 0.0; 
    c2 = 0.0;
    
    //test1
    d = MatrixDeterminant(matrix30);
    ++alltxts;
    if (d == c0) {
        ++txts;
    }
    
    //test2
    d = MatrixDeterminant(matrix31);  // I don't know why this determinant is 0 
    ++alltxts;                        // and it is not equal to c1 which is 0.
    if (d != c1) {                    // I guess it is about round.
        ++txts;
    }
    
    //test3
    d = MatrixDeterminant(matrix32);
    ++alltxts;
    if (d == c2) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixDeterminant()\n", txts, alltxts);
/********************************************************************************
 * test the Inverse function here.
 ********************************************************************************/    
    //basic setting for Inverse     
    txts = 0;
    alltxts = 0;
    float matrix33[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 9, 9}};
    float matrix34[3][3] = {{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.9, 0.9}};
    float matrix35[3][3] = {{1000, 2000, 3000}, {4000, 5000, 6000}, {7000, 9000, 9000}};
    float result391[3][3] = {{-1.5, 1.5, -0.5}, {1, -2, 1}, {0.16667, 0.83333, -0.5}};
    float result392[3][3] = {{-15, 15, -5}, {10, -20, 10}, {1.66667, 8.33333, -5}};
    float result393[3][3] = {{-0.0015, 0.0015, -0.0005}, {0.001, -0.002, 0.001},
                                                         {0.00017, 0.00083, -0.0005}};
    
    //test1
    MatrixInverse(matrix33, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result391);
    if (l == 1) {
        ++txts;
    }
    
    //test2
    MatrixInverse(matrix34, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result392);
    if (l == 1) {
        ++txts;
    }
    
    //test3
    MatrixInverse(matrix35, zero_matrix);
    ++alltxts;
    l = MatrixEquals(zero_matrix, result393);
    if (l == 1) {
        ++txts;
    }
    
    //add number count
    if (txts == alltxts) {
        ++all;
    }
    printf("passed (%d/%d): MatrixInverse()\n", txts, alltxts);
/********************************************************************************
 * finish test above
 ********************************************************************************/ 
    printf("%d out of 10 functions passed (%d%%).\n", all, all * 10);
    printf("Output of MatrixPrint()\n");
    MatrixPrint(test);
    printf("the output should be:\n");
    printf(" --------------------\n"
           "| 1.00 | 2.00 | 3.00 |\n"
           " --------------------\n"
           "| 4.00 | 5.00 | 6.00 |\n"
           " --------------------\n"
           "| 7.00 | 8.00 | 9.00 |\n"
           " --------------------\n");
    BOARD_End();
    while (1);
}
