//
// Created by rodri on 30/12/2023.
//

#include "Airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country,
                 double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
    this->flights = vector<Flight>();
}

string Airport::getCode() {
    return this->code;
}

string Airport::getName() {
    return this->name;
}

string Airport::getCity() {
    return this->city;
}

string Airport::getCountry() {
    return this->country;
}

double Airport::getLatitude() {
    return this->latitude;
}

double Airport::getLongitude() {
    return this->longitude;
}

vector<Flight> Airport::getFlights() {
    return this->flights;
}

void Airport::addFlight(Flight flight) {
    this->flights.push_back(flight);
}

bool Airport::operator==(const Airport &other) const {
    return this->code == other.code;
}