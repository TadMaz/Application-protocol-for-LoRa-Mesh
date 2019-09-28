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
    void static extractVibrationSignature(uint8_t* buffer, float* output);
    void static readNodeIdFromBuffer(uint16_t* nodeId, uint8_t* buffer, int position);
    void static readPayloadFromBuffer();
    void static readVibrationReadingFromBuffer();
    void static unpackFloat();
    void static unpackInt16_t();
};

#endif