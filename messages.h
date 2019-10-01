/* Header File defining all message structures*/

//Define Message Types
#define BROADCAST_MESSAGE 1
#define VIBRATION_SIGNATURE_MESSAGE 2
//#define MAGNETIC_DATA_MESSAGE 3
#define HEARTBEAT_MESSAGE 4

//------------------------Define Message Structure for all Gateway Messages--------------------------------

//1.Define Payload Structure for Broadcast Message
#define MESSAGE_TYPE_START 0
#define NODE_ID_START 3
#define DISTANCE_TO_GATEWAY_START 19
#define BROADCAST_MESSAGE_LENGTH 4

// 2. Vibration Message Definitions
#define GATEWAY_MSG_PAYLOAD_START 5
#define MAX_NO_OF_READINGS 11               // Each reading is 22 bytes, Available space = 255 - 4(RFM95 Header) - 5(Header) = 246 Bytes
#define SOURCE_ID_START 0
#define DESTINATION_ID_START 2
#define GATEWAY_MSG_TYPE_START 4


// 3. HEARTBEAT MESSAGE
#define HEARTBEAT_PAYLOAD_START 4

//Define Bit Masks for byte packing
#define BYTE_MASK 0xFF

//Masks to Extract data from payload

