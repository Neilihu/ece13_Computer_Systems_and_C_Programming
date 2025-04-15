// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include "Leds_Lab06.h"
// User libraries
#include "Buttons.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

struct Button {
    uint8_t event;
    uint8_t check;
};
// **** Define global, module-level, or external variables here ****
struct Button butt;
uint8_t old2 = -1;
int gp1 = 1, gp2 = 1, gp3 = 1, gp4 = 1;
char light;
// **** Declare function prototypes ****

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
    printf("Welcome to CRUZID's lab6 part5 (bounce_buttons).  Compiled on %s %s.\n", __TIME__, __DATE__);

    ButtonsInit();
    LEDS_INIT();

    while (1) {
        if (butt.event == TRUE) {
            butt.event = FALSE;
            light = LEDS_GET();
            if (butt.check & 1) {// CHECK first button
                if ((gp1 = 1) && (SWITCH_STATES() & 1)) {
                    light = light ^ 3;
                    gp1++;
                } else if ((gp1 = 2) && (SWITCH_STATES() & 1)) {
                    light = light ^ 3;
                    gp1--;
                }
            } else if (butt.check & 2) {
                if ((gp1 = 1) && (!(SWITCH_STATES() & 0))) {
                    light = light ^ 3;
                    gp1++;
                } else if ((gp1 = 2) && (!(SWITCH_STATES() & 0))) {
                    light = light ^ 3;
                    gp1--;
                }
            }

            if (butt.check & 4) {// CHECK second button
                if ((gp2 = 1) && (SWITCH_STATES() & 2)) {
                    light = light ^ 12;
                    gp2++;
                } else if ((gp2 = 2) && (SWITCH_STATES() & 2)) {
                    light = light ^ 12;
                    gp2--;
                }
            } else if (butt.check & 8) {
                if ((gp2 = 1) && (!(SWITCH_STATES() & 2))) {
                    light = light ^ 12;
                    gp2++;
                } else if ((gp2 = 2) && (!(SWITCH_STATES() & 2))) {
                    light = light ^ 12;
                    gp2--;
                }
            }

            if (butt.check & 16) {// CHECK third button
                if ((gp3 = 1) && (SWITCH_STATES() & 4)) {
                    light = light ^ 48;
                    gp3++;
                } else if ((gp3 = 2) && (SWITCH_STATES() & 4)) {
                    light = light ^ 48;
                    gp3--;
                }
            } else if (butt.check & 32) {
                if ((gp3 = 1) && (!(SWITCH_STATES() & 4))) {
                    light = light ^ 48;
                    gp3++;
                } else if ((gp3 = 2) && (!(SWITCH_STATES() & 4))) {
                    light = light ^ 48;
                    gp3--;
                }
            }

            if (butt.check & 64) {// CHECK fourth button
                if ((gp4 = 1) && (SWITCH_STATES() & 8)) {
                    light = light ^ 192;
                    gp4++;
                } else if ((gp4 = 2) && (SWITCH_STATES() & 8)) {
                    light = light ^ 192;
                    gp4--;
                }
            } else if (butt.check & 128) {
                if ((gp4 = 1) && (!(SWITCH_STATES() & 8))) {
                    light = light ^ 192;
                    gp4++;
                } else if ((gp4 = 2) && (!(SWITCH_STATES() & 8))) {
                    light = light ^ 192;
                    gp4--;
                }
            }
            LEDS_SET(light);
        }
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It should check for button events and stores them in a
 * module-level variable.
 * 
 * You should not modify this function for ButtonsTest.c or bounce_buttons.c!
 */
void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/

    int new;
    new = ButtonsCheckEvents();
    
    if (new != old2) {
        butt.event = TRUE;
        butt.check = new;
        old2 = new;
    }

    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}