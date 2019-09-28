/* Header File defining all message structures*/

//Define Message Types
#define BROADCAST_MESSAGE 1
#define BROADCAST_MESSAGE_LENGTH 4

//Define Payload Structure for Broadcast Message
#define MESSAGE_TYPE_START 0
#define NODE_ID_START 3
#define DISTANCE_TO_GATEWAY_START 19

//Define Message Structure for all Gateway Messages
#define SOURCE_ID_START 0
#define DESTINATION_ID_START 2
#define MAX_NO_OF_READINGS 11               // Each reading is 22 bytes, Available space = 255 - 4(RFM95 Header) - 5(Header) = 246 Bytes 

//Define Bit Masks for byte packing
#define BYTE_MASK 0xFF

//Masks to Extract data from payload

