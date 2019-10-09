#include "util.h"

bool Util::isBroadcastMessage(uint8_t* buffer){
    return (buffer[0] & 0b111) == 1;
}

bool Util::isVibrationSignature(uint8_t* buffer){
    uint8_t msgType;
    readMessageTypeFromBuffer(&msgType, buffer, GATEWAY_MSG_TYPE_START);
    return msgType == VIBRATION_SIGNATURE_MESSAGE;
}

bool Util::matchIDs(uint8_t* buffer){
    uint16_t otherNodeId;
    readNodeIdFromBuffer(&otherNodeId, buffer, DESTINATION_ID_START);
    return otherNodeId == NODE_ID;
}

void Util::readNodeIdFromBuffer(uint16_t* nodeId, uint8_t* buffer, int position){

    /// buffer[pos] | buffer [pos+1]
    *nodeId = (uint16_t)(buffer[position]<<8) | (uint16_t)(buffer[position+1]) ;
}

void Util::readMessageTypeFromBuffer(uint8_t* msgType, uint8_t* buffer, int position){
    *msgType = buffer[position];
} 

void Util::writeNodeIdToBuffer(uint16_t nodeId, uint8_t* buffer, int position){

    //Node ID : 0b | 0000 0000 | 0000 0001 |

    buffer[position] = nodeId>>8;
    buffer[position +1] = nodeId & ((uint16_t)(BYTE_MASK));

}

void Util::writeMessageTypeToBuffer(int msgType, uint8_t* buffer, int position){
    buffer[position] = msgType;
}

uint8_t Util:: getBatteryStatus(){
    /* This method returns the Node Battery Status 
                The node has 4 battery life modes 
                0b00 - Critical Power <= 20 %
                0b01 - Low Power : >20 %
                0b10 - Medium Power : > 50 %
                0b11 - Full  : >75% */
                
    return (uint8_t) 3;
}

