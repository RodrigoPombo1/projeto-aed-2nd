//
// Created by rodri on 30/12/2023.
//

#include "csv_reader.h"

using namespace std;

/// @brief Gets all the information from the csv files
/// complexity: O(n1+m1) + O(n2+m2) + O(n3+m3)
csv_reader::csv_reader() {
    this->airlines_csv_file_name = "data/airlines.csv";
    this->airports_csv_file_name = "data/airports.csv";
    this->flights_csv_file_name = "data/flights.csv";

    read_airlines_csv();
    read_airports_csv();
    read_flights_csv();
}

/// @brief Reads the airlines csv file and gets all the information about each airline
/// complexity: O(n1*m1) (n1 = number of lines in the csv file, m1 = number of cells in each line)
void csv_reader::read_airlines_csv() {
    ifstream file(this->airlines_csv_file_name);
    string line;
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            vector<string> airline_elements;
            stringstream current_line_string_stream(line);
            string airline_element;
            while (getline(current_line_string_stream, airline_element, ',')) {
                airline_elements.push_back(airline_element);
            }
            Airline airline(airline_elements[0],airline_elements[1],
                            airline_elements[2],airline_elements[3]);
            this->airlines.insert({airline.getCode(), airline});
        }
        file.close();
    }
}

/// @brief Reads the airports csv file and gets all the information about each airport
/// complexity: O(n2*m2) (n2 = number of lines in the csv file, m2 = number of cells in each line)
void csv_reader::read_airports_csv() {
    ifstream file(this->airports_csv_file_name);
    string line;
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            vector<string> airport_elements;
            stringstream current_line_string_stream(line);
            string airport_element;
            while (getline(current_line_string_stream, airport_element, ',')) {
                airport_elements.push_back(airport_element);
            }
            Airport airport(airport_elements[0],airport_elements[1],
                            airport_elements[2],airport_elements[3],
                            stod(airport_elements[4]),stod(airport_elements[5]));
            this->airports.insert({airport.getCode(), airport});
        }
        file.close();
    }
}

/// @brief Reads the airlines csv file and gets all the information about each flight
/// complexity: O(n3*m3) (n3 = number of lines in the csv file, m3 = number of cells in each line)
void csv_reader::read_flights_csv() {
    ifstream file(this->flights_csv_file_name);
    string line;
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            vector<string> flight_elements;
            stringstream current_line_string_stream(line);
            string flight_element;
            while (getline(current_line_string_stream, flight_element, ',')) {
                flight_elements.push_back(flight_element);
            }
            Airport *source_airport = get_airport_pointer_by_code(flight_elements[0]);
            Airport *destination_airport = get_airport_pointer_by_code(flight_elements[1]);
            Flight flight(source_airport, destination_airport, flight_elements[2]);
            source_airport->addFlight(flight);
        }
        file.close();
    }
}

/// @brief Gets the pointer to the airport wanted by it's code
/// complexity: O(1)
/// @param code code of the airport we want the pointer to
/// @return pointer to the airport
Airport* csv_reader::get_airport_pointer_by_code(string code) {
    try {
        Airport *airport_pointer = &this->airports.at(code);
        return airport_pointer;
    } catch (std::out_of_range &e) {
        return nullptr;
    }
}

/// @brief Gets all the airports
/// complexity: O(1)
/// @return map with all airports
std::unordered_map<std::string, Airport> csv_reader::getAirports() {
    return this->airports;
}

/// @brief Gets all the airlines
/// complexity: O(1)
/// @return map with all airlines
std::unordered_map<std::string, Airline> csv_reader::getAirlines() {
    return this->airlines;
}
