#include "rx.h"
#include "util.h"


uint16_t Rx::extractBroadcastMessage(uint8_t* buffer,uint16_t rssi, AppRouter* router){

    //{9, 0, 32, 3}
    uint32_t payload = 0x0;

    for (char i = 0; i<BROADCAST_MESSAGE_LENGTH; i++){
        payload |= ((uint32_t) buffer[i])<<i*8;
    }
    
    uint32_t node_id = (payload & 0b1111111111111111000)>>NODE_ID_START;
    uint8_t dist_to_gateway = (payload & 0b111111110000000000000000000)>>DISTANCE_TO_GATEWAY_START; 
    
    // add route to routing table
    router->addRoute(node_id,rssi,dist_to_gateway);

    return node_id;

}

void Rx::extractVibrationSignature(uint8_t* buffer, uint16_t* sourceId, uint16_t* destId,
                                   uint8_t* msgType,float* timestamp, float* windspeed,
                                   int16_t* accX, int16_t* accY,
                                   int16_t* accZ, float* pitch,
                                   float* roll){

   //read the Source ID and Destination ID
    Util::readNodeIdFromBuffer(sourceId, buffer, SOURCE_ID_START);
    Util::readNodeIdFromBuffer(destId, buffer, DESTINATION_ID_START);

    //read the Message Type
    Util::readMessageTypeFromBuffer(msgType, buffer, GATEWAY_MSG_TYPE_START);

   
    //read the payload
    readPayloadFromBuffer(timestamp,windspeed,
                         accX, accY, accZ,
                         pitch, roll, buffer,MAX_NO_OF_READINGS);
}


void Rx::readPayloadFromBuffer(float* timestamp, float* windspeed,
                                int16_t* accX, int16_t* accY,
                                int16_t* accZ, float* pitch,
                                float* roll, uint8_t* buffer,
                                int numberofReadings){
    //Go through Buffer and unpack  bytes for the different types.
    //Store the different types in arrays 
    if (numberofReadings>MAX_NO_OF_READINGS) return;

    int bufferIndex = GATEWAY_MSG_PAYLOAD_START;
    // for each reading, copy the value to these arrays
    for (int i = 0; i<numberofReadings; i++){

        readVibrationReadingFromBuffer( &timestamp[i],
                                        &windspeed[i],
                                        &accX[i],
                                        &accY[i],
                                        &accZ[i],
                                        &pitch[i],
                                        &roll[i],
                                        &buffer[i],
                                        &bufferIndex
                                      );
        bufferIndex--;
    }
    
}

void Rx::readVibrationReadingFromBuffer(float* timestamp, float* windspeed,
                                       int16_t* accX, int16_t* accY,
                                       int16_t* accZ, float* pitch,
                                       float* roll, uint8_t* buffer,
                                       int* bufferIndex){

    unpackFloat(timestamp, buffer, bufferIndex);
    unpackFloat(windspeed, buffer, bufferIndex);
    unpackInt16_t(accX, buffer, bufferIndex);
    unpackInt16_t(accY, buffer, bufferIndex);
    unpackInt16_t(accZ, buffer, bufferIndex);
    unpackFloat(pitch, buffer, bufferIndex);
    unpackFloat(roll, buffer, bufferIndex);

}
void Rx::unpackFloat(float* number, uint8_t* buffer, int* bufferIndex){
    
    //Allocate space for number
    uint8_t bytes[4];

    //Read the number in byte-form from the buffer
    for (char i = 0; i<4; i++) bytes[i] = buffer[(*bufferIndex)++]; 

    *number = *(float*)(bytes);  // convert bytes back to float
}

void Rx::unpackInt16_t(int16_t* number, uint8_t* buffer, int* bufferIndex){

    *number = ( (uint16_t)buffer[(*bufferIndex)++]) <<8 | ((uint16_t)buffer[(*bufferIndex)++]);
}
