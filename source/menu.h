//
// Created by rodri on 30/12/2023.
//

#ifndef PROJETO_AED_2ND_MENU_H
#define PROJETO_AED_2ND_MENU_H

#include "request.h"
#include <string>
#include <iostream>
#include <vector>

class menu {
private:
    request Request;
    bool go_back_to_main_menu;
    // functions common to all menus
    int print_menu_and_get_choice_input(std::string current_selection, std::vector<std::string> options,
                                        bool is_main_menu = false);
    int print_menu_and_get_number_input(std::string current_selection);
    std::string print_menu_and_get_string_input(std::string current_selection);
    void print_separator();
    int print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results);

    // main menu
    void main_menu();
    void statistics_of_the_network();
    void best_flight_option();

    // best_flight_option
    void best_flight_option_get_airport_source();
//    void best_flight_option_get_city_source();
//    void best_flight_option_get_geographical_coordinates_source();
    void best_flight_option_select_airline(std::vector<Airport*> vector_airport_pointer, std::string source_code);
    void best_flight_option_get_airline(std::vector<Airport*> vector_airport_pointer, std::string source_code);
    void best_flight_option_select_destination(std::vector<Airport*> vector_airport_pointer, std::string source_code, Airline *airline_pointer);
    void best_flight_option_get_airport_destination(std::vector<Airport*> vector_airport_pointer, std::string source_code, Airline *airline_pointer);
//    void best_flight_option_get_city_destination(std::vector<Airport*> vector_airport_pointer, std::string source_code, Airline *airline_pointer);
//    void best_flight_option_get_geographical_coordinates_destination(std::vector<Airport*> vector_airport_pointer,
//                                                                     std::string source_code,
//                                                                     Airline *airline_pointer);
    void best_flight_option_airport_to_airport(std::vector<Airport*> vector_airport_pointer, std::string source_code,
                                               Airline *airline_pointer, std::vector<Airport*> vector_airport_destinations_pointer, std::string destination_code);
    // statistics of the network
    void global_statistics();
    void statistics_for_a_specific_airport_get_airport();
    void statistics_for_a_specific_airport(Airport *airport_pointer);
    void statistics_for_a_specific_city();
    void statistics_for_a_specific_airline_get_airline();
    void statistics_for_a_specific_airline(Airline *airline_pointer);

    void get_airline_to_filter_flights(std::vector<Flight> flights);

    // global statistics
    void get_total_number_of_airports();
    void get_total_number_of_available_flights();
    void get_airports_with_top_air_traffic_capacity();
    void get_airports_that_are_essential_to_the_network();
    void get_maximum_trip_and_corresponding_pair_of_source_destination_airports();

    // statistics for a specific airport/city
    void any_airline_or_a_specific_airline();

    void get_specific_airline();

    // statistics for a specific airport/city/airline
    void get_either_airports_cities_or_airlines_to_consider();
    void get_maximum_number_of_stops();

    // get airline/city/airport/geographical coordinates
    void get_airline();
    void get_city();
    void get_airport();
    void get_geographical_coordinates();
public:
    menu();
};

#endif //PROJETO_AED_2ND_MENU_H
