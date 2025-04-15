// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>
#include <GenericTypeDefs.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"


// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
#define timea 2*38
#define timeb 3*38
#define timec 5*38

static struct Timer TimerA, TimerB, TimerC;
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
    printf("Welcome to 1752639's lab6 part1 (timers).  Compiled on %s %s.\n", __TIME__, __DATE__);
    TimerA.timeRemaining = timea;
    TimerA.event = FALSE;
    TimerB.timeRemaining = timeb;
    TimerB.event = FALSE;
    TimerC.timeRemaining = timec;
    TimerC.event = FALSE;
    LEDS_INIT();

    while (1) {
        if (TimerA.event == TRUE) {
            TimerA.event = FALSE;
            LEDS_SET((LEDS_GET() ^ 0x01));
            printf("A ");
        }
        if (TimerB.event == TRUE) {
            TimerB.event = FALSE;
            LEDS_SET((LEDS_GET() ^ 0x02));
            printf("B ");
        }
        if (TimerC.event == TRUE) {
            TimerC.event = FALSE;
            LEDS_SET((LEDS_GET() ^ 0x04));
            printf("C ");
        }
    }


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

    TimerA.timeRemaining--;
    TimerB.timeRemaining--;
    TimerC.timeRemaining--;

    if (TimerA.timeRemaining == FALSE) {
        TimerA.event = TRUE;
        TimerA.timeRemaining = timea;
    }
    if (TimerB.timeRemaining == FALSE) {
        TimerB.event = TRUE;
        TimerB.timeRemaining = timeb;
    }
    if (TimerC.timeRemaining == FALSE) {
        TimerC.event = TRUE;
        TimerC.timeRemaining = timec;
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}