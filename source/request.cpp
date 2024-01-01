//
// Created by rodri on 30/12/2023.
//

#include "request.h"

using namespace std;

request::request() {
    csvReader = csv_reader();
    this->airports = csvReader.getAirports();
    this->airlines = csvReader.getAirlines();
}

std::vector<Flight> request::get_flights_from_airport_pointer(Airport *airport_pointer) {
    return airport_pointer->getFlights();
}

Airport* request::get_airport_pointer_from_airport_code(std::string airport_code) {
    if (this->airports.find(airport_code) == this->airports.end()) {
        return nullptr;
    }
    return &this->airports.at(airport_code);
}

int request::get_total_number_of_airports() {
    return this->airports.size();
}

int request::get_total_number_of_flights_from_all_airports() {
    int total_number_of_flights = 0;
    for (auto &airport : this->airports) {
        total_number_of_flights += airport.second.getFlights().size();
    }
    return total_number_of_flights;
}

vector<pair<int, Airport>> request::get_airports_with_top_air_traffic_capacity(int top_number_of_airports) {
    multimap<int, Airport> airports_by_air_traffic_capacity;
    for (auto &airport : this->airports) {
        airports_by_air_traffic_capacity.insert({airport.second.getFlights().size(), airport.second});
    }
    vector<pair<int, Airport>> res;
    int i = 0;
    for (auto it = airports_by_air_traffic_capacity.rbegin();
            it != airports_by_air_traffic_capacity.rend(); it++) {
        if (i == top_number_of_airports) {
            break;
        }
        res.push_back({it->first, it->second});
        i++;
    }
    return res;
}