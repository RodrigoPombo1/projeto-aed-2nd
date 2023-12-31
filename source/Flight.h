//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_FLIGHT_H
#define PROJETO_AED_2ND_FLIGHT_H

#include <string>
#include <math.h>
#include "Airport.h"
class Airport;
class Flight {
private:
    Airport *target;
    std::string airline;
    double distance;

    double calculate_distance(Airport *source);
public:
    Flight(Airport *source, Airport *target, std::string airline);
    Airport* getTarget();
    std::string getAirline();
    double getDistance();
};


#endif //PROJETO_AED_2ND_FLIGHT_H
