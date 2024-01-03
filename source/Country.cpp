#include "Country.h"

using namespace std;

/// @brief Constructs the country object by attributing it's values
/// complexity: O(1)
/// @param name name of the country
Country::Country(string name) {
    this->name = name;
}

/// @brief Gets the name of a country
/// complexity: O(1)
/// @return name of the country
string Country::getName() {
    return this->name;
}

/// @brief Gets the cities in a country
/// complexity: O(1)
/// @return vector with pointers to the cities in the country
vector<City*> Country::getCities() {
    return this->cities;
}

/// @brief Adds a city to a country
/// complexity: O(1)
/// @param city pointer to the city
void Country::addCity(City* city) {
    this->cities.push_back(city);
}

/// @brief Puts all the information about a country into a string
/// complexity: O(1)
/// @return string with all the information about the country
string Country::toString() {
    string res = "";
    res += "Country: " + this->name;
    return res;
}

/// @brief Defines an operator to compare two countries by their names (to see if it's the same)
/// complexity: O(1)
/// @param other other country we want to compare with
/// @return boolean value indicating if two countries are the same
bool Country::operator==(const Country &other) const {
    return this->name == other.name;
}