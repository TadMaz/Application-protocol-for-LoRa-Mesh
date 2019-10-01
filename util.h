#ifndef APPUtil_h
#define APPUtil_h

#include <stdint.h>
#include "messages.h"
#include "node_config.h"

class Util{

    public:

    bool static isBroadcastMessage(uint8_t* buffer);
    bool static isVibrationSignature(uint8_t* buffer);
    bool static matchIDs(uint8_t* buffer);
    void static readNodeIdFromBuffer(uint16_t* nodeId, uint8_t* buffer, int position);
    void static readMessageTypeFromBuffer(uint8_t* msgType, uint8_t* buffer, int position);
    void static writeMessageTypeToBuffer(int msgType, uint8_t* buffer, int position);
    void static writeNodeIdToBuffer(uint16_t nodeId, uint8_t* buffer, int position);
    uint8_t static getBatteryStatus();
};
#endif