#include "City.h"

using namespace std;

/// @brief Constructs the city object by attributing it's values
/// complexity: O(1)
/// @param city_name name of the city
/// @param country_name name of the country the city is in
City::City(string city_name, string country_name) {
    this->code = city_name + "-" + country_name;
    this->city_name = city_name;
    this->country_name = country_name;
}

/// @brief Gets the code of a city
/// complexity: O(1)
/// @return code of the city
string City::getCode() {
    return this->code;
}

/// @brief Gets the name of a city
/// complexity: O(1)
/// @return name of the city
string City::getCityName() {
    return this->city_name;
}

/// @brief Gets the name of the country a city is in
/// complexity: O(1)
/// @return name of the country the city is in
string City::getCountryName() {
    return this->country_name;
}

/// @brief Gets the airports in a city
/// complexity: O(1)
/// @return vector with pointers to the airports in the city
vector<Airport*> City::getAirports() {
    return this->airports;
}

/// @brief Adds an airport to a city
/// complexity: O(1)
/// @param airport pointer to the airport
void City::addAirport(Airport* airport) {
    this->airports.push_back(airport);
}

/// @brief Puts all the information about the city into a string
/// complexity: O(1)
/// @return string with all the information about the city
string City::toString() {
    string res = "";
    res += "City: " + this->city_name + " - Country: " + this->country_name;
    return res;
}

/// @brief Defines an operator to compare two cities by their codes (to see if it's the same)
/// complexity: O(1)
/// @param other other city we want to compare with
/// @return boolean value indicating if two cities are the same
bool City::operator==(const City &other) const {
    return this->code == other.code;
}