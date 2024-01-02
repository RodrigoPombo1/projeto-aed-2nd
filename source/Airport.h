//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_AIRPORT_H
#define PROJETO_AED_2ND_AIRPORT_H

#include <string>
#include <vector>
#include "Flight.h"
class Flight;

class Airport {
private:
    std::string code;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;
    std::vector<Flight> flights;
public:
    Airport(std::string code, std::string name, std::string city, std::string country,
            double latitude, double longitude);
    std::string getCode();
    std::string getName();
    std::string getCity();
    std::string getCountry();
    double getLatitude();
    double getLongitude();
    std::vector<Flight> getFlights();
    std::vector<Flight*> getFlightsPointer();
    void addFlight(Flight flight);
    std::string toString();

    bool operator==(const Airport &other) const;
};

#endif //PROJETO_AED_2ND_AIRPORT_H
