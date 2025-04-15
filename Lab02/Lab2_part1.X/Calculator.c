/* 
 * File:   Calculator.c
 * Author: Neili Hu (nehu@ucsc.edu)
 * ID: 1752639
 * 
 * Created on January 12, 2022, 6:57 PM
 */

// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
//add more prototypes here
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
//variables
double i,j, result;
char mp;


void CalculatorRun(void)
{
    printf("\n\nWelcome to Neili's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);

    // Your code here

    for (int k = 3; k != 2;) {                          // an infinite loop
        
        //collect mathematical operation and echo
        fflush(stdin);
        fflush(stdout);
        printf("\n\nEnter a mathematical operation to perform (*,/,+,-,v,a,c,f,t): ");
        scanf(" %c", &mp);
        printf("%c", mp);

        //see if mathematical operation is valid
        if (mp == '*'||mp == '/'||mp == '+'||mp == '-'||mp == 'v'||mp == 'a'||mp == 'c'
                                                             ||mp == 'f'||mp == 't') {
                printf("\n   Enter the first operand: ");
            if (scanf(" %lf", &i) > 0) {                  //see if input is valid for first operand
                    printf("%lf", i);   
                
                //mathematical operation is unary
                if (mp == 'a'||mp == 'c'||mp == 'f'||mp == 't') {
                    
                    if (mp == 'a') {                      //absolute operation
                            result = AbsoluteValue(i);
                            printf("\n   Result of |%lf|: %lf", i, result);
                    } else if (mp == 'c') {              //Fahrenheit to Celsius operation
                            result = FahrenheitToCelsius(i);
                            printf("\n   Result of (%lf deg->C): %lf", i, result);
                    } else if (mp == 'f') {              //Celsius to Fahrenheit operation
                            result = CelsiusToFahrenheit(i); 
                            printf("\n   Result of (%lf deg->F): %lf", i, result);
                    } else {                             //tangent operation
                            result = Tangent(i); 
                            printf("\n   Result of tan(%lf): %lf", i, result);
                    }
                    
                //mathematical operation is biary    
                } else if (mp == '*'||mp == '/'||mp == '+'||mp == '-'||mp == 'v') {
                        printf("\n   Enter the second operand: ");
                    
                    if (scanf(" %lf", &j) > 0) {        //see if input is valid for second operand
                            printf("%lf", j);                
                        
                        if (mp == '*') {                 //multiply operation
                                result = Multiply(i, j);
                                printf("\n   Result of (%lf * %lf): %lf", i, j, result);
                        } else if (mp == '/') {          //divide operation
                            
                                if (j == 0) {                //see if the second operand is 0
                                    printf("\n   Divide By Zero Error!");
                                    continue;
                                }
                                result = Divide(i, j);
                                printf("\n   Result of (%lf / %lf): %lf", i, j, result);
                        } else if (mp == '+') {          //add operation 
                                result = Add(i, j);
                                printf("\n   Result of (%lf + %lf): %lf", i, j, result);
                        } else if (mp == '-') {          //subtract operation
                                result = Subtract(i, j);
                                printf("\n   Result of (%lf - %lf): %lf", i, j, result);
                        } else if (mp == 'v') {          //average operation
                                result = Average(i, j);
                                printf("\n   Result of Avg(%lf and %lf): %lf", i, j, result);
                        }
                    } else {                             //for second operand error
                            printf("%lf", j);
                            printf("\n   Error, not a valid operator");
                            continue;
                    }     
                }
            } else {                                     //for first operand error
                    printf("%lf", i);
                    printf("\n   Error, not a valid operator");
                    continue;
            }
        } else {
                printf("\n   Error, not a valid operator"); //for mathematical operation error
                continue; 
        }
    }

    BOARD_End();
    while (1);
}



/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{   
    result = operand1 + operand2;
    return result;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
    result = (operand1 - operand2);
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    result = operand1 * operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
    result = operand1 / operand2;
    return result;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    if (operand < 0.0)
    {
        operand = operand * -1.0;
    }
    result = operand; 
    return result;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    operand = (operand - 32) * 5 / 9;
    return operand ;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    operand = operand * 9 / 5 + 32;
    return operand;
}
/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    result = (operand1 + operand2) / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    operand = (operand * M_PI) / 180;
    result = tan(operand);
    return result;
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/



