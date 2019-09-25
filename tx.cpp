// construct 27 bit broacast message number (4 bytes)
// represent everything as bits and add togeher
#include "tx.h"

void Tx::constructBroadcastMessage(uint8_t* result){

    uint32_t payload = 0x0;

    //0b0000 0 | dist_gateway | node_id | msg_type |;

    payload |= (((uint32_t)BROADCAST_MESSAGE << MESSAGE_TYPE_START)|
                ((uint32_t)NODE_ID << NODE_ID_START)|
                ((uint32_t)DISTANCE_TO_GATEWAY << DISTANCE_TO_GATEWAY_START));
    

    // Pack the bits

    for (char i = 0; i<BROADCAST_MESSAGE_LENGTH; i++){
        result[i] = ((payload & ((uint32_t) BYTE_MASK << i*8)) >> i*8);
    }

}

void Tx::constructVibrationMessage(uint8_t * output){

    // dummy sensor data
    uint8_t data[] = {"20201"
                        "14066967,3.46,38,-24,140,1.76,-1.40;"
                        "14066974,3.46,-44,-12,148,1.68,-1.48;"
                        "14066984,3.46,-45,5,151,1.68,-1.48"
                        "14066995,3.46,-36,18,156,1.68,-1.47;"
                        "14067005,3.46,-12,29,147,1.69,-1.48;"
                        "14067015,3.46,17,32,138,1.69,-1.47;"}; 
    output = data;
}