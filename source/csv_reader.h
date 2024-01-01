//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_CSV_READER_H
#define PROJETO_AED_2ND_CSV_READER_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

class csv_reader {
private:
    std::string airlines_csv_file_name;
    std::string airports_csv_file_name;
    std::string flights_csv_file_name;
    void read_airlines_csv();
    void read_airports_csv();
    void read_flights_csv();
    std::unordered_map<std::string, Airport> airports;
    std::unordered_map<std::string, Airline> airlines;
    Airport* get_airport_pointer_by_code(std::string code);
public:
    csv_reader();
    std::unordered_map<std::string, Airport> getAirports();
    std::unordered_map<std::string, Airline> getAirlines();
};

#endif //PROJETO_AED_2ND_CSV_READER_H
