// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Buttons.h"
#include "Adc.h"
#include "Ascii.h"


// **** Set any macros or preprocessor directives here ****

// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)


// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING, TWINKLE
} OvenState;

typedef enum {
    Baketim, Baketem, Toast, Broil
} OvenMode;

typedef struct {
    OvenState state; // four
    //add more members to this struct
    OvenMode mode;
    char *modestring;
    uint16_t time;
    uint16_t temperature;
    uint16_t cooking_time_left;
    uint32_t button_recording_time;
} OvenData;
// **** Declare any datatypes here ****

static struct Event {
    uint8_t butt_event;
    uint8_t butt_check;
    uint8_t adc_event;
    int16_t adc_voltage;
    int32_t worldtime;
    uint8_t tick;
} event;

// **** Define any module-level, global, or external variables here ****
#define long_press 5
OvenData oven = {SETUP, Baketim, "Bake"};
static int cooktime = 0;
static char time[40], buffer[255];
// **** Put any helper functions here ****

char * timeconvert(OvenData ovenData)
{
    int time2 = 0, cook = 0;
    
    time2 = ovenData.time / 60;
    cook = ovenData.cooking_time_left / 60;
    
    if ((ovenData.state == SETUP) || (ovenData.state == SELECTOR_CHANGE_PENDING)) {
        sprintf(time, "%d:%d", time2, ovenData.time - (time2 * 60));
    } else {
        sprintf(time, "%d:%d", cook, ovenData.cooking_time_left - (cook * 60));
    }
    
    return time;
}

void LEDUsing(void)
{
    int i = 0, led = 255;
    
    i = (oven.time - oven.cooking_time_left) * 8 / oven.time ;
    if (oven.cooking_time_left == 0){
        LEDS_SET(0);
    } else {
        LEDS_SET(led << i);
    }
}

