//
// Created by rodri on 30/12/2023.
//

#include "Airline.h"

using namespace std;

Airline::Airline(string code, string name, string callsign, string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

string Airline::getCode() {
    return this->code;
}

string Airline::getName() {
    return this->name;
}

string Airline::getCallsign() {
    return this->callsign;
}

string Airline::getCountry() {
    return this->country;
}