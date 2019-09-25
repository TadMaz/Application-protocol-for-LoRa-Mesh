/* Header File defining all message structures*/

//Define Message Types
#define BROADCAST_MESSAGE 1
#define BROADCAST_MESSAGE_LENGTH 4

//Define Payload Structure
#define MESSAGE_TYPE_START 0
#define NODE_ID_START 3
#define DISTANCE_TO_GATEWAY_START 19

//Define Bit Masks for byte packing
#define BYTE_MASK 0xFF

//Masks to Extract data from payload

