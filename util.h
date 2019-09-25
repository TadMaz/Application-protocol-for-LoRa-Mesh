#ifndef APPUtil_h
#define APPUtil_h

#include <stdint.h>


class Util{

    public:

    bool static isBroadcastMessage(uint8_t* buffer);
    bool static isVibrationSignature(uint8_t* buffer);
    uint8_t static combineBits (uint8_t msb, uint8_t lsb);
};
#endif