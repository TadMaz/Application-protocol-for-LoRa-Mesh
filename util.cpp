#include "util.h"

bool Util::isBroadcastMessage(uint8_t* buffer){
    return (buffer[0] & 0b111) == 1;
}

bool Util::isVibrationSignature(uint8_t* buffer){
    return (char)buffer[0] == '2';
}

bool Util::matchIDs(uint8_t* buffer){
    return (char) buffer[4] == '1';
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

void Util::convertToBytes(float number, uint8_t* result){
    *(float*)(result) = number;
}