/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData)
{
    //update OLED here
    int exist = 0, i = 6;
    if ((ovenData.state == SETUP) || (ovenData.state == SELECTOR_CHANGE_PENDING)) {
        exist = sprintf(buffer + exist, "|");
        for (; i > 0; i--) {
            exist += sprintf(buffer + exist, "%s", OVEN_TOP_OFF);
        }
        exist += sprintf(buffer + exist, "|  Mode: %s\n|      |", ovenData.modestring);
        switch (ovenData.mode) {
        case Baketim:
            exist += sprintf(buffer + exist, " >Time:  %s\n|------|  Temp: %d%sF\n"
                    , timeconvert(ovenData), ovenData.temperature, DEGREE_SYMBOL);
            break;
        case Baketem:
            exist += sprintf(buffer + exist, "  Time:  %s\n|------| >Temp: %d%sF\n"
                    , timeconvert(ovenData), ovenData.temperature, DEGREE_SYMBOL);
            break;
        case Toast:
            exist += sprintf(buffer + exist, "  Time:  %s\n|------|\n", timeconvert(ovenData));
            break;
        case Broil:
            exist += sprintf(buffer + exist, "  Time:  %s\n|------|  Temp: 500%sF\n"
                    , timeconvert(ovenData), DEGREE_SYMBOL);
        }
        i = 6;
        exist += sprintf(buffer + exist, "|");
        for (; i > 0; i--) {
            exist += sprintf(buffer + exist, "%s", OVEN_BOTTOM_OFF);
        }
        exist += sprintf(buffer + exist, "|");
    } else {
        exist = sprintf(buffer + exist, "|");
        for (; i > 0; i--) {
            exist += sprintf(buffer + exist, "%s", OVEN_TOP_ON);
        }
        exist += sprintf(buffer + exist, "|  Mode: %s\n|      |  Time:  %s\n|------| "
                    , ovenData.modestring, timeconvert(ovenData));
        switch (ovenData.mode) {
        case Toast:
            exist += sprintf(buffer + exist, "\n");
            break;
        case Broil:
            exist += sprintf(buffer + exist, " Temp: 500%sF\n", DEGREE_SYMBOL);
            break;
        default:
            exist += sprintf(buffer + exist, " Temp: %d%sF\n"
                    , ovenData.temperature, DEGREE_SYMBOL);
        }
        i = 6;
        exist += sprintf(buffer + exist, "|");
        for (; i > 0; i--) {
            exist += sprintf(buffer + exist, "%s", OVEN_BOTTOM_ON);
        }
        exist += sprintf(buffer + exist, "|");
    }
    OledClear(0);
    OledDrawString(buffer);
    OledUpdate();
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void)
{
    //write your SM logic here.
    switch (oven.state) {
    case SETUP:
        if (event.adc_event) {
            switch (oven.mode) {
            case Baketem:
                oven.temperature = event.adc_voltage + 300;
                break;
            default:
                oven.time = event.adc_voltage + 1;
            }
            updateOvenOLED(oven);
        } else if (event.butt_event) {
            switch (event.butt_check) {
            case BUTTON_EVENT_3DOWN:
                oven.button_recording_time = event.worldtime;
                oven.state = SELECTOR_CHANGE_PENDING;
                break;
            case BUTTON_EVENT_4DOWN:
                oven.button_recording_time = event.worldtime;
                oven.state = COOKING;
                oven.cooking_time_left = oven.time;
                updateOvenOLED(oven);
                LEDUsing();
            }
        }
        break;
    case SELECTOR_CHANGE_PENDING:
        if (event.butt_check == BUTTON_EVENT_3UP) {
            if (event.worldtime - oven.button_recording_time >= long_press) {
                if (oven.mode == Baketim) {
                    oven.mode = Baketem;
                } else if (oven.mode == Baketem) {
                    oven.mode = Baketim;
                }
                oven.modestring = "Bake";
            } else {
                if (oven.mode == Baketim || oven.mode == Baketem) {
                    oven.mode = Toast;
                    oven.modestring = "Toast";
                } else if (oven.mode == Toast) {
                    oven.mode = Broil;
                    oven.modestring = "Broil";
                } else if (oven.mode == Broil) {
                    oven.mode = Baketim;
                    oven.modestring = "Bake";
                }
            }
            updateOvenOLED(oven);
            oven.state = SETUP;
        }
        break;
    case COOKING:
        if (event.tick) {
            cooktime++;
            if (cooktime == 5) {
                if (oven.cooking_time_left > 1) {
                    oven.cooking_time_left--;
                } else {
                    oven.cooking_time_left = 0;
                    oven.state = TWINKLE;
                    event.worldtime = 0;
                }
                updateOvenOLED(oven);
                LEDUsing();
                cooktime = 0;
            }
        } else if (event.butt_check == BUTTON_EVENT_4DOWN) {
            oven.button_recording_time = event.worldtime;
            oven.state = RESET_PENDING;
        }
        break;
    case RESET_PENDING:
        if (event.butt_check == BUTTON_EVENT_4UP) {
            oven.state = COOKING;
        } else if (event.tick) {
            cooktime++;
            if ((event.worldtime - oven.button_recording_time) >= long_press) {
                oven.state = SETUP;
                oven.cooking_time_left = 0;
                LEDUsing();
                updateOvenOLED(oven);
                cooktime = 0;
            } else {
                oven.state = RESET_PENDING;
                if (cooktime == 5) {
                    if (oven.cooking_time_left > 1) {
                        oven.cooking_time_left--;
                    } else {
                        oven.cooking_time_left = 0;
                        oven.state = TWINKLE;
                        event.worldtime = 0; 
                    }
                    LEDUsing();
                    updateOvenOLED(oven);
                    cooktime = 0;
                }
            }
        }
        break;
    case TWINKLE:
        cooktime++;
        if (event.butt_event) {
            oven.state = SETUP;
            OledSetDisplayNormal();
        } else if (cooktime == 1) {
            oven.state = SETUP;
            updateOvenOLED(oven);
            OledSetDisplayInverted();
            oven.state = TWINKLE;
        } else if (cooktime == 2) {
            OledSetDisplayNormal();
        } else if (cooktime == 3) {
            OledSetDisplayInverted();
            cooktime = 1;
        }
    }
}

int main()
{
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to 1752639's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    LEDS_INIT();
    OledInit();
    ButtonsInit();
    AdcInit();
    event.adc_voltage = AdcRead() >> 2;
    oven.time = event.adc_voltage + 1;
    oven.temperature = 350;
    oven.cooking_time_left = 0;
    while (1) {
        if (event.butt_event) {
            runOvenSM();
            event.butt_event = FALSE;
        } else if (event.adc_event) {
            runOvenSM();
            event.adc_event = FALSE;
        } else if (event.tick) {
            runOvenSM();
            event.tick = FALSE;
        }
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //add event-checking code here
    event.worldtime++;
    if ((oven.state != SETUP) || (oven.state != SELECTOR_CHANGE_PENDING)) {
        event.tick = TRUE;
    }
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //add event-checking code here
    int a;
    a = ButtonsCheckEvents();
    if (a != BUTTON_EVENT_NONE) {
        event.butt_event = TRUE;
        event.butt_check = a;
    } else if (AdcChanged() && (event.adc_voltage = AdcRead() >> 2 != event.adc_voltage)) {
        event.adc_event = TRUE;
        event.adc_voltage = AdcRead() >> 2;
    }
}