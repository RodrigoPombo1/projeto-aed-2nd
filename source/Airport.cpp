#include "Airport.h"

using namespace std;

/// @brief Constructs the airport object by attributing it's values
/// complexity: O(1)
/// @param code code of the airport
/// @param name name of the airport
/// @param city city of the airport
/// @param country country of the airport
/// @param latitude latitude of the airport
/// @param longitude longitude of the airport
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

/// @brief Gets the code of an airport
/// complexity: O(1)
/// @return code of the airport
string Airport::getCode() {
    return this->code;
}

/// @brief Gets the name of an airport
/// complexity: O(1)
/// @return name of the airport
string Airport::getName() {
    return this->name;
}

/// @brief Gets the city of an airport
/// complexity: O(1)
/// @return city of the airport
string Airport::getCity() {
    return this->city;
}

/// @brief Gets the country of an airport
/// complexity: O(1)
/// @return country of the airport
string Airport::getCountry() {
    return this->country;
}

/// @brief Gets the latitude of an airport
/// complexity: O(1)
/// @return latitude of the airport
double Airport::getLatitude() {
    return this->latitude;
}

/// @brief Gets the longitude of an airport
/// complexity: O(1)
/// @return longitude of the airport
double Airport::getLongitude() {
    return this->longitude;
}

/// @brief Gets the flight leaving from an airport
/// complexity: O(1)
/// @return vector with the flights leaving from the airport
vector<Flight> Airport::getFlights() {
    return this->flights;
}

/// @brief Gets pointers to flights leaving an airport
/// complexity: O(n) (n = number of flights)
/// @return vector with pointers to the flights leaving the airport
std::vector<Flight*> Airport::getFlightsPointer() {
    vector<Flight*> flightsPointer;
    for (Flight &flight : this->flights) {
        flightsPointer.push_back(&flight);
    }
    return flightsPointer;
}

/// @brief Adds a flight to the flights leaving an airport
/// complexity: O(1)
/// @param flight flight we want to add
void Airport::addFlight(Flight flight) {
    this->flights.push_back(flight);
}

/// @brief Puts all the information about an airport into a string
/// complexity: O(1)
/// @return string with all the information about the airport
string Airport::toString() {
    return this->code + " " + this->name + " " + this->city
    + " " + this->country + " " + to_string(this->latitude)
    + " " + to_string(this->longitude);
}

/// @brief Defines an operator to compare two airports by their codes (to see if it's the same)
/// complexity: O(1)
/// @param other other airport we want to compare with
/// @return boolean value indicating if two airports are the same
bool Airport::operator==(const Airport &other) const {
    return this->code == other.code;
}