#include <stdio.h>
#include "BOARD.h"
#include <xc.h>
#include <sys/attribs.h>
#include "Buttons.h"
int old = -1;
static int debunc = BUTTONS_DEBOUNCE_PERIOD;

void ButtonsInit(void)
{
    TRISFbits.TRISF1 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
}

uint8_t ButtonsCheckEvents(void)
{
    int new = 0, e = 0;
    new = BUTTON_STATES();
    debunc--;
    if (debunc == 0) {
        if (old != new) {
            if ((new ^ old) & 0b0001) {
                if ((new & 0b0001) == 0) {
                    e = e + BUTTON_EVENT_1UP;
                } else if (new & 0b0001) {
                    e = e + BUTTON_EVENT_1DOWN;
                }
            }
            if ((new ^ old) & 0b0010) {
                if ((new & 0b0010) == 0) {
                    e = e + BUTTON_EVENT_2UP;
                } else if (new & 0b0010) {
                    e = e + BUTTON_EVENT_2DOWN;
                }
            }
            if ((new ^ old) & 0b0100) {
                if ((new & 0b0100) == 0) {
                    e = e + BUTTON_EVENT_3UP;
                } else if (new & 0b0100) {
                    e = e + BUTTON_EVENT_3DOWN;
                }
            }
            if ((new ^ old) & 0b1000) {
                if ((new & 0b1000) == 0) {
                    e = e + BUTTON_EVENT_4UP;
                } else if (new & 0b1000) {
                    e = e + BUTTON_EVENT_4DOWN;
                }
            }
            old = new;
        } else if (old == new) {
            e = BUTTON_EVENT_NONE;
        }
        debunc = BUTTONS_DEBOUNCE_PERIOD;
    } else {
        e = BUTTON_EVENT_NONE;
    }

    return e;
}