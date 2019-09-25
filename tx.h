#ifndef TX_H
#define TX_H

#include <stdint.h>
#include "node_config.h"
#include "messages.h"


class Tx
{
    public:

    void static constructBroadcastMessage(uint8_t* result);
    void static constructVibrationMessage(uint8_t* buf);
};

#endif