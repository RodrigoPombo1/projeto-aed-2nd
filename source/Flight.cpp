//
// Created by rodri on 30/12/2023.
//

#include "Flight.h"

/// @brief Constructs the airline object by attributing it's values
/// complexity: O(1)
/// @param source source of the flight
/// @param target target of the flight
/// @param airline airline of the flight
Flight::Flight(Airport *source, Airport *target, std::string airline) : target(target) {
    this->airline = airline;
    this->distance = calculate_distance(source);
}

/// @brief Gets a pointer to the target of a flight
/// complexity: O(1)
/// @return pointer to the target of the flight
Airport* Flight::getTarget() {
    return this->target;
}

/// @brief Gets the airline of a flight
/// complexity: O(1)
/// @return airline of the flight
std::string Flight::getAirline() {
    return this->airline;
}

/// @brief Gets the distance of a flight
/// complexity: O(1)
/// @return distance of the flight
double Flight::getDistance() {
    return this->distance;
}

/// @brief Calculates the distance of a flight using the latitude and longitude of it's source and it's target
/// complexity: O(1)
/// @return distance between the target and source airports
double Flight::calculate_distance(Airport* source) {
    double lat1 = source->getLatitude();
    double lon1 = source->getLongitude();
    double lat2 = this->target->getLatitude();
    double lon2 = this->target->getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/// @brief Puts the name and the code of the target airport of the flight, the airline of the flight and the distance of the flight into a string
/// complexity: O(1)
/// @return string with name and code of target airport, airline and distance of the flight
std::string Flight::toString() {
    return "destination airport: " + this->target->getName() + " (" + this->target->getCode() + ")"
        + "\nairline: " + this->airline + "\ndistance: " + std::to_string(this->distance);
}