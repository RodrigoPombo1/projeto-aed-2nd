//
// Created by rodri on 02/01/2024.
//

#include "Country.h"

using namespace std;

Country::Country(string name) {
    this->name = name;
}

string Country::getName() {
    return this->name;
}

vector<City*> Country::getCities() {
    return this->cities;
}

void Country::addCity(City* city) {
    this->cities.push_back(city);
}

string Country::toString() {
    string res = "";
    res += "Country: " + this->name;
    return res;
}

bool Country::operator==(const Country &other) const {
    return this->name == other.name;
}