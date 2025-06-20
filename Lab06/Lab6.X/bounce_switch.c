
// **** Include libraries here ****
// old bounce
#include "Leds_Lab06.h"
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
// **** Define global, module-level, or external variables here ****
static struct Timer Time1;
#define LEFT LEDS_GET() << 1
#define RIGHT LEDS_GET() >> 1
// **** Declare function prototypes ****
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void);

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to 1752639's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);
    Time1.timeRemaining = SWITCH_STATES() + 1;
    Time1.event = FALSE;
    LEDS_INIT();
    int state = 0;
    while (1) {
        if (Time1.event == TRUE) {
            Time1.event = FALSE;
            state++;
            if (state == 1) {
                LEDS_SET(0x01);
            } else if (state < 9) {
                LEDS_SET(LEFT);
            } else if (state == 9) {
                LEDS_SET(0x40);
            } else if (state < 16) {
                LEDS_SET(RIGHT);
                if (state == 15) {
                    state = 1;
                }
            }
        }
    }
    Time1.event = FALSE;

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    Time1.timeRemaining--;

    if (Time1.timeRemaining == FALSE) {
        Time1.event = TRUE;
        Time1.timeRemaining = SWITCH_STATES() + 1;
    }
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}