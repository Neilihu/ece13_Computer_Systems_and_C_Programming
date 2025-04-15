#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "BOARD.h"
#include "Message.h"

void main() {
    BOARD_Init();

    printf("Welcome to Jlai38'S MessageTest.  Compiled on %s %s\n\n", __DATE__, __TIME__);

    printf("This is Message_CalculateChecksum Test\n");
    int i = 0;

    char* payload;

    //test 1
    payload = "CHA,1";
    //printf("test 1 %u\n ", Message_CalculateChecksum(payload)); //87

    if (Message_CalculateChecksum(payload) == 87) {
        printf("Message_CalculateChecksum() 1 works\n");
        i++;
    } else {
        printf("Message_CalculateChecksum() 1 fails\n");
    }
    //


    //test 2
    payload = "SHO,2,20";
    // printf("test 2 %u\n ", Message_CalculateChecksum(payload));//100
    if (Message_CalculateChecksum(payload) == 100) {
        printf("Message_CalculateChecksum() 2 works\n");
        i++;
    } else {
        printf("Message_CalculateChecksum() 2 fails\n");
    }

    //test 3
    payload = "ACC,8r";
    //printf("test 3 %u\n ", Message_CalculateChecksum(payload));//39
    if (Message_CalculateChecksum(payload) == 39) {
        printf("Message_CalculateChecksum() 3 works\n");
        i++;
    } else {
        printf("Message_CalculateChecksum() 3 fails\n");
    }


    //test 4
    payload = "REV,2,2";
    //printf("test 4 %u\n", Message_CalculateChecksum(payload)); //65
    if (Message_CalculateChecksum(payload) == 65) {
        printf("Message_CalculateChecksum() 4 works\n");
        i++;
    } else {
        printf("Message_CalculateChecksum() 4 fails\n");
    }


    payload = "RES,1,0,3";
    //printf("%u\n ", Message_CalculateChecksum(payload)); //90
    if (Message_CalculateChecksum(payload) == 90) {
        printf("Message_CalculateChecksum() 5 works\n");
        i++;
    } else {
        printf("Message_CalculateChecksum() 5 fails\n");
    }

    printf("%d/5 Message_CalculateChecksum Tests worked\n\n", i);
    //end of Message_CalculateChecksum



    //begin Message_ParseMessage() test
    printf("This is Message_ParseMessage Test\n");

    char* checksum_string;
    int a = 0;


    checksum_string = "26";
    
    payload = "CHA,43182";
    BB_Event message_event = {};
    //test 1
    //printf("test 1 %U",Message_ParseMessage(payload, checksum_string, &message_event));
    
    if (Message_ParseMessage(payload, checksum_string, &message_event) == STANDARD_ERROR) {
        printf("Message_ParseMessage() test 1 works\n");
        a++;
    } else {
        printf("Message_ParseMessage() test 1 fails\n");
    }

    // test 2
    payload = "REV,7";
    checksum_string = "5a";
    //printf("%U test 02\n ", Message_ParseMessage(payload, checksum_string, &message_event));
    
    if (Message_ParseMessage(payload, checksum_string, &message_event) == SUCCESS) {
        printf("Message_ParseMessage() test 2 works\n");
        a++;
    } else {
        printf("Message_ParseMessage() test 2 fails\n");
    }

    // test 3 
    payload = "ACC,6";
    checksum_string = "2";
    if (Message_ParseMessage(payload, checksum_string, &message_event) == STANDARD_ERROR) {
        printf("Message_ParseMessage() test 3  works\n");
        a++;
    } else {
        printf("Message_ParseMessage() test 3 fails\n");
    }


    printf("%d/3 Message_ParseMessage Tests worked\n\n", a);

    // End of Message_parseMessage Test

    //TESTING MESSAGE ENCODE


    int b = 0;
    char message_string[MESSAGE_MAX_LEN];

    printf("This is Message_Encode Test \n");

    // test 1 
    Message message_to_encode1 = {MESSAGE_SHO, 2, 9};

    //printf("%U test one ", Message_Encode(message_string, message_to_encode1));

    char result_str1[MESSAGE_MAX_LEN] = "$SHO,2,9*5F\n";
    if (Message_Encode(message_string, message_to_encode1) == strlen(result_str1) && !strcmp(message_string, result_str1)) {
        printf("Message_Encode test 1 works\n");
        b++;
    } else {
        printf("Message_Encode TEST 1 fails\n");
    }


    //2
    Message message_to_encode2 = {MESSAGE_CHA, 10};
    char result_str2[MESSAGE_MAX_LEN] = "$CHA,10*67\n";

   // printf("%U test 002 ", Message_Encode(message_string, message_to_encode1));

    if (Message_Encode(message_string, message_to_encode2) == strlen(result_str2) && !strcmp(message_string, result_str2)) {
        printf("Message_Encode test 2 works\n");
        b++;
    } else {
        printf("Message_Encode TEST 2 fails\n");
    }

    Message message_to_encode3 = {MESSAGE_REV, 7};
    char result_str3[MESSAGE_MAX_LEN] = "$REV,7*5A\n";
    if (Message_Encode(message_string, message_to_encode3) == strlen(result_str3) && !strcmp(message_string, result_str3)) {
        printf("Message_Encode test 3 works\n");
        b++;
    } else {
        printf("Message_Encode TEST 3 fails\n");
    }

    printf("%d/3 Message_Encode Tests worked\n\n", b);

    //End of Message_Encode test

    //begin MessageDecode Test

    printf("This is MessageDecode test \n");

    unsigned char char_in;
    BB_EventType expected_type;
    uint16_t expected_param0;

    char_in = '$';
    expected_type = BB_EVENT_CHA_RECEIVED;
    expected_param0 = 10;
    int c = 0;

    // test 1
    BB_Event decoded_message_event1 = {};
    // printf("%U test one 01 ", Message_Decode(char_in, &decoded_message_event1));
    
    if (Message_Decode(char_in, &decoded_message_event1) == SUCCESS) {
        printf("Message_Decode test 1 works\n");
        c++;
    } else {
        printf("Message_Decode test 1 fails\n");
    }


    //test 2
    char_in = 'C';
    expected_type = BB_EVENT_CHA_RECEIVED;
    //  printf("%U test 02", Message_Decode(char_in, &decoded_message_event1));

    if (Message_Decode(char_in, &decoded_message_event1) == SUCCESS) {
        printf("Message_Decode test 2 works\n");
        c++;
    } else {
        printf("Message_Decode test 2 fails\n");
    }

    //test 3
    char_in = '3';
    expected_type = BB_EVENT_CHA_RECEIVED;
    if (Message_Decode(char_in, &decoded_message_event1) == SUCCESS) {
        printf("Message_Decode test 3 works\n");
        c++;
    } else {
        printf("Message_Decode test 3 fails\n");
    }

    printf("%d/3 Message_Decode Tests worked\n\n", c);

    //END
}
