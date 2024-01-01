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