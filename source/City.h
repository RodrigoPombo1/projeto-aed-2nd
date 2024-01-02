//
// Created by rodri on 02/01/2024.
//

#ifndef PROJETO_AED_2ND_CITY_H
#define PROJETO_AED_2ND_CITY_H

#include <string>
#include <vector>
#include "Airport.h"

class City {
private:
    std::string code; // = name_name-country_name
    std::string city_name;
    std::string country_name;
    std::vector<Airport*> airports;
public:
    City(std::string city_name, std::string country_name);
    std::string getCode();
    std::string getCityName();
    std::string getCountryName();
    std::vector<Airport*> getAirports();
    void addAirport(Airport* airport);
    std::string toString();

    bool operator==(const City &other) const;
};


#endif //PROJETO_AED_2ND_CITY_H
