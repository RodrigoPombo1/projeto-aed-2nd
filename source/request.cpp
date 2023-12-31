//
// Created by rodri on 30/12/2023.
//

#include "request.h"

request::request() {
    csvReader = csv_reader();
    this->airports = csvReader.getAirports();
    this->airlines = csvReader.getAirlines();
}