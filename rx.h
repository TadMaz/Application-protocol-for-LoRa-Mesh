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
};

#endif