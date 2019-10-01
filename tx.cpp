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
    
    //                         | SOURCE ID | DESTINATION ID | MSG TYPE | PAYLOAD |

    //Write the Source ID, Destination ID and Message Type to Buffer 
    //Source ID uses first 2 bytes ; Destination ID follows after

    Util::writeNodeIdToBuffer(NODE_ID, output, SOURCE_ID_START);
    Util::writeNodeIdToBuffer(2, output, DESTINATION_ID_START);
    Util::writeMessageTypeToBuffer(VIBRATION_SIGNATURE_MESSAGE, output, GATEWAY_MSG_TYPE_START);
    // Write Payload to Buffer 
    writeVibrationPayloadToBuffer(output);
}

void Tx::constructHeartbeatMessage(uint8_t* output, uint16_t destinationID){

    //                          | SOURCE ID | DESTINATION ID | MSG TYPE | PAYLOAD |

    Util::writeNodeIdToBuffer(NODE_ID, output, SOURCE_ID_START);
    Util::writeNodeIdToBuffer(destinationID, output, DESTINATION_ID_START);
    Util::writeMessageTypeToBuffer(HEARTBEAT_MESSAGE, output, GATEWAY_MSG_TYPE_START);
    
}

void Tx::writeHeartbeatPayloadToBuffer(uint8_t* buffer){
    
    buffer[GATEWAY_MSG_PAYLOAD_START] = Util::getBatteryStatus();
}

void Tx::writeVibrationPayloadToBuffer(uint8_t* buffer){

    // Define the dummy data to be sent 

    float timestamp[MAX_NO_OF_READINGS] = {14066967,14066974,14066984,14066995,14067005,14067015,
                            14067024,14067035,14067045,14067055,14067064};
    float windspeed[MAX_NO_OF_READINGS] = {3.46, 3.46, 3.46, 3.46 ,3.46 ,3.46 ,3.46 ,3.46 ,3.46 ,3.46 ,3.46};
    int16_t accX[MAX_NO_OF_READINGS] = {38,-44,-45,-36,-12 ,17 ,44 ,61, 68 ,83 ,95 };
    int16_t accY [MAX_NO_OF_READINGS] = {-24,-12, 5, 18, 29 ,32, 26 ,23, 39 ,62 ,77};
    int16_t accZ[MAX_NO_OF_READINGS] = {140,148,151,156,147,138,138,137,141,131,132};
    float pitch [MAX_NO_OF_READINGS] = {1.76,1.68,1.68,1.68,1.69,1.69,1.7,1.71,1.71,1.72, 1.73 };
    float roll [MAX_NO_OF_READINGS] = {-1.4,-1.48,-1.48,-1.47,-1.48,-1.47,-1.47,-1.47,-1.46 ,-1.46,-1.45};

    //Convert readings into bytes and pack
    int bufferIndex = GATEWAY_MSG_PAYLOAD_START;

    for (char i = 0; i<MAX_NO_OF_READINGS; i++){
        
       writeVibrationReadingToBuffer(   timestamp[i],
                                        windspeed[i],
                                        accX[i],
                                        accY[i],
                                        accZ[i],
                                        pitch[i],
                                        roll[i],
                                        buffer,
                                        &bufferIndex
                                    );
    }
}

void Tx::writeVibrationReadingToBuffer(float timestamp, float windspeed,
                                       int16_t accX, int16_t accY,
                                       int16_t accZ, float pitch,
                                       float roll, uint8_t* buffer,
                                       int* bufferIndex){

    
    packFloat(timestamp, buffer, bufferIndex);
    packFloat(windspeed, buffer, bufferIndex);
    packInt16_t(accX, buffer, bufferIndex);
    packInt16_t(accY, buffer, bufferIndex );
    packInt16_t(accZ, buffer, bufferIndex);
    packFloat(pitch, buffer, bufferIndex);
    packFloat(roll, buffer, bufferIndex);

}

void Tx::packFloat(float number, uint8_t* buffer, int* bufferIndex){
    
    uint8_t bytes [4];
    
    *(float*)(bytes) = number;          //Convert float to bytes

    //Pack bytes into the buffer
    for (char j = 0 ; j<4; j++){  buffer[(*bufferIndex)++] = bytes[j]; }
}

void  Tx::packInt16_t(int16_t number, uint8_t* buffer, int* bufferIndex){
    
    //0b 0000 0000 | 0000 0001 |
    buffer[(*bufferIndex)++] = ( number >> 8 );
    buffer[(*bufferIndex)++] = (number & (uint16_t)0xFF);
}