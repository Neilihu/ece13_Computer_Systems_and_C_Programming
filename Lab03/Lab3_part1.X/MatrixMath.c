/* 
 * File:   MatrixMath.c
 * Author: Neili Hu
 *
 * Created on January 17, 2022, 9:25 AM
 */

#include <stdio.h>
#include <stdlib.h>

// User libraries:
#include "MatrixMath.h"

//variables for using
int a,b,c;
float d;
/*
 * 
 */

//define each function below

/********************************************************************************
 * Define the print function here.
 ********************************************************************************/
void MatrixPrint(float mat[3][3])
{
    printf(" --------------------\n");
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            printf("| %.2f ", mat[a][b]);
        }
        printf("|\n --------------------\n");
    }   
}
/********************************************************************************
 * Define the equal function here.
 ********************************************************************************/
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    c = 1;
    d = 0.0;
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            d = mat1[a][b] - mat2[a][b];
            if (d < 0.0) {
                d = d * -1.0;
            }
            if (d >= 0.0001) {
                ++c;
            }
        }
    }
    if (c > 1) {
        c = 0;
    }
    return c;
}
/********************************************************************************
 * Define the add function here.
 ********************************************************************************/
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            result[a][b] = 0;
            result[a][b] = mat1[a][b] + mat2[a][b];
        }
    }    
}
/********************************************************************************
 * Define the multiply function here.
 ********************************************************************************/
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            result[a][b] = 0;
        }
    }
    for (c = 0; c < 3; c++) {
        for (a = 0; a < 3; a++) {
            for (b = 0; b < 3; b++) {
                result[a][c] = mat1[a][b] * mat2[b][c] + result[a][c];
            }
        }
    }    
}
/********************************************************************************
 * Define the scalar add function here.
 ********************************************************************************/
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            result[a][b] = 0;
            result[a][b] = mat[a][b] + x;    
        }
    }    
}
/********************************************************************************
 * Define the scalar multiply function here.
 ********************************************************************************/
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            result[a][b] = mat[a][b] * x;   
        }
    }    
}
/********************************************************************************
 * Define the trace function here.
 ********************************************************************************/
float MatrixTrace(float mat[3][3])
{
    float c = 0;
    for (a = 0; a < 3; a++) {
        c = mat[a][a] + c;
    }
    return c;
}
/********************************************************************************
 * Define the transpose function here.
 ********************************************************************************/
void MatrixTranspose(float mat[3][3], float result[3][3])
{
    float mat21[3][3] = {};      
    
    for (a = 0; a < 3; a++) {
        for (b = 0; b < 3; b++) {
            mat21[a][b] = mat[a][b];
            result[b][a] = mat21[a][b];
        }
    }    
}
/********************************************************************************
 * Define the submatrix function here.
 ********************************************************************************/
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
            result[a][b] = 0;
        }
    }
    int row[3] = {0, 0, 0};
    int column[3] = {0, 0, 0};
    if (i == 0){
        row[0] = 1;
        row[1] = 2;
        row[2] = 0;
    } else if (i == 1) {
        row[0] = 0;
        row[1] = 2;
        row[2] = 1;
    } else if (i == 2) {
        row[0] = 0;
        row[1] = 1;
        row[2] = 2;
    }
    if (j == 0){
        column[0] = 1;
        column[1] = 2;
        column[2] = 0;
    } else if (j == 1) {
        column[0] = 0;
        column[1] = 2;
        column[2] = 1;
    } else if (j == 2) {
        column[0] = 0;
        column[1] = 1;
        column[2] = 2;
    }
    
    for (a = 0; a < 2; a++) {
        for (b = 0; b < 2; b++) {
            result[a][b] = mat[row[a]][column[b]];
        }
    }
}
/********************************************************************************
 * Define the determinant function here.
 ********************************************************************************/
float MatrixDeterminant(float mat[3][3])
{
    float c = mat[0][0] * ( mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1] ) 
            - mat[0][1] * ( mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0] )
            + mat[0][2] * ( mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0] );
    return c;
}
/********************************************************************************
 * Define the determinant function here.
 ********************************************************************************/
void MatrixInverse(float mat[3][3], float result[3][3])
{
    float mat2[2][2] = {{}, {}};
    float result2[3][3] = {{}, {}, {}};
    
    for (a = 0; a < 3; a++) {               //copy mat to result2
        for (b = 0; b < 3; b++) {
            result2[a][b] = mat[a][b];
        }
    }    

    int y, z;
    for (y = 0; y < 3; y++) {
        for (z = 0; z < 3; z++) {     
            MatrixSubmatrix(y,z,result2,mat2);
            result[z][y] = mat2[0][0] * mat2[1][1] - mat2[0][1] * mat2[1][0];
        }
    }

    result[0][1] = result[0][1] * -1;
    result[1][0] = result[1][0] * -1;
    result[1][2] = result[1][2] * -1;
    result[2][1] = result[2][1] * -1;
    
    MatrixScalarMultiply(1 / MatrixDeterminant(mat), result, result);
}
