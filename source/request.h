//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_REQUEST_H
#define PROJETO_AED_2ND_REQUEST_H

#include <vector>
#include "csv_reader.h"

class request {
private:
    std::vector<Airport> airports;
    std::vector<Airline> airlines;
    csv_reader csvReader;
public:
    request();

};

#endif //PROJETO_AED_2ND_REQUEST_H
