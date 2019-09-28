#ifndef RX_H
#define RX_H

#include <stdint.h>
#include "node_config.h"
#include "messages.h"
#include "app_routing.h"


class Rx
{
    public:
    
    uint32_t static extractBroadcastMessage(uint8_t* buffer,uint16_t rssi, AppRouter* router);
    
    void static extractVibrationSignature(uint8_t* buffer, uint16_t* sourceId, uint16_t* destId,
                                          uint8_t* msgType);

    void static readNodeIdFromBuffer(uint16_t* nodeId, uint8_t* buffer, int position);

    void static readPayloadFromBuffer(float* timestamp, float* windspeed,
                                       int16_t* accX, int16_t* accY,
                                       int16_t* accZ, float* pitch,
                                       float* roll, uint8_t* buffer,
                                       int* bufferIndex, int numberofReadings);

    void static readVibrationReadingFromBuffer(float* timestamp, float* windspeed,
                                       int16_t* accX, int16_t* accY,
                                       int16_t* accZ, float* pitch,
                                       float* roll, uint8_t* buffer,
                                       int* bufferIndex);

    void static readMessageTypeFromBuffer(uint8_t* msgType, uint8_t* buffer, int position);

    void static unpackFloat(float* number, uint8_t* buffer, int* bufferIndex);

    void static unpackInt16_t(int16_t* number, uint8_t* buffer, int* bufferIndex);
};

#endif