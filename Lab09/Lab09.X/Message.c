/*
 *Neili Hu nehu 1752639
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Message.h"
#include "BOARD.h"
#define ERROR 10
static char payload2[MESSAGE_MAX_PAYLOAD_LEN], checksum2[MESSAGE_CHECKSUM_LEN];
static int data = -1, record_pay = 0, record_che = 0;


int htoi(const char *string)//help function
{
    int i = 0, n = 0;

    for (; (string[i] >= '0' && string[i] <= '9') || (string[i] >= 'A' && string[i] <= 'Z'); ++i) {
        if (string[i] > '9') {
            n = 16 * n + (10 + string[i] - 'A');
        } else {
            n = 16 * n + (string[i] - '0');
        }
    }
    return n;
}

uint8_t Message_CalculateChecksum(const char* payload)
{
    int l = 0, i = 0, j = strlen(payload);

    if (j < 5) {
        return 0;
    } else {
        for (; i < j; i++) {
            l = l^payload[i];
        }
        return l;
    }

}

int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event)
{
    char i[3], j[] = "";
    int c = 0;
    if (strlen(checksum_string) == 2) {
        if (htoi(checksum_string) == Message_CalculateChecksum(payload)) {
            for (c=0; c < 3; c++) {
                i[c] = payload[c];
            }
            i[c] = '\0';
            if (strcmp(i, "CHA") == 0) {
                message_event->type = BB_EVENT_CHA_RECEIVED;
                message_event->param0 = atoi(strncpy(j, payload + 4, 5));//CHA,12345
                return SUCCESS;
            } else if (strcmp(i, "ACC") == 0) {
                message_event->type = BB_EVENT_ACC_RECEIVED;
                message_event->param0 = atoi(strncpy(j, payload + 4, 5));//ACC,12345
                return SUCCESS;
            } else if (strcmp(i, "REV") == 0) {
                message_event->type = BB_EVENT_REV_RECEIVED;
                message_event->param0 = atoi(strncpy(j, payload + 4, 5));//REV,12345
                return SUCCESS;
            } else if (strcmp(i, "SHO") == 0) {
                message_event->type = BB_EVENT_SHO_RECEIVED;
                if (payload[5] == ',') {
                    message_event->param0 = atoi(strncpy(j, payload + 4, 1));
                    if (payload[7] == 0) {
                        message_event->param1 = atoi(strncpy(j, payload + 6, 1));//SHO,1,1
                    } else {
                        message_event->param1 = atoi(strncpy(j, payload + 6, 2));//SHO,10,10
                    }
                } else {
                    message_event->param0 = atoi(strncpy(j, payload + 4, 2));
                    if (payload[8] == 0) {
                        message_event->param1 = atoi(strncpy(j, payload + 7, 1));//SHO,10,1
                    } else {
                        message_event->param1 = atoi(strncpy(j, payload + 7, 2));//SHO,10,10
                    }
                }
                return SUCCESS;
            } else if (strcmp(i, "RES") == 0) {
                message_event->type = BB_EVENT_RES_RECEIVED;
                if (payload[5]==',') {
                    message_event->param0 = atoi(strncpy(j, payload + 4, 1));
                    if (payload[7] == ',') {
                        message_event->param0 = atoi(strncpy(j, payload + 6, 1));
                        if (payload[9]==0) {
                            message_event->param0 = atoi(strncpy(j, payload + 8, 1));//RES,1,1,1
                        } else {
                            message_event->param0 = atoi(strncpy(j, payload + 8, 2));//RES,1,1,10
                        }
                    } else {
                        message_event->param0 = atoi(strncpy(j, payload + 6, 2));
                        if (payload[10]==0){
                            message_event->param0 = atoi(strncpy(j, payload + 9, 1));//RES,1,10,1
                        } else {
                            message_event->param0 = atoi(strncpy(j, payload + 9, 2));//RES,1,10,10
                        }
                    }
                } else {
                    message_event->param0 = atoi(strncpy(j, payload + 4, 2));
                    if (payload[8]==','){
                        message_event->param0 = atoi(strncpy(j, payload + 7, 1));
                        if (payload[10]==0) {
                            message_event->param0 = atoi(strncpy(j, payload + 9, 1));//RES,10,1,1
                        } else {
                            message_event->param0 = atoi(strncpy(j, payload + 9, 2));//RES,10,1,10
                        }
                    } else {
                        message_event->param0 = atoi(strncpy(j, payload + 7, 2));
                        if (payload[11]==0) {
                            message_event->param0 = atoi(strncpy(j, payload + 10, 1));//RES,10,10,1
                        } else {
                            message_event->param0 = atoi(strncpy(j, payload + 10, 2));//RES,10,10,10
                        }
                    }
                }
                return SUCCESS;
            } else {
                message_event->type = BB_EVENT_ERROR;
                return STANDARD_ERROR;
            }
        } else {
            message_event->type = BB_EVENT_ERROR;
            return STANDARD_ERROR;
        }
    } else {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
}

int Message_Encode(char *message_string, Message message_to_encode)
{
    char i[MESSAGE_MAX_LEN];

    switch (message_to_encode.type) {
    case MESSAGE_CHA:
        sprintf(i, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
        return sprintf(message_string, MESSAGE_TEMPLATE, i, Message_CalculateChecksum(i));
        break;
    case MESSAGE_ACC:
        sprintf(i, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
        return sprintf(message_string, MESSAGE_TEMPLATE, i, Message_CalculateChecksum(i));
        break;
    case MESSAGE_REV:
        sprintf(i, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
        return sprintf(message_string, MESSAGE_TEMPLATE, i, Message_CalculateChecksum(i));
        break;
    case MESSAGE_SHO:
        sprintf(i, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
        return sprintf(message_string, MESSAGE_TEMPLATE, i, Message_CalculateChecksum(i));
        break;
    case MESSAGE_RES:
        sprintf(i, PAYLOAD_TEMPLATE_RES, message_to_encode.param0,
                message_to_encode.param1, message_to_encode.param2);
        return sprintf(message_string, MESSAGE_TEMPLATE, i, Message_CalculateChecksum(i));
        break;
    case MESSAGE_NONE:
        return 0;
    }
}

int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    if ((data == 0) && (char_in != '*')) {
        if ((record_pay == MESSAGE_MAX_PAYLOAD_LEN) || (char_in == '$')) {
            data = data + ERROR;
            printf("here");
            return STANDARD_ERROR;
        } else {
            payload2[record_pay] = char_in;
            return SUCCESS;
        }
        record_pay++;
    } else if ((data == 1) && (char_in != '\n')) {
        if ((record_che == MESSAGE_CHECKSUM_LEN) || ((char_in < '0' || char_in > '9')
                && (char_in < 'A' || char_in > 'Z'))) {
            data = data + ERROR;
            return STANDARD_ERROR;
        } else {
            checksum2[record_che] = char_in;
            record_che++;
            return SUCCESS;
        }
    }

    if (char_in == '$') {
        data++;
        return SUCCESS;
    } else if (char_in == '*') {
        data++;
        return SUCCESS;
    } else if ((char_in == '\n') && data < ERROR) {
        if (Message_ParseMessage(payload2, checksum2, decoded_message_event)) {
            return SUCCESS;
        } else {
            return STANDARD_ERROR;
        }
        data == -1;
        record_pay == 0;
        record_che == 0;
        memset(payload2, 0, MESSAGE_MAX_PAYLOAD_LEN);
        memset(checksum2, 0, MESSAGE_CHECKSUM_LEN);
    } else if ((char_in == '\n') && data >= ERROR) {
        data == -1;
        record_pay == 0;
        record_che == 0;
        memset(payload2, 0, MESSAGE_MAX_PAYLOAD_LEN);
        memset(checksum2, 0, MESSAGE_CHECKSUM_LEN);
        return STANDARD_ERROR;
    }
}