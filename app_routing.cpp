
#include "app_routing.h"
#include "util.h"

AppRouter::AppRouter()
{   

    Rssi = new int16_t[ROUTER_TABLE_LENGTH];
    DestinationID = new uint32_t[ROUTER_TABLE_LENGTH];
    DistanceToGateway = new uint8_t[ROUTER_TABLE_LENGTH];

    for (int i = 0; i<ROUTER_TABLE_LENGTH; i++){
        Rssi[i] = 0;
        DestinationID[i] = 0;
        DistanceToGateway[i] = 0;
    }
}

AppRouter::~AppRouter(){
    delete[] Rssi;
    delete[] DestinationID;
    delete[] DistanceToGateway;
}

void AppRouter::addRoute(uint16_t destinationID, uint16_t rssi, uint8_t distanceToGateway){
    
    // If entry exists, update the Relative Signal Strength
    int position = AppRouter::contains(destinationID);

    if(position!=-1){
        Rssi[position] = rssi;
        return;
    }

    position =  AppRouter::hasFreePosition();

    if(position!= -1){
        DestinationID[position] = destinationID;
        Rssi[position] = rssi;
        DistanceToGateway[position] = distanceToGateway;
        return;
    }

    AppRouter::updateTable(destinationID, rssi, distanceToGateway);  

}

int AppRouter::contains(uint32_t destID){

    for(char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == destID)
            return (int)i;
    }
    return -1;
}

int AppRouter::hasFreePosition(){
    for (char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == 0)
            return (int)i;
    }
    return -1;
}

int AppRouter::updateTable(int32_t destID, int16_t rssi, uint8_t distToGateway){

    for(char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        //Better RSSI to distance gateway ratio
        if( Rssi[i]/DistanceToGateway[i] > rssi/distToGateway){
            DestinationID[i] = destID;
            Rssi[i] = rssi;
            DistanceToGateway[i] = distToGateway;
            return 1;
        }
    }
    return 0;
}

int16_t AppRouter::getRssiAt(int index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return Rssi[index];
}

uint32_t AppRouter::getDestinationIDAt(int index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return DestinationID[index];
}

uint8_t AppRouter::getDistanceToGatewayAt(int index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return DistanceToGateway[index];
}

