//
// Created by rodri on 02/01/2024.
//

#include "City.h"

using namespace std;

City::City(string city_name, string country_name) {
    this->code = city_name + "-" + country_name;
    this->city_name = city_name;
    this->country_name = country_name;
}

string City::getCode() {
    return this->code;
}

string City::getCityName() {
    return this->city_name;
}

string City::getCountryName() {
    return this->country_name;
}

vector<Airport*> City::getAirports() {
    return this->airports;
}

void City::addAirport(Airport* airport) {
    this->airports.push_back(airport);
}

string City::toString() {
    string res = "";
    res += "City: " + this->city_name + " - Country: " + this->country_name;
    return res;
}

bool City::operator==(const City &other) const {
    return this->code == other.code;
}