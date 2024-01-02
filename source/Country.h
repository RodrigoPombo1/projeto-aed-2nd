//
// Created by rodri on 02/01/2024.
//

#ifndef PROJETO_AED_2ND_COUNTRY_H
#define PROJETO_AED_2ND_COUNTRY_H

#include "City.h"
#include <vector>
#include <string>

class Country {
private:
    std::string name;
    std::vector<City*> cities;
public:
    Country(std::string name);
    std::string getName();
    std::vector<City*> getCities();
    void addCity(City* city);
    std::string toString();
    bool operator==(const Country &other) const;
};


#endif //PROJETO_AED_2ND_COUNTRY_H
