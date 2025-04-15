#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"
#include <stdint.h>
#include "BattleBoats.h"
#include "Negotiation.h"


void main()
{//******************NegotiationHash() testing***********************//
    if (NegotiationHash(20)==400){
        printf("NegotiationHash() test 1 works\n");
    } else {
        printf("NegotiationHash() test 1 Fail\n");
    }
    
//*******************NegotiationVerify() testing*********************//   
    if (NegotiationVerify(30,900)){
        printf("NegotiationVerify() test 1 works\n");
    } else {
        printf("NegotiationVerify() test 1 Fail\n");
    }
    
    if (NegotiationVerify(12345,43182)){
        printf("NegotiationVerify() test 2 works\n");
    } else {
        printf("NegotiationVerify() test 2 Fail\n");
    }
    
    if (NegotiationVerify(0,0)){
        printf("NegotiationVerify() test 3 works\n");
    } else {
        printf("NegotiationVerify() test 3 Fail\n");
    }
//*****************NegotiateCoinFlip() testing*********************// 
    if (NegotiateCoinFlip(00121,30125)){
        printf("NegotiateCoinFlip() test 1 works\n");
    } else {
        printf("NegotiateCoinFlip() test 1 Fail\n");
    }
    
    if (!(NegotiateCoinFlip(00121,30124))){
        printf("NegotiateCoinFlip() test 2 works\n");
    } else {
        printf("NegotiateCoinFlip() test 2 Fail\n");
    }

    if (NegotiateCoinFlip(30124,30124)){
        printf("NegotiateCoinFlip() test 3 works\n");
    } else {
        printf("NegotiateCoinFlip() test 3 Fail\n");
    }


    
}