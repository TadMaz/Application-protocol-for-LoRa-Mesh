#include "rx.h"
#include "util.h"


uint32_t Rx::extractBroadcastMessage(uint8_t* buffer,uint16_t rssi, AppRouter* router){

    //{9, 0, 32, 3}
    uint32_t payload = 0x0;

    for (char i = 0; i<BROADCAST_MESSAGE_LENGTH; i++){
        payload |= ((uint32_t) buffer[i])<<i*8;
    }
    
    uint16_t node_id = (payload & 0b1111111111111111000)>>NODE_ID_START;
    uint8_t dist_to_gateway = (payload & 0b111111110000000000000000000)>>DISTANCE_TO_GATEWAY_START; 
    
    // add route to routing table
    router->addRoute(node_id,rssi,dist_to_gateway);

    return node_id;

}

void Rx::extractVibrationSignature(uint8_t* buffer, float* output){

    int pos = 0;
    //convert each byte back into float and store.
    for (char i = 4; i<47; i+=4){
        
        //Extract the bytes from the buffer
        uint8_t bytes[] = {buffer[i-4], buffer[i-3], buffer[i-2], buffer[i-1]};

        //convert bytes to float
        output[pos] = *(float*)(bytes);
        pos++; 
    }
}

void Rx::unpackFloat(){

}

void Rx::unpackInt16_t(){

}
