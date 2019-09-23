#include "util.h"

bool Util::isBroadcastMessage(uint8_t* data){
    return data[0] == 1;
}

uint8_t Util::combineBits (uint8_t msb, uint8_t lsb){
    
    if(lsb<10){
        return msb*10 + lsb;        //shift once
    } 
    if ( lsb <100){           
        return msb*100 + lsb;       //shift twice
    }
    return msb*1000 + lsb;          //shift three times

}