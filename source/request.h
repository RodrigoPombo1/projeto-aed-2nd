//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_REQUEST_H
#define PROJETO_AED_2ND_REQUEST_H

#include <vector>
#include <map>
#include <queue>
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
    int get_total_number_of_airports();
    int get_total_number_of_flights_from_all_airports();
    std::vector<std::pair<int, Airport>> get_airports_with_top_air_traffic_capacity(int top_number_of_airports);
    Airline* get_airline_pointer_from_airline_code(std::string airline_code);
    int get_number_flights_from_airline_pointer(Airline *airline_pointer);
    std::pair<std::vector<Flight>, Airport*> get_flights_best_option_bfs(std::vector<Airport*> source,
                                                                     std::vector<Airport*> destination,
                                                                     std::vector<Airline*> airline);
};

#endif //PROJETO_AED_2ND_REQUEST_H
