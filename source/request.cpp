//
// Created by rodri on 30/12/2023.
//

#include "request.h"

using namespace std;

/// @brief Gets all the airports and airlines
/// complexity: O(n1+m1) + O(n2+m2) + O(n3+m3) (check csv_reader class)
request::request() {
    csvReader = csv_reader();
    this->airports = csvReader.getAirports();
    this->airlines = csvReader.getAirlines();
}

/// @brief Gets the flights leaving from an airport using it's pointer
/// complexity: O(1)
/// @param airport_pointer pointer to the airport
/// @return vector with the flights leaving from the airport
std::vector<Flight> request::get_flights_from_airport_pointer(Airport *airport_pointer) {
    return airport_pointer->getFlights();
}

/// @brief Gets pointer to an aiport using it's code
/// complexity: O(1)
/// @param airport_code code of the airport
/// @return pointer to the airport
Airport* request::get_airport_pointer_from_airport_code(std::string airport_code) {
    if (this->airports.find(airport_code) == this->airports.end()) {
        return nullptr;
    }
    return &this->airports.at(airport_code);
}

/// @brief Gets the total number of airports
/// complexity: O(1)
/// @return total number of airports
int request::get_total_number_of_airports() {
    return this->airports.size();
}

/// @brief Gets the total number of flights
/// complexity: O(n) (n = number of airports)
/// @return total number of flights
int request::get_total_number_of_flights_from_all_airports() {
    int total_number_of_flights = 0;
    for (auto &airport : this->airports) {
        total_number_of_flights += airport.second.getFlights().size();
    }
    return total_number_of_flights;
}

/// @brief Gets the airports with the top air traffic capacity limited by a number chosen (how many the user wants to see)
/// complexity: O(n*log(n)) (n = number of airports)
/// @param top_number_of_airports number of airports the user wants to see
/// @return vector of pairs with the airport and it's air traffic capacity
vector<pair<int, Airport>> request::get_airports_with_top_air_traffic_capacity(int top_number_of_airports) {
    multimap<int, Airport> airports_by_air_traffic_capacity;
    for (auto &airport : this->airports) {
        airports_by_air_traffic_capacity.insert({airport.second.getFlights().size(), airport.second});
    }
    vector<pair<int, Airport>> res;
    int i = 0;
    for (auto it = airports_by_air_traffic_capacity.rbegin();
            it != airports_by_air_traffic_capacity.rend(); it++) {
        if (i == top_number_of_airports) {
            break;
        }
        res.push_back({it->first, it->second});
        i++;
    }
    return res;
}

/// @brief Gets pointer to an airline using it's code
/// complexity: O(1)
/// @param airline_code code of the airline
/// @return pointer to the airline
Airline* request::get_airline_pointer_from_airline_code(std::string airline_code) {
    if (this->airlines.find(airline_code) == this->airlines.end()) {
        return nullptr;
    }
    return &this->airlines.at(airline_code);
}

/// @brief Gets all the flights from an airline
/// complexity: O(n*m) (n = number of airports, m = maximum number of flights of the airline leaving an airport )
/// @param airline_pointer pointer to the airline
/// @return total number of flights of the airline
int request::get_number_flights_from_airline_pointer(Airline *airline_pointer) {
    int total_number_of_flights = 0;
    string airline_code = airline_pointer->getCode();
    for (auto &airport : this->airports) {
        vector<Flight> flights_from_airport = airport.second.getFlights();
        for (auto &flight : flights_from_airport) {
            if (flight.getAirline() == airline_code) {
                total_number_of_flights++;
            }
        }
    }
    return total_number_of_flights;
}

