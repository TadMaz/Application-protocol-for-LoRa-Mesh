#ifndef TX_H
#define TX_H

#include <stdint.h>
#include "node_config.h"
#include "messages.h"
#include "util.h"


class Tx
{
    public:

    void static constructBroadcastMessage(uint8_t* result);
    void static constructVibrationMessage(uint8_t* buf);
    void static writeNodeIdToBuffer(uint16_t nodeId, uint8_t* buffer, int position);
    void static writePayloadToBuffer(uint8_t* buffer);
    void static writeVibrationReadingToBuffer(float timestamp, float windspeed,
                                       int16_t accX, int16_t accY,
                                       int16_t accZ, float pitch,
                                       float roll, uint8_t* buffer,
                                       int* bufferIndex);
    void static writeMessageTypeToBuffer(int msgType, uint8_t* buffer, int position);
    void static packFloat(float number, uint8_t* buffer, int* bufferIndex);
    void static packInt16_t(int16_t number, uint8_t* buffer, int* bufferIndex);
    void static sendMessageToNode();
};

#endif