//Header for routing in sensor node
#ifndef APPRouter_h
#define APPRouter_h

#include <stdint.h>
#define ROUTER_TABLE_LENGTH 5

class AppRouter
{
    public:

    int16_t* Rssi;
    uint16_t* DestinationID ;
    uint8_t* DistanceToGateway;

    AppRouter();
    ~AppRouter();
    void addRoute(uint16_t destinationID, uint16_t rssi, uint8_t distanceToGateway);
    void getBestRoute();
    uint8_t getWorstRoute();
    void updateTable(int16_t destID, int16_t rssi, uint8_t distToGateway);
    void getRouteTo(uint16_t  id);
    uint8_t contains(uint16_t destID);
    uint8_t  hasFreePosition();
    int16_t getRssiAt(uint8_t index);
    uint8_t getDestinationIDAt(uint8_t index);
    uint8_t getDistanceToGatewayAt(uint8_t index);
    void resetRoutingTable();
};

#endif

