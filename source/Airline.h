//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_AIRLINE_H
#define PROJETO_AED_2ND_AIRLINE_H

#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    std::string getCode();
    std::string getName();
    std::string getCallsign();
    std::string getCountry();
};


#endif //PROJETO_AED_2ND_AIRLINE_H
