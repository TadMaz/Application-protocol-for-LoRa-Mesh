
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

void AppRouter::addRoute(uint16_t destinationID, int16_t rssi, uint8_t distanceToGateway){
    
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

int AppRouter::contains(uint16_t destID){

    for(char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == destID)
            return (uint8_t )i;
    }
    return -1;
}

int  AppRouter::hasFreePosition(){
    for (char i = 0; i< ROUTER_TABLE_LENGTH; i++){
        if(DestinationID[i] == 0)
            return (uint8_t )i;
    }
    return -1;
}

void AppRouter::updateTable(int16_t destID, int16_t rssi, uint8_t distToGateway){

    uint8_t indexOfWorst = getWorstRoute();
    
    if (indexOfWorst == ROUTER_TABLE_LENGTH) return;

    //check if this reading is better than the worst
    if(distToGateway > DistanceToGateway[indexOfWorst]) return;

    DestinationID[indexOfWorst] = destID;
    Rssi[indexOfWorst] = rssi;
    DistanceToGateway[indexOfWorst] = distToGateway;
    
}

int AppRouter::getRssiAt(uint8_t index){
    if (index > ROUTER_TABLE_LENGTH || index <0)
        return -1;
    return (int) Rssi[index];
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
    //Worst route has largest Rssi/dist_to_gateway ratio
    int worstDistance = -10000;

    for (char i = 0; i < ROUTER_TABLE_LENGTH; i++){
        if (DistanceToGateway[i] == 0) continue;

        // if same distance from gateway -  choose one with better signal strength
        if(DistanceToGateway[i] == worstDistance && Rssi[i] <= Rssi[index_of_worst] ){
            worstDistance = DistanceToGateway[i];
            index_of_worst = i;
            continue;
        }
        
        // The worst route is one that is furthest from the gateway.
        if(DistanceToGateway[i] > worstDistance){
            worstDistance = DistanceToGateway[i];
            index_of_worst = i;
        }
        
    }
    return index_of_worst;

}

uint8_t AppRouter::getBestRoute(){

    uint8_t index_of_best = ROUTER_TABLE_LENGTH;
    int bestDistance = 10000;

    //Best route has is closest to gateway
    for (char i = 0; i < ROUTER_TABLE_LENGTH; i++){
        if (DistanceToGateway[i] == 0) continue;

        // if same distance from gateway -  choose one with better signal strength
        if(DistanceToGateway[i] == bestDistance && Rssi[i] <= Rssi[index_of_best] ){
            bestDistance = DistanceToGateway[i];
            index_of_best = i;
        }
        
        // The worst route is one that is furthest from the gateway.
        if(DistanceToGateway[i] < bestDistance){
            bestDistance = DistanceToGateway[i];
            index_of_best = i;
        } 
    }
    return index_of_best;
}

uint16_t AppRouter::getBestDestination(){
    if (getBestRoute() == ROUTER_TABLE_LENGTH) return 0;
    return DestinationID[getBestRoute()];
}

void AppRouter::resetRoutingTable(){

    for (int i = 0; i<ROUTER_TABLE_LENGTH; i++){
        Rssi[i] = 0;
        DestinationID[i] = 0;
        DistanceToGateway[i] = 0;
    }
}
