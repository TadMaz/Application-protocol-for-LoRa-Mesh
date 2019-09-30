#include "util.h"

bool Util::isBroadcastMessage(uint8_t* buffer){
    return (buffer[0] & 0b111) == 1;
}

bool Util::isVibrationSignature(uint8_t* buffer){
    uint8_t msgType;
    readMessageTypeFromBuffer(&msgType, buffer, VIBR_MSG_START);
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

