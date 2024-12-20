#include "request.h"

using namespace std;

/// @brief Gets all the airports, airlines and cities
/// complexity: O(n1+m1) + O(n2+m2) + O(n3+m3) (check csv_reader class)
request::request() {
    csvReader = csv_reader();
    this->airports = csvReader.getAirports();
    this->airlines = csvReader.getAirlines();
    this->cities = csvReader.getCities();
    this->countries = csvReader.getCountries();
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

/// @brief Gets pointers to airports with the coordinates given
/// complexity: O(n) (n = number of airports)
/// @param latitude latitude of the airport
/// @param longitude longitude of the airport
/// @return vector with pointer to the airports with the coordinates given
vector<Airport*> request::get_vector_airport_pointer_from_geographical_coordinates(double latitude, double longitude) {
    vector<Airport*> res;
    double min_airport_distance_difference = std::numeric_limits<double>::max();
    for (auto &airport : this->airports) {
        double current_airport_distance_difference = calculate_distance(airport.second.getLatitude(),
                                                                        airport.second.getLongitude(),
                                                                        latitude, longitude);
        if (current_airport_distance_difference < min_airport_distance_difference) {
            res.clear();
            res.push_back(&airport.second);
            min_airport_distance_difference = current_airport_distance_difference;
        }
        else if (current_airport_distance_difference == min_airport_distance_difference) {
            res.push_back(&airport.second);
        }
    }
    return res;
}

/// @brief Calculates the distance between two coordinates by using their latitude and longitude
/// complexity: O(1)
/// @param latitude1 latitude of the first coordinate
/// @param longitude1 longitude of the first coordinate
/// @param latitude2 latitude of the second coordinate
/// @param longitude2 longitude of the second coordinate
/// @return distance between the two coordinates
double request::calculate_distance(double latitude1, double longitude1, double latitude2, double longitude2) {
    double dLat = (latitude2 - latitude1) * M_PI / 180.0;
    double dLon = (longitude2 - longitude1) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(latitude1) * cos(latitude2);

    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

/// @brief Gets pointers to the airports in a city
/// complexity: O(n) (n = number of airports in the city)
/// @param city city we want the airports from
/// @param country country of the city
/// @return vector with pointers to the airports in the city
vector<Airport*> request::get_vector_airport_pointer_from_city(string city, string country) {
    vector<Airport*> res;
    string city_code = city + "-" + country;
    if (this->cities.find(city_code) == this->cities.end()) {
        return res;
    }
    City current_city = this->cities.at(city_code);
    vector<Airport*> current_city_airports = current_city.getAirports();
    for (Airport* &airport : current_city_airports) {
        res.push_back(airport);
    }
    return res;
}

/// @brief Gets a pointer to a city
/// complexity: O(1)
/// @param city_code code of the city
/// @return pointer to the city
City* request::get_city_pointer_from_city_code(string city_code) {
    if (this->cities.find(city_code) == this->cities.end()) {
        return nullptr;
    }
    return &this->cities.at(city_code);
}