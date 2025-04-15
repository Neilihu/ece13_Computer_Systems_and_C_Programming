#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// CSE13E Libraries
#include "BOARD.h"
#include "Oled.h"

// BattleBoat Libraries
#include "Agent.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"
#include "Message.h"
#include "BattleBoats.h"
#include <time.h>
// Define Block

// TypeDef Block

typedef enum {
    lose,
    victory
} GameState;


static AgentState agentState;
static int turnCounter,f;
static char string1[50];
static char string2[50];
static char aHashStr[50];
static Message message;
static NegotiationData a, hashA, b, c, d;
static NegotiationOutcome coinFlip;
static Field ownField, oppField;
static GuessData guessOut, guessRes;
static GameState gameState;
static FieldOledTurn Turn;
static char output[200] = "";
// Function Block

NegotiationData generateHash(void);

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void AgentInit(void) {
    agentState = AGENT_STATE_START;
    turnCounter = 0;
    Turn = FIELD_OLED_TURN_NONE;
    message.type = MESSAGE_NONE;
    //coinFlip = HEADS;
    a = 0;
    b = 0;
    hashA = 0;
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */

Message AgentRun(BB_Event event) {
    //time_t t;
    //srand((unsigned) time(&t));
    //srand((unsigned int) time(0)*10);     
    switch (agentState) {
            //START
        case AGENT_STATE_START:
            if (event.type == BB_EVENT_RESET_BUTTON) {
                AgentInit();
                OledClear(0);
                OledDrawString("START");
                OledDrawString("\n\nReady for a new game?");
                OledDrawString("\n\n\nPress BTN4 to Start");
                OledUpdate();

                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
                turnCounter = 0;

                guessOut.row = 0;
                guessOut.col = 0;
                guessOut.result = 0;
                
                guessRes.row = 0;
                guessRes.col = 0;
                guessRes.result = 0;
                a = 0;
                b = 0;
                hashA = 0;
                agentState = AGENT_STATE_START;
                Turn = FIELD_OLED_TURN_NONE;

            } else if (event.type == BB_EVENT_START_BUTTON) {
                agentState = AGENT_STATE_CHALLENGING;
                srand((unsigned int) time(0)*6);
                a = rand();
                if (c == a || d == a) {
                    a = rand();
                }
                d = c;
                c = a;
                //printf("a is %d\n", a);
                hashA = NegotiationHash(a);
                //cha
                message.type = MESSAGE_CHA;
                message.param0 = hashA;
                message.param1 = 0;
                message.param2 = 0;
                //coinFlip = NegotiateCoinFlip(a,b);

                // Field on
                FieldInit(&ownField, &oppField);
                // place boat
                FieldAIPlaceAllBoats(&ownField);

                OledClear(0);
                sprintf(output, "Challenging!\nhash_a:%d\nA:%d", hashA, a);
                OledDrawString(output);
                OledUpdate();
            } else if (event.type == BB_EVENT_CHA_RECEIVED) {
                //b
                //b = rand();               
                srand((unsigned int) time(0)*2);
                b = rand();
                if (c == b || d == b) {
                    b = rand();
                }
                d = c;
                c = b;
                message.param0 = b;
                message.param1 = 0;
                message.param2 = 0;
                hashA = event.param0;
                //printf("b is %d\n", b);
                message.type = MESSAGE_ACC;
                // Initialize field
                FieldInit(&ownField, &oppField);
                FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                //Find boat

                //PLACE BOAT
                FieldAIPlaceAllBoats(&ownField);
                OledClear(0);

                sprintf(output, "ACCEPTING\n"
                        "hash_a:%d\n"
                        "B:%d", hashA, b);
                OledDrawString(output);
                OledUpdate();
                agentState = AGENT_STATE_ACCEPTING;

            } else if (event.type == BB_EVENT_ERROR) {
                OledClear(0);
                sprintf(output, "ERROR IN STATE START");
                OledDrawString(output);
                OledUpdate();
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            } else {
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            }
            break;

            //CHALLENGE
        case AGENT_STATE_CHALLENGING:
            if (event.type == BB_EVENT_RESET_BUTTON) {
                OledClear(0);
                OledDrawString("START");
                OledDrawString("\n\nReady for a new game?");
                OledDrawString("\n\n\nPress BTN4 to Start");
                OledUpdate();

                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
                turnCounter = 0;
                a = 0;
                b = 0;
                hashA = 0;
                agentState = AGENT_STATE_START;

            } else if (event.type == BB_EVENT_ACC_RECEIVED) {
                //SEND REV
                message.type = MESSAGE_REV;
                message.param0 = a;
                message.param1 = 0;
                message.param2 = 0;
                //flip
                if (NegotiateCoinFlip(a, b) == HEADS) {
                    agentState = AGENT_STATE_WAITING_TO_SEND;
                } else {
                    agentState = AGENT_STATE_DEFENDING;
                    FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);

                }
                //FieldOledDrawScreen(&ownField, &oppField, Turn, turnCounter);

            } else if (event.type == BB_EVENT_ERROR) {
                OledClear(0);
                sprintf(output, "ERROR IN STATE CHALLENGING");
                OledDrawString(output);
                OledUpdate();
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            } else {
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            }
            break;

            // ACCEPT
        case AGENT_STATE_ACCEPTING:
            if (event.type == BB_EVENT_RESET_BUTTON) {
                // if (event.type == BB_EVENT_RESET_BUTTON) {
                OledClear(0);
                OledDrawString("START");
                OledDrawString("\n\nReady for a new game?");
                OledDrawString("\n\n\nPress BTN4 to Start");
                OledUpdate();

                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
                turnCounter = 0;
                a = 0;
                b = 0;
                hashA = 0;
                agentState = AGENT_STATE_START;
                //begin

            } else if (event.type == BB_EVENT_REV_RECEIVED) {
                agentState = AGENT_STATE_END_SCREEN;
                message.type = MESSAGE_NONE;
                a = event.param0;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;

                if (NegotiationVerify(a, hashA) == TRUE) {

                    if (NegotiateCoinFlip(a, b) == HEADS) {
                        OledClear(0);
                        sprintf(output, "Heading to defense\n");
                        //printf(output, "Heading to defense\n");

                        OledDrawString(output);
                        OledUpdate();
                        agentState = AGENT_STATE_DEFENDING;
                    } else {
                        //send SHO 
                        message.type = MESSAGE_SHO;
                        guessOut = FieldAIDecideGuess(&oppField);
                        message.param0 = guessOut.row;
                        message.param1 = guessOut.col;
                        agentState = AGENT_STATE_ATTACKING;
                    }
                    FieldOledDrawScreen(&ownField, &oppField, Turn, turnCounter);
                }

            } else if (event.type == BB_EVENT_ERROR) {

                OledClear(0);
                sprintf(output, "ERROR IN STATE ACCEPTING");
                OledDrawString(output);
                OledUpdate();
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            } else {
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            }
            break;

        case AGENT_STATE_ATTACKING:
            if (event.type == BB_EVENT_RES_RECEIVED) {
                //printf("event type attacking is %U\n", event.type);
                guessRes.row = event.param0;
                guessRes.col = event.param1;
                guessRes.result = event.param2;

                //
                //message.type = MESSAGE_RES;
                message.type = MESSAGE_NONE;


                message.param0 = guessRes.row;
                message.param1 = guessRes.col;

                FieldUpdateKnowledge(&oppField, &guessRes);
                message.param2 = guessRes.result;
                //
                uint8_t boatsAlive = FieldGetBoatStates(&oppField);

                //printf("Boats remain attacking %U\n", boatsAlive);

                if (boatsAlive == 0x00) {
                    // victory
                    agentState = AGENT_STATE_END_SCREEN;
                } else {
                    agentState = AGENT_STATE_DEFENDING;
                    FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                }
            }

            if (event.type == BB_EVENT_ERROR) {
                OledClear(OLED_COLOR_BLACK);
                char errorString[100];
                sprintf(errorString, "error in attack! \n");
                OledDrawString(errorString);
                OledUpdate();
            }
            break;


        case AGENT_STATE_DEFENDING:

            if (event.type == BB_EVENT_SHO_RECEIVED) {
                //printf("event type defending is %U\n", event.type);
                guessOut.row = event.param0;
                guessOut.col = event.param1;

                message.type = MESSAGE_RES;

                message.param0 = guessOut.row;
                message.param1 = guessOut.col;

                FieldRegisterEnemyAttack(&ownField, &guessOut);
                message.param2=guessOut.result;
                
                uint8_t boatsAlive = FieldGetBoatStates(&ownField);
                //printf("Boats remain defending %U\n", boatsAlive);
                if (boatsAlive == 0x00) {
                    //all sunk
                    agentState = AGENT_STATE_END_SCREEN;
                } else {
                    agentState = AGENT_STATE_WAITING_TO_SEND;
                    FieldOledDrawScreen(&ownField, &oppField, FIELD_OLED_TURN_MINE, turnCounter);
                }
            } else if (event.type == BB_EVENT_ERROR) {
                OledClear(OLED_COLOR_BLACK);
                char errorString[100];
                sprintf(errorString, "error in defending \n");
                OledDrawString(errorString);
                OledUpdate();
            }
            break;


        case AGENT_STATE_WAITING_TO_SEND:
            if (event.type == BB_EVENT_RESET_BUTTON) {

                OledClear(0);
                OledDrawString("START");
                OledDrawString("\n\nReady for a new game?");
                OledDrawString("\n\n\nPress BTN4 to Start");
                OledUpdate();

                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
                turnCounter = 0;
                a = 0;
                b = 0;
                hashA = 0;
                agentState = AGENT_STATE_START;

            } else if (event.type == BB_EVENT_MESSAGE_SENT) {
                // Turn = FIELD_OLED_TURN_MINE;

                turnCounter++;
                message.type = MESSAGE_SHO;
                guessRes = FieldAIDecideGuess(&oppField);

                message.param0 = guessOut.row;
                message.param1 = guessOut.col;
                agentState = AGENT_STATE_ATTACKING;

                // FieldOledDrawScreen(&ownField, &oppField, Turn, turnCounter);

            } else if (event.type == BB_EVENT_ERROR) {
                OledClear(0);
                sprintf(output, "ERROR IN WAITING TO SENT");
                OledDrawString(output);
                OledUpdate();
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            } else {
                message.type = MESSAGE_NONE;
                message.param0 = 0;
                message.param1 = 0;
                message.param2 = 0;
            }
            break;

        case AGENT_STATE_END_SCREEN:
            if (gameState == victory) {
                OledDrawString("U WON");
            } else if (gameState == lose) {
                OledDrawString("U LOST");
            } else {
                OledDrawString("ERROR\n");
            }
            OledUpdate();
            break;
    }
    return message;
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void) {
    return agentState;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState) {
    agentState = newState;
}


//------------------

