//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_REQUEST_H
#define PROJETO_AED_2ND_REQUEST_H

#include <vector>
#include "csv_reader.h"

class request {
private:
    std::unordered_map<std::string, Airport> airports;
    std::unordered_map<std::string, Airline> airlines;
    csv_reader csvReader;
    // functions used internally by request

public:
    request();

    // functions called by menu
    std::vector<Flight> get_flights_from_airport_pointer(Airport *airport_pointer);
    Airport* get_airport_pointer_from_airport_code(std::string airport_code);
};

#endif //PROJETO_AED_2ND_REQUEST_H
