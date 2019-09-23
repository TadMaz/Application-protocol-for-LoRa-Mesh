//Header for routing in sensor node
#ifndef APPRouter_h
#define APPRouter_h

#include <stdint.h>
#define ROUTER_TABLE_LENGTH 5

class AppRouter
{
    public:

    int16_t* Rssi;
    uint32_t* DestinationID ;
    uint8_t* DistanceToGateway;

    AppRouter();
    ~AppRouter();
    void addRoute(uint8_t* data, uint16_t rssi);
    void getBestRoute();
    int updateTable(int32_t destID, int16_t rssi, uint8_t distToGateway);
    void getRouteTo(int id);
    int contains(uint32_t destID);
    int hasFreePosition();
    int16_t getRssiAt(int index);
    uint32_t getDestinationIDAt(int index);
    uint8_t getDistanceToGatewayAt(int index);
};

#endif

