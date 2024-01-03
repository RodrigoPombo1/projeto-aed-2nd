#include "Airline.h"

using namespace std;

/// @brief Constructs the airline object by attributing it's values
/// complexity: O(1)
/// @param code code of the airline
/// @param name name of the airline
/// @param callsign call sign of the airline
/// @param country country of the airline
Airline::Airline(string code, string name, string callsign, string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

/// @brief Gets the code of an airline
/// complexity: O(1)
/// @return code of the airline
string Airline::getCode() {
    return this->code;
}

/// @brief Gets the name of an airline
/// complexity: O(1)
/// @return name of the airline
string Airline::getName() {
    return this->name;
}

/// @brief Gets the call sign of an airline
/// complexity: O(1)
/// @return call sign of the airline
string Airline::getCallsign() {
    return this->callsign;
}

/// @brief Gets the country of an airline
/// complexity: O(1)
/// @return country of the airline
string Airline::getCountry() {
    return this->country;
}