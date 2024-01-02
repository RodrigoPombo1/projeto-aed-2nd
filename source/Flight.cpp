//
// Created by rodri on 30/12/2023.
//

#include "Flight.h"

Flight::Flight(Airport *source, Airport *target, std::string airline) : target(target) {
    this->airline = airline;
    this->distance = calculate_distance(source);
}

Airport* Flight::getTarget() {
    return this->target;
}

std::string Flight::getAirline() {
    return this->airline;
}

double Flight::getDistance() {
    return this->distance;
}

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

std::string Flight::toString() {
    return "destination airport: " + this->target->getName() + " (" + this->target->getCode() + ")"
        + "\nairline: " + this->airline + "\ndistance: " + std::to_string(this->distance);
}