/// @brief Gets the flight options for the wanted sources, targets and airlines
/// complexity: O(n+m+s+d) (n = number of airports, m = maximum number of flights leaving an airport, s = number of sources, t = number of targets)
/// @param airport_sources vector with all airport soyrces we want to search
/// @param airport_destinations vector with all airport targets we ant to search
/// @param airlines vector with all teh airlines we want to search
/// @return pair of vector with the flight and a pointer to the airport of the best flight options
pair<vector<Flight>, Airport*> request::get_flights_best_option_bfs(vector<Airport*> airport_sources,
                                                                     vector<Airport*> airport_destinations,
                                                                     vector<Airline*> airlines) {
    bool all_airlines_to_consider = false;
    for (Airline* &current_airline : airlines) {
        if (current_airline == nullptr) {
            all_airlines_to_consider = true;
            break;
        }
    }

    // declaration of a map with the airlines to consider, so we can have constant lookup time
    unordered_map<string, Airline*> airlines_to_consider;

    if (!all_airlines_to_consider) {
        // initialization of the airlines to consider
        for (Airline* &current_airline : airlines) {
            airlines_to_consider.insert({current_airline->getCode(), current_airline});
        }
    }
    else {
        // initialization of the airlines to consider
        for (auto &airline : this->airlines) {
            airlines_to_consider.insert({airline.second.getCode(), &airline.second});
        }
    }

    // declaration of the nodes that will be used in this bfs
    struct airport_node {
        Airport *airport;
        bool visited;
        bool is_destination;
        Flight *predecessor_flight;
        airport_node *predecessor_airport_node;
    };
    unordered_map<string, airport_node> airport_nodes;

    // initialization of the nodes
    for (auto &airport : this->airports) {
        airport_node current_node;
        current_node.airport = &airport.second;
        current_node.visited = false;
        current_node.is_destination = false;
        current_node.predecessor_flight = nullptr;
        current_node.predecessor_airport_node = nullptr;
        string airport_code = airport.first;
        airport_nodes.insert({airport_code, current_node});
    }

    // set the nodes that are destinations
    for (Airport* &airport : airport_destinations) {
        airport_node current_node = airport_nodes.at(airport->getCode());
        current_node.is_destination = true;
        airport_nodes.at(airport->getCode()) = current_node;
    }

    // enqueueing the source nodes
    queue<string> airport_nodes_string_code_queue;
    for (Airport* &airport : airport_sources) {
        airport_node current_node = airport_nodes.at(airport->getCode());
        current_node.visited = true;
        string current_node_code = airport->getCode();
        airport_nodes.at(current_node_code) = current_node;
        airport_nodes_string_code_queue.push(current_node_code);
    }

    vector<Flight> flights;

    while (!airport_nodes_string_code_queue.empty()) {
        string current_node_code = airport_nodes_string_code_queue.front();
        airport_nodes_string_code_queue.pop();

        airport_node* current_node = &airport_nodes.at(current_node_code);
        if (current_node->is_destination) {
            Flight *flight_predecessor_to_current_node = current_node->predecessor_flight;
            while (flight_predecessor_to_current_node != nullptr) {
                // add the flight to the vector of flights
                flights.push_back(*flight_predecessor_to_current_node);
                // make the predecessor node and flight the current node and flight
                current_node = current_node->predecessor_airport_node;
                flight_predecessor_to_current_node = current_node->predecessor_flight;
            }
            vector<Flight> flights_reversed(flights.rbegin(), flights.rend());
            pair<vector<Flight>, Airport*> res(flights_reversed, current_node->airport);
            return res;
        }

        int current_node_airport_size_flight_vector = current_node->airport->getFlights().size();
        for (int i = 0; i < current_node_airport_size_flight_vector; i++) {
            Flight *current_flight = current_node->airport->getFlightsPointer()[i];
            // check if the airline is one of the airlines we want to consider
            if (airlines_to_consider.find(current_flight->getAirline()) == airlines_to_consider.end()) {
                continue;
            }

            Airport *current_flight_destination_airport = current_flight->getTarget();
            airport_node *current_flight_destination_airport_node =
                    &airport_nodes.at(current_flight_destination_airport->getCode());
            if (!current_flight_destination_airport_node->visited) {
                current_flight_destination_airport_node->visited = true;
                current_flight_destination_airport_node->predecessor_flight = current_flight;
                current_flight_destination_airport_node->predecessor_airport_node = current_node;
                airport_nodes_string_code_queue.push(current_flight_destination_airport_node->airport->getCode());
            }
        }
    }

    // case where it isn't possible to reach the destination(s) from the source(s)
    pair<vector<Flight>, Airport*> res(flights, nullptr);
    return res;
}