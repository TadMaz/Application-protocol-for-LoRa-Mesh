
#include "app_routing.h"
#include "util.h"

AppRouter::AppRouter()
{   

    Rssi = new int16_t[ROUTER_TABLE_LENGTH];
    DestinationID = new uint16_t[ROUTER_TABLE_LENGTH];
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

    //Add the route to a free position in the routing table
    position =  AppRouter::hasFreePosition();

    if(position!= -1){
        DestinationID[position] = destinationID;
        Rssi[position] = rssi;
        DistanceToGateway[position] = distanceToGateway;
        return;
    }
    //Otherwise, find the weakest route and replace it with this route
    AppRouter::updateTable(destinationID, rssi, distanceToGateway);  

}

uint8_t AppRouter::contains(uint16_t destID){

    for(char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == destID)
            return (uint8_t )i;
    }
    return -1;
}

uint8_t  AppRouter::hasFreePosition(){
    for (char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == 0)
            return (uint8_t )i;
    }
    return -1;
}

void AppRouter::updateTable(int16_t destID, int16_t rssi, uint8_t distToGateway){

    uint8_t indexOfWorst = getWorstRoute();
  
    DestinationID[indexOfWorst] = destID;
    Rssi[indexOfWorst] = rssi;
    DistanceToGateway[indexOfWorst] = distToGateway;
    
}

int16_t AppRouter::getRssiAt(uint8_t index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return Rssi[index];
}

uint8_t AppRouter::getDestinationIDAt(uint8_t index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return DestinationID[index];
}

uint8_t AppRouter::getDistanceToGatewayAt(uint8_t index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return DistanceToGateway[index];
}

uint8_t AppRouter::getWorstRoute(){

    uint8_t index_of_worst = ROUTER_TABLE_LENGTH;

    for (char i = 0; i<(ROUTER_TABLE_LENGTH -1); i++){ 
        if(Rssi[i]/DistanceToGateway[i]< Rssi[i+1]/DistanceToGateway[i+1]){
            index_of_worst = i;
            continue;
        }
        index_of_worst = i+1;
    }
    return index_of_worst;
}

void AppRouter::resetRoutingTable(){
    
    for (int i = 0; i<ROUTER_TABLE_LENGTH; i++){
        Rssi[i] = 0;
        DestinationID[i] = 0;
        DistanceToGateway[i] = 0;
    }
}
