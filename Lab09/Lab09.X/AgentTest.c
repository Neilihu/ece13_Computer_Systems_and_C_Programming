/* 
 * File:   newmain.c
 * Author: ????
 *
 * Created on March 3, 2022, 1:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include <stdint.h>
#include "BattleBoats.h"
#include "Agent.h"
#include "Field.h"
#include "Negotiation.h"


/*
 * 
 */
void main()
{
    int i = 0;
    NegotiationData a = 12345;
    NegotiationData c;
    BB_Event event2 = {BB_EVENT_START_BUTTON};
    BB_Event event9 = {BB_EVENT_CHA_RECEIVED, 43182};
    //************************AgentInit()/AgentGetState() testing*************************//
    AgentInit();
    if (AgentGetState() == AGENT_STATE_START) {
        printf("\nAgentGetState() works\n");
        i++;
    } else {
        printf("\nAgentGetState() fails\n");
    }

    //************************AgentRun() testing*************************//

    BB_Event event1 = {BB_EVENT_NO_EVENT};
    if (!(AgentRun(event1).type)) {
        printf("\nAgentRun() no event works\n");
        i++;
    } else {
        printf("\nAgentRun() no event fails\n");
    }
    
    //---------------------------------------------------------------------------------

    AgentInit(); //start button-ACC received-heads-message sent
    Message event2_1 = AgentRun(event2);
    if ((event2_1.type == MESSAGE_CHA)&&(AgentGetState() == AGENT_STATE_CHALLENGING)) {
        printf("\nAgentRun() start button works\n");
        i++;
    } else {
        printf("\nAgentRun() start button fails\n");
    }
        //--------------------
    c = event2_1.param0;
    BB_Event event3 = {BB_EVENT_ACC_RECEIVED, 12345};
    if (NegotiateCoinFlip(c, a) != HEADS) {
        event3.param0 = 12344;
    }
        //set a number for event3 from event2_1 that must be head
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ((AgentRun(event3).type == MESSAGE_REV)&&(AgentGetState() == AGENT_STATE_WAITING_TO_SEND)) {
        printf("\nAgentRun() ACC received and in head situation works\n");
        i++;
    } else {
        printf("\nAgentRun() ACC received and in head situation fails\n");
    }

    BB_Event event4 = {BB_EVENT_MESSAGE_SENT};
    if ((AgentRun(event4).type == MESSAGE_SHO)&&(AgentGetState() == AGENT_STATE_ATTACKING)) {
        printf("\nAgentRun() MESSAGE SENT works\n");
        i++;
    } else {
        printf("\nAgentRun() MESSAGE SENT fails\n");
    }
    
    //---------------------------------------------------------------------------------    
    AgentInit(); //start button-ACC received-tails-SHO received-not defeat
    AgentRun(event2);
    Message event2_2 = AgentRun(event2);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //set a number for event5 from event2_2 that must be tail
    c = event2_2.param0;
    BB_Event event5 = {BB_EVENT_ACC_RECEIVED, 12345};
    if (NegotiateCoinFlip(c, a) != TAILS) {
        event5.param0 = 12344;
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   
    if ((AgentRun(event5).type == MESSAGE_REV)&&(AgentGetState() == AGENT_STATE_DEFENDING)) {
        printf("\nAgentRun() ACC received and in tail situation works\n");
        i++;
    } else {
        printf("\nAgentRun() ACC received and in tail situation fails\n");
    }
    BB_Event event6 = {BB_EVENT_SHO_RECEIVED, 0, 0};
    if ((AgentRun(event6).type == MESSAGE_RES)&&(AgentGetState() == AGENT_STATE_WAITING_TO_SEND)) {
        printf("\nAgentRun() SHO received and not defeat situation works\n");
        i++;
    } else {
        printf("\nAgentRun() SHO received and not defeat situation fails\n");
    }
    
    //---------------------------------------------------------------------------------
    AgentInit(); //start button-ACC received-tails-SHO received-defeat
    int k = 0, j = 0,l=0;
    Message try;
    AgentRun(event2);
        
    Message event2_3 = AgentRun(event2);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //set a number for event7 from event2_3 that must be tail
    c = event2_3.param0;
    BB_Event event7 = {BB_EVENT_ACC_RECEIVED, 12345};
    if (NegotiateCoinFlip(c, a) != TAILS) {
        event7.param0 = 12344;
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    AgentRun(event7);
    BB_Event event8 = {BB_EVENT_SHO_RECEIVED, 0, 0};
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for (k=0; k < FIELD_ROWS; k++) {
        for (j=0; j < FIELD_COLS; j++) {
            event8.param0 = k;
            event8.param1 = j;
            try=AgentRun(event8);
            if (AgentGetState() == AGENT_STATE_END_SCREEN) {
                i++;
            break;
            }
            AgentSetState(AGENT_STATE_DEFENDING);
        }
        if (AgentGetState() == AGENT_STATE_END_SCREEN) {
            break;
        }
    }
    if (AgentGetState() != AGENT_STATE_END_SCREEN) {
        printf("\nAgentRun() SHO received and defeat situation fails\n");
    } else if (AgentGetState() == AGENT_STATE_END_SCREEN){
        printf("\nAgentRun() SHO received and defeat situation works\n");
        i++;
    }
    
    //---------------------------------------------------------------------------------    
    AgentInit(); //CHA received-REV received-tails-RES received-not victory
    Message event9_1 = AgentRun(event9);
    if ((event9_1.type == MESSAGE_ACC)&&(AgentGetState() == AGENT_STATE_ACCEPTING)) {
        printf("\nAgentRun() CHA received works\n");
        i++;
    } else {
        printf("\nAgentRun() CHA received fails\n");
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //set a number for event10 from event9_1 that must be tail
    c = event9_1.param0;
    BB_Event event10 = {BB_EVENT_REV_RECEIVED, 12345};
    while (NegotiateCoinFlip(c, a) != TAILS){
        AgentSetState(AGENT_STATE_START);
        Message event9_1 = AgentRun(event9);
        c = event9_1.param0;
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Message event10_1 = AgentRun(event10);
    if ((event10_1.type == MESSAGE_SHO)&&(AgentGetState() == AGENT_STATE_ATTACKING)) {
        printf("\nAgentRun() REV received tails situation works\n");
        i++;
    } else {
        printf("\nAgentRun() REV received tails situation fails\n");
    }
    BB_Event event11 = {BB_EVENT_RES_RECEIVED, event10_1.param0, event10_1.param1, RESULT_MISS};
    if ((!(AgentRun(event11).type))&&(AgentGetState() == AGENT_STATE_DEFENDING)) {
        printf("\nAgentRun() RES received and not victory works\n");
        i++;
    } else {
        printf("\nAgentRun() RES received and not victory fails\n");
    }
    
    //--------------------------------------------------------------------------------- 
    AgentInit(); //CHA received-REV received-tails-RES received-victory
    Message event9_2 = AgentRun(event9);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //set a number for event10_2 from event9_4 that must be tail
    c = event9_2.param0;
    BB_Event event10_2 = {BB_EVENT_REV_RECEIVED, 12345};
    while (NegotiateCoinFlip(c, a) != TAILS){
        AgentSetState(AGENT_STATE_START);
        Message event9_2 = AgentRun(event9);
        c = event9_2.param0;
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    AgentRun(event10_2);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    BB_Event event10_3 = {BB_EVENT_RES_RECEIVED, 1, 1, RESULT_SMALL_BOAT_SUNK};
    BB_Event event10_4 = {BB_EVENT_RES_RECEIVED, 2, 1, RESULT_MEDIUM_BOAT_SUNK};
    BB_Event event10_5 = {BB_EVENT_RES_RECEIVED, 2, 2, RESULT_LARGE_BOAT_SUNK};
    BB_Event event10_6 = {BB_EVENT_RES_RECEIVED, 2, 3, RESULT_HUGE_BOAT_SUNK};
    AgentRun(event10_3);
    AgentSetState(AGENT_STATE_ATTACKING);
    AgentRun(event10_4);
    AgentSetState(AGENT_STATE_ATTACKING);
    AgentRun(event10_5);
    AgentSetState(AGENT_STATE_ATTACKING);
        //sink every boats
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ((!(AgentRun(event10_6).type))&&(AgentGetState() == AGENT_STATE_END_SCREEN)) {
        printf("\nAgentRun() RES received and victory fails\n");
        i++;
    } else {
        printf("\nAgentRun() RES received and victory works\n");
    }

    //---------------------------------------------------------------------------------    
    AgentInit(); //CHA received-REV received-heads
    Message event9_3 = AgentRun(event9);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //set a number for event12 from event9_2 that must be HEADS
    c = event9_3.param0;
    BB_Event event12 = {BB_EVENT_REV_RECEIVED, 12345};
    while (NegotiateCoinFlip(c, a) != HEADS){
        AgentSetState(AGENT_STATE_START);
        Message event9_3 = AgentRun(event9);
        c = event9_3.param0;
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ((!(AgentRun(event12).type))&&(AgentGetState() == AGENT_STATE_DEFENDING)) {
        printf("\nAgentRun() REV received heads situation works\n");
        i++;
    } else {
        printf("\nAgentRun() REV received heads situation fails\n");
    } 
    //---------------------------------------------------------------------------------    
    AgentInit(); //CHA received-REV received-cheat
    AgentRun(event9);
    BB_Event event13 = {BB_EVENT_REV_RECEIVED, 12233};
    if ((!(AgentRun(event13).type))&&(AgentGetState() == AGENT_STATE_END_SCREEN)) {
        printf("\nAgentRun() REV received cheating situation works\n");
        i++;
    } else {
        printf("\nAgentRun() REV received cheating situation fails\n");
    }

    if (i == 14) {
        printf("\nyou pass all tests!!!!\n");
    } else {
        printf("\nyou failed at least one test\n");
    }
    printf("-------------------------end of test------------------------------\n");

}

