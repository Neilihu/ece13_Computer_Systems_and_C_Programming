// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//CSE13 Support Library
#include "BOARD.h"

//CSE13 standard libraries:
#include "BattleBoats.h"
#include "Field.h"

void main() {
    BOARD_Init();
    printf("Welcome to jlai38'S FieldTest.  Compiled on %s %s\n", __DATE__, __TIME__);

    // Test FieldInit()
    {
        printf("\nThis is FieldInit test\n");

        int pass = 0;
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);

        //Test 1  check if boatLives equals to zero initially
        if (!(ownField.smallBoatLives && ownField.mediumBoatLives && ownField.largeBoatLives && ownField.hugeBoatLives)) {
            printf("FieldInit Test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldInit Test 1 FAILED\n");
        }



        //Test 2 FieldInit()
        //Check if the lives of the opponents fields boats is full
        if (oppField.smallBoatLives && oppField.mediumBoatLives && oppField.largeBoatLives && oppField.hugeBoatLives) {
            printf("FieldInit Test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldInit Test 2 FAILED\n");
        }

        // Test 3
        // check grid is empty
        if ((ownField.grid[0][0] && ownField.grid[5][9] && ownField.grid[3][3]) == FIELD_SQUARE_EMPTY) {
            printf("FieldInit Test 3 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldInit Test 3 FAILED\n");
        }


        printf("%d/3 FieldInit Tests PASSED.\n", pass);
    }

    //End of FieldInit Test *******

    //Testing FieldGetSqaureStatus
    {
        printf("\nThis is FieldGetSquareStatus test \n");
        int pass = 0;
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);

        ownField.grid[0][0] = FIELD_SQUARE_SMALL_BOAT;
        oppField.grid[0][0] = FIELD_SQUARE_MISS;

        //Test 1
        //Check if the small boat exists on grid
        if (FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_SMALL_BOAT) {
            printf("FieldGetSquareStatus test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldGetSquareStatus test 1 FAILED\n");
        }

        //Test 2
        // Check if row and col are not valid field locations
        if (FieldGetSquareStatus(&ownField, 10, 10) == FIELD_SQUARE_INVALID) {
            printf("FieldGetSquareStatus test 2 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldGetSquareStatus test 2 FAILED\n");
        }

        //Test 3
        //Check if the shot miss
        if (FieldGetSquareStatus(&oppField, 0, 0) == FIELD_SQUARE_MISS) {
            printf("FieldGetSquareStatus test 3 PASSED\n");
            pass++;
        } else {
            printf("FieldGetSquareStatus test 3 FAILED\n");
        }

        //Test 4 
        //Check for error
        if (FieldGetSquareStatus(&ownField, 10, 10) == FIELD_SQUARE_INVALID) {
            printf("FieldGetSquareStatus test 4 PASSED\n");
            pass++;
        } else {
            printf("FieldGetSquareStatus test 4 FAILED\n");
        }

        printf("%d/4, FieldGetSquareStatus tests PASSED.\n", pass);
    }

    // End of FieldGetSquareStatus Test

    // Test for FieldSetSquareStatus
    {
        printf("\nThis is FieldSetSquareStatus test\n");
        int pass = 0;
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);

        ownField.grid[0][0] = FIELD_SQUARE_SMALL_BOAT;
        oppField.grid[0][0] = FIELD_SQUARE_MISS;

        //Test 1
        //
        if (FieldSetSquareStatus(&ownField, 0, 0, FIELD_SQUARE_LARGE_BOAT) == FIELD_SQUARE_SMALL_BOAT) {
            printf("FieldSetSquareStatus test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldSetSquareStatus 1 FAILED\n");
        }

        //Test 2
        // Making sure that they square changed
        if (ownField.grid[0][0] == FIELD_SQUARE_LARGE_BOAT) {
            printf("FieldSetSquareStatus test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldSetSquareStatus test 2 FAILED\n");
        }

        //Test 3
        if (FieldSetSquareStatus(&oppField, 0, 0, FIELD_SQUARE_HIT) == FIELD_SQUARE_MISS) {
            printf("FieldSetSquareStatus test 3 PASSED \n");
            pass++;
        } else {
            printf("FieldSetSquareStatus test 3 FAILED\n");
        }

        //Test 4
        if (oppField.grid[0][0] == FIELD_SQUARE_HIT) {
            printf("FieldSetSquareStatus test 4 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldSetSquareStatus test 4 FAILED\n");
        }

        printf("%d/4, FieldSetSquareStatus tests PASSED.\n", pass);
    }

    //End of FieldSetSquareStatus test ******

    // FieldRegisterEnemyAttack Test
    {
        printf("\nThis is FieldRegisterEnemyAttack test\n");
        int pass = 0;
        GuessData attack = {0, 0}; // Sets the row, column being attacked to [0][0]
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);
        FieldAddBoat(&ownField, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL);
        FieldAddBoat(&oppField, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE);

        //Test 1
        if (FieldRegisterEnemyAttack(&ownField, &attack) == FIELD_SQUARE_SMALL_BOAT && attack.result == RESULT_HIT) {
            printf("FieldRegisterEnemyAttack test 1 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldRegisterEnemyAttack test 1 FAILED\n");
        }

        //Test 2
        if (FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_HIT) {
            printf("FieldRegisterEnemyAttack test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldRegisterEnemyAttack test 2 FAILED\n");
        }

        // Testing to see that we sink a boat
        attack.col = 1;
        FieldRegisterEnemyAttack(&ownField, &attack);
        attack.col = 2;

        //Test 3
        if (FieldRegisterEnemyAttack(&ownField, &attack) == FIELD_SQUARE_SMALL_BOAT && attack.result == RESULT_SMALL_BOAT_SUNK) {
            printf("FieldRegisterEnemyAttack test 3 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldRegisterEnemyAttack test 3 FAILED\n");
        }

        //Test 4
        if (FieldGetSquareStatus(&ownField, 0, 0) == FIELD_SQUARE_HIT
                && FieldGetSquareStatus(&ownField, 0, 1) == FIELD_SQUARE_HIT
                && FieldGetSquareStatus(&ownField, 0, 2) == FIELD_SQUARE_HIT) {
            printf("FieldRegisterEnemyAttack test 4 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldRegisterEnemyAttack test 4 FAILED\n");
        }

        printf("%d/4, FieldRegisterEnemyAttack tests PASSED.\n", pass);
    }

    //End of FieldRegisterEnemyAttack test


    //Test FieldAddBoat
    {
        printf("\nThis is FieldAddBoat Test\n");
        int pass = 0;
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);

        //Test 1
        if (FieldAddBoat(&ownField, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_SMALL) == SUCCESS) {
            printf("FieldAddBoat test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldAddBoat test 1 FAILED\n");
        }

        //Test 2
        if (FieldAddBoat(&oppField, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE) == STANDARD_ERROR) {
            printf("FieldAddBoat test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldAddBoat test 2 FAILED\n");
        }

        //Test 3
        if ((FieldAddBoat(&ownField, 1, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE) == SUCCESS)) {
            printf("FieldAddBoat test 3 PASSED\n");
            pass++;
        } else {
            printf("FieldAddBoat test 3 FAILED\n");
        }

        //Test 4
        if (FieldAddBoat(&oppField, 1, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_MEDIUM) == STANDARD_ERROR) {
            printf("FieldAddBoat test 4 PASSED\n");
            pass = pass + 1;
        } else {
            printf("FieldAddBoat test 4 FAILED\n");
        }
        printf("%d/4, FieldAddBoat tests PASSED.\n", pass);
    }


    //Test the FieldUpdateKnowledge
    printf("\nThis is FieldUpdateKnowledge test\n");
    int pass = 0;
    GuessData attack = {0, 0, RESULT_HIT};
    Field ownField, oppField;
    FieldInit(&ownField, &oppField);

    //test 1 
    if (FieldUpdateKnowledge(&oppField, &attack) == FIELD_SQUARE_UNKNOWN && oppField.grid[0][0] == FIELD_SQUARE_HIT) {
        printf("FieldUpdateKnowledge test 1 PASSED\n");
        pass++;
    } else {
        printf("FieldUpdateKnowledge test 1 FAILED\n");
    }

    attack.col = 1;

    //test 2
    if (FieldUpdateKnowledge(&oppField, &attack) == FIELD_SQUARE_UNKNOWN && oppField.grid[0][1] == FIELD_SQUARE_HIT) {
        printf("FieldUpdateKnowledge test 2 PASSED\n");
        pass++;
    } else {
        printf("FieldUpdateKnowledge test 2 FAILED\n");
    }


    //test 3
    // Makes sure that once a boat has sunk that the lives of that boat type are zero
    attack.col = 2;
    attack.result = RESULT_SMALL_BOAT_SUNK;
    if (FieldUpdateKnowledge(&oppField, &attack) == FIELD_SQUARE_UNKNOWN
            && oppField.grid[0][2] == FIELD_SQUARE_HIT
            && oppField.smallBoatLives == 0) {
        printf("FieldUpdateKnowledge test 3 PASSED\n");
        pass++;
    } else {
        printf("FieldUpdateKnowledge test 3 FAILED\n");
    }

    printf("%d/3, FieldUpdateKnowledge tests PASSED\n", pass);

    // End of FieldUpdateKnowledge test

    //begin FieldGetBoatStates test
    {

        printf("\nThis is FieldGetBoatStates test\n");
        int pass = 0;
        Field ownField, oppField;
        FieldInit(&ownField, &oppField);
        ownField.hugeBoatLives = 1;
        ownField.largeBoatLives = 0;
        ownField.mediumBoatLives = 1;
        ownField.smallBoatLives = 0;

        // test 1
        if ((FieldGetBoatStates(&ownField) & FIELD_BOAT_STATUS_SMALL) == 0) {
            printf("FieldGetBoatStates test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldGetBoatStates test 1 FAILED\n");
        }


        // test 2 
        if ((FieldGetBoatStates(&ownField) & FIELD_BOAT_STATUS_MEDIUM)) {
            printf("FieldGetBoatStates test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldGetBoatStates test 2 FAILED\n");
        }

        // test 3
        if (!(FieldGetBoatStates(&ownField) & FIELD_BOAT_STATUS_LARGE)) {
            printf("FieldGetBoatStates test 3 PASSED\n");
            pass++;
        } else {
            printf("FieldGetBoatStates test 3 FAILED\n");
        }



        // test 4
        if ((FieldGetBoatStates(&ownField) & FIELD_BOAT_STATUS_HUGE)) {
            printf("FieldGetBoatStates test 4 PASSED\n");
            pass++;
        } else {
            printf("FieldGetBoatStates test 4 FAILED\n");
        }
        printf("%d/4 FieldGetBoatStates tests PASSED\n", pass);
    }

    //End of FieldGetBoatStates

    //FieldAIPlaceAllBoats test

    {
        printf("\nThis is FieldAIPlaceAllBoats test\n");
        int pass = 0;
        Field ownField, oppField;

        //test 1 
        FieldInit(&ownField, &oppField);
        if (FieldAIPlaceAllBoats(&ownField)) {
            printf("FieldAIPlaceAllBoats test 1 PASSED\n");
            pass++;
        } else {
            printf("FieldAIPlaceAllBoats test 1 FAILED\n");
        }
        
        //test 2 
        if (ownField.hugeBoatLives && ownField.largeBoatLives && ownField.mediumBoatLives && ownField.smallBoatLives) {
            printf("FieldAIPlaceAllBoats test 2 PASSED\n");
            pass++;
        } else {
            printf("FieldAIPlaceAllBoats test 2 FAILED\n");
        }

        printf("%d/2 FieldAIPlaceAllBoats tests PASSED\n", pass);
    }
}






