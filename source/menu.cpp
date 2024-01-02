//
// Created by rodri on 30/12/2023.
//

#include "menu.h"

using namespace std;

int menu::print_menu_and_get_choice_input(string current_selection, vector<string> options, bool is_main_menu) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
        if (!is_main_menu) {
            cout << "0. Go back to previous menu\n";
            cout << "-1. Go back to main menu\n";
        } else {
            cout << "0. Exit\n";
        }
        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= (int) options.size() && !is_main_menu) {
            valid_input = true;
        } else if (input >= 0 && input <= (int) options.size() && is_main_menu) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

void menu::print_separator() {
    cout << "---------------------------------------------------------------------------\n";
}

int menu::print_menu_and_get_number_input(string current_selection) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a number above 1" << " and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

string menu::print_menu_and_get_string_input(string current_selection) {
    string input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        cout << "Enter a string and press enter\n";

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input != "") {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

int menu::print_result_and_get_choice_input(std::string current_selection, std::vector<std::string> results) {
    int input;
    bool valid_input = false;
    while (!valid_input) {
        cout << current_selection << endl;

        this->print_separator();

        for (int i = 0; i < results.size(); i++) {
            cout << i + 1 << ". " << results[i] << endl;
        }

        this->print_separator();

        cout << "0. Go back to previous menu\n";
        cout << "-1. Go back to main menu\n";

        this->print_separator();

        cout << "Chose one of the options above by entering the corresponding number and press enter\n";
        cin >> input;
        if (input >= -1 && input <= 0) {
            valid_input = true;
        } else {
            cout << "Invalid input, please try again\n";
        }
    }
    return input;
}

menu::menu() {
    Request = request();
    this->main_menu();
}

void menu::main_menu() {
    while (true) {
        this->go_back_to_main_menu = false;
        string current_menu = "Main menu";
        vector<string> options = {"Statistics of the network", "Best flight option"};
        int input = this->print_menu_and_get_choice_input(current_menu, options, true);
        switch (input) {
            case 0:
                return;
            case 1:
                this->statistics_of_the_network();
                break;
            case 2:
                this->best_flight_option();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::statistics_of_the_network() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics of the network";
        vector<string> options = {"Global statistics", "Statistics for a specific airport",
                                  "Statistics for a specific city", "Statistics for a specific airline"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->global_statistics();
                break;
            case 2:
                this->statistics_for_a_specific_airport_get_airport();
                break;
            case 3:
                this->statistics_for_a_specific_city_get_city();
                break;
            case 4:
                this->statistics_for_a_specific_airline_get_airline();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::global_statistics() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Global statistics";
        vector<string> options = {"Total number of airports", "Total number of available flights",
                                  "Airports with top air traffic capacity",
                                  "Airports that are essential to the network",
                                  "Maximum trip and corresponding pair of source-destination airports"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->get_total_number_of_airports();
                break;
            case 2:
                this->get_total_number_of_available_flights();
                break;
            case 3:
                this->get_airports_with_top_air_traffic_capacity();
                break;
            case 4:
//                this->get_airports_that_are_essential_to_the_network();
                break;
            case 5:
//                this->get_maximum_trip_and_corresponding_pair_of_source_destination_airports();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::statistics_for_a_specific_airport_get_airport() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistic for a specific airport - enter airport code";
        string airport_code = this->print_menu_and_get_string_input(current_menu);
        if (airport_code == "0") {
            return;
        } else if (airport_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airport *airport_pointer = this->Request.get_airport_pointer_from_airport_code(airport_code);
            if (airport_pointer == nullptr) {
                cout << "Airport with code " << airport_code << " does not exist\n";
            } else {
                this->statistics_for_a_specific_airport(airport_pointer);
            }
        }
    }
}

void menu::statistics_for_a_specific_airport(Airport *airport_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistic for a specific airport - " + airport_pointer->getCode();
        vector<string> options = {"Any airline", "A specific airline"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                vector<Flight> flights_from_airport = Request.get_flights_from_airport_pointer(airport_pointer);
                string res = "There are " + to_string(flights_from_airport.size())
                             + " flights from this airport in total.";
                vector<string> vec_res = {res};
                int input2 = this->print_result_and_get_choice_input(current_menu, vec_res);
                switch (input2) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
                break;
        }
        if (input == 2) {
            vector<Flight> flights_from_airport2 = Request.get_flights_from_airport_pointer(airport_pointer);
            this->get_airline_to_filter_flights(flights_from_airport2);
            break;
        }
    }
}

void menu::get_airline_to_filter_flights(std::vector<Flight> flights) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Please enter airline code";
        string input = this->print_menu_and_get_string_input(current_menu);
        if (input == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        else if (input == "0") {
            return;
        }
        else {
            vector<int> index_to_remove;
            for (int i = 0; i < flights.size(); i++) {
                if (flights[i].getAirline() == input) {
                    index_to_remove.push_back(i);
                }
            }
            for (int i = index_to_remove.size(); i >= 0; i--) {
                flights.erase(flights.begin() + i);
            }
            if (flights.empty()) {
                string current_selection = "No flights found.";
                vector<string> res = {"No flights found for this airport for this airline."};
                int input = this->print_result_and_get_choice_input(current_selection, res);
                switch(input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
            else {
                string res = "There are " + to_string(flights.size()) + " flights from this airport with this airline";
                vector<string> vec_res = {res};
                int input = this->print_result_and_get_choice_input(current_menu, vec_res);
                switch(input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
        }
    }
}

void menu::get_total_number_of_airports() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Total number of airports";
        vector<string> res = {"There are " + to_string(Request.get_total_number_of_airports()) + " airports in total."};
        int input = this->print_result_and_get_choice_input(current_menu, res);
        switch(input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::get_total_number_of_available_flights() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Total number of available flights";
        vector<string> res = {"There are " + to_string(Request.get_total_number_of_flights_from_all_airports())
                              + " flights in total from all airports."};
        int input = this->print_result_and_get_choice_input(current_menu, res);
        switch(input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::get_airports_with_top_air_traffic_capacity() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Airports with top air traffic capacity - enter number of airports to show";
        int input = this->print_menu_and_get_number_input(current_menu);
        if (input == -1) {
            this->go_back_to_main_menu = true;
            return;
        }
        else if (input == 0) {
            return;
        }
        else {
            vector<pair<int, Airport>> top_airports = Request.get_airports_with_top_air_traffic_capacity(input);
            if (top_airports.empty()) {
                string current_selection = "No airports found.";
                vector<string> res = {"No airports found with this number of flights."};
                int input = this->print_result_and_get_choice_input(current_selection, res);
                switch(input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
            else {
                string current_menu = "The airports with top air traffic capacity are: ";
                vector<string> vec_res;
                for (pair<int, Airport> pair_num_flights_and_airport : top_airports) {
                    vec_res.push_back(to_string(pair_num_flights_and_airport.first) + " flights out - "
                                      + pair_num_flights_and_airport.second.toString());
                }
                int input = this->print_result_and_get_choice_input(current_menu, vec_res);
                switch(input) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
        }
    }
}

void menu::statistics_for_a_specific_city_get_city() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific city - enter city";
        string city = this->print_menu_and_get_string_input("Enter city");
        if (city == "0") {
            return;
        } else if (city == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string country = this->print_menu_and_get_string_input("Enter country");
        if (country == "0") {
            return;
        } else if (country == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string city_code = city + "-" + country;
        City *city_pointer = this->Request.get_city_pointer_from_city_code(city_code);
        if (city_pointer == nullptr) {
            cout << "City with code " << city + "-" + country << " does not exist\n";
        } else {
            this->statistics_for_a_specific_city(city_pointer);
        }
    }
}

void menu::statistics_for_a_specific_city_want_airline(City *city_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific city - " + city_pointer->getCode();
        vector<string> options = {"Any airline", "A specific airline"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->statistics_for_a_specific_city_show_number_of_flights_out(city_pointer, nullptr);
                break;
            case 2:
                this->statistics_for_a_specific_city_get_airline(city_pointer);
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }

}

void menu::statistics_for_a_specific_city_get_airline(City *city_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific city - " + city_pointer->getCode() + " - enter airline code";
        string airline_code = this->print_menu_and_get_string_input(current_menu);
        if (airline_code == "0") {
            return;
        } else if (airline_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airline *airline_pointer = this->Request.get_airline_pointer_from_airline_code(airline_code);
            if (airline_pointer == nullptr) {
                cout << "Airline with code " << airline_code << " does not exist\n";
            } else {
                this->statistics_for_a_specific_city_show_number_of_flights_out(city_pointer, airline_pointer);
            }
        }
    }
}

void menu::statistics_for_a_specific_city_show_number_of_flights_out(City *city_pointer, Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific city - " + city_pointer->getCode();
        int flights_from_city = 0;
        for (Airport *&airport_pointer: city_pointer->getAirports()) {
            flights_from_city += Request.get_flights_from_airport_pointer(airport_pointer).size();
        }
        string res = "There are " + to_string(flights_from_city)
                     + " flights from this city in total.";
        vector<string> vec_res = {res};
        int input2 = this->print_result_and_get_choice_input(current_menu, vec_res);
        switch (input2) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::statistics_for_a_specific_city(City *city_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific city - " + city_pointer->getCode();
        vector<string> options = {"Number of flights out of the city", "Number of countries the city has flights to",
                                  "Number of reachable destinations"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->statistics_for_a_specific_city_want_airline(city_pointer);
                break;
            case 2:
//                this->specific_city_get_number_of_countries_it_flies_to;
                break;
            case 3:
//                this->specific_city_get_number_of_reachable_destinations;
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::statistics_for_a_specific_airline_get_airline() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific airline - enter airline code";
        string airline_code = this->print_menu_and_get_string_input(current_menu);
        if (airline_code == "0") {
            return;
        } else if (airline_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airline *airline_pointer = this->Request.get_airline_pointer_from_airline_code(airline_code);
            if (airline_pointer == nullptr) {
                cout << "Airline with code " << airline_code << " does not exist\n";
            } else {
                this->statistics_for_a_specific_airline(airline_pointer);
            }
        }
    }
}

void menu::statistics_for_a_specific_airline(Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Statistics for a specific airline - " + airline_pointer->getCode();
        vector<string> options = {"Number of flights"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1 : {
                int flights_from_airline = Request.get_number_flights_from_airline_pointer(airline_pointer);
                string res = "There are " + to_string(flights_from_airline)
                             + " flights from this airline in total.";
                vector<string> vec_res = {res};
                int input2 = this->print_result_and_get_choice_input(current_menu, vec_res);
                switch (input2) {
                    case -1:
                        this->go_back_to_main_menu = true;
                        return;
                    case 0:
                        break;
                    default:
                        cout << "Invalid input, please try again\n";
                        break;
                }
            }
        }
    }
}

void menu::best_flight_option() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - select starting source";
        vector<string> options = {"Airport code", "City", "Geographical coordinates"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->best_flight_option_get_airport_source();
                break;
            case 2:
                this->best_flight_option_get_city_source();
                break;
            case 3:
                this->best_flight_option_get_geographical_coordinates_source();
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::best_flight_option_get_airport_source() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - enter airport code";
        string airport_code = this->print_menu_and_get_string_input(current_menu);
        if (airport_code == "0") {
            return;
        } else if (airport_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airport *airport_pointer = this->Request.get_airport_pointer_from_airport_code(airport_code);
            if (airport_pointer == nullptr) {
                cout << "Airport with code " << airport_code << " does not exist\n";
            } else {
                vector<Airport*> airport_pointer_vec = {airport_pointer};
                string vector_airport_pointer_code = airport_pointer->getCode();
                this->best_flight_option_select_airline(airport_pointer_vec, vector_airport_pointer_code);
            }
        }
    }
}

void menu::best_flight_option_get_geographical_coordinates_source() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - enter geographical coordinates";
        string latitude = this->print_menu_and_get_string_input("Enter latitude");
        if (latitude == "0") {
            return;
        } else if (latitude == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string longitude = this->print_menu_and_get_string_input("Enter longitude");
        if (longitude == "0") {
            return;
        } else if (longitude == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        vector<Airport*> airport_pointer_vec = this->Request.get_vector_airport_pointer_from_geographical_coordinates(stod(latitude), stod(longitude));
        if (airport_pointer_vec.empty()) {
            cout << "No airports found with these geographical coordinates\n";
        } else {
            this->best_flight_option_select_airline(airport_pointer_vec, latitude + "-" + longitude);
        }
    }
}

void menu::best_flight_option_get_city_source() {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - enter city";
        string city = this->print_menu_and_get_string_input("Enter city");
        if (city == "0") {
            return;
        } else if (city == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string country = this->print_menu_and_get_string_input("Enter country");
        if (country == "0") {
            return;
        } else if (country == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        vector<Airport*> airport_pointer_vec = this->Request.get_vector_airport_pointer_from_city(city, country);
        if (airport_pointer_vec.empty()) {
            cout << "No airports found in this city\n";
        } else {
            this->best_flight_option_select_airline(airport_pointer_vec, city + "-" + country);
        }
    }
}

void menu::best_flight_option_select_airline(vector<Airport*> vector_airport_pointer, string source_code) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - select airline";
        vector<string> options = {"Any airline", "A specific airline", "As few airlines as possible"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 2:
                this->best_flight_option_get_airline(vector_airport_pointer, source_code);
                break;
            case 1:
                this->best_flight_option_select_destination(vector_airport_pointer, source_code, nullptr);
                break;
            case 3:
//                this->best_flight_option_airport_select_destination(airport_pointer, nullptr, true);  // ???
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::best_flight_option_get_airline(vector<Airport*> vector_airport_pointer, string source_code) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - enter airline code";
        string airline_code = this->print_menu_and_get_string_input(current_menu);
        if (airline_code == "0") {
            return;
        } else if (airline_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airline *airline_pointer = this->Request.get_airline_pointer_from_airline_code(airline_code);
            if (airline_pointer == nullptr) {
                cout << "Airline with code " << airline_code << " does not exist\n";
            } else {
                this->best_flight_option_select_destination(vector_airport_pointer, source_code, airline_pointer);
            }
        }
    }
}

void menu::best_flight_option_select_destination(vector<Airport*> vector_airport_pointer, string source_code, Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - select destination";
        vector<string> options = {"Airport code", "City", "Geographical coordinates"};
        int input = this->print_menu_and_get_choice_input(current_menu, options);
        switch (input) {
            case -1:
                this->go_back_to_main_menu = true;
                return;
            case 0:
                return;
            case 1:
                this->best_flight_option_get_airport_destination(vector_airport_pointer, source_code, airline_pointer);
                break;
            case 2:
                this->best_flight_option_get_city_destination(vector_airport_pointer, source_code, airline_pointer);
                break;
            case 3:
                this->best_flight_option_get_geographical_coordinates_destination(vector_airport_pointer, source_code, airline_pointer);
                break;
            default:
                cout << "Invalid input, please try again\n";
                break;
        }
    }
}

void menu::best_flight_option_get_airport_destination(vector<Airport*> vector_airport_pointer, string source_code, Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - enter destination airport code";
        string destination_airport_code = this->print_menu_and_get_string_input(current_menu);
        if (destination_airport_code == "0") {
            return;
        } else if (destination_airport_code == "-1") {
            this->go_back_to_main_menu = true;
            return;
        } else {
            Airport *destination_airport_pointer = this->Request.get_airport_pointer_from_airport_code(destination_airport_code);
            if (destination_airport_pointer == nullptr) {
                cout << "Airport with code " << destination_airport_code << " does not exist\n";
            } else {
                vector<Airport*> destination_airport_pointer_vec = {destination_airport_pointer};
                string destination_code = "";
                for (Airport* &airport_pointer : destination_airport_pointer_vec) {
                    destination_code += airport_pointer->getCode();
                }
                this->best_flight_option_airport_to_airport(vector_airport_pointer, source_code, airline_pointer,
                                                            destination_airport_pointer_vec, destination_code);
            }
        }
    }
}

void menu::best_flight_option_get_geographical_coordinates_destination(std::vector<Airport *> vector_airport_pointer,
                                                                       std::string source_code,
                                                                       Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - enter geographical coordinates";
        string latitude = this->print_menu_and_get_string_input("Enter latitude");
        if (latitude == "0") {
            return;
        } else if (latitude == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string longitude = this->print_menu_and_get_string_input("Enter longitude");
        if (longitude == "0") {
            return;
        } else if (longitude == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        vector<Airport*> destination_airport_pointer_vec = this->Request.get_vector_airport_pointer_from_geographical_coordinates(stod(latitude), stod(longitude));
        if (destination_airport_pointer_vec.empty()) {
            cout << "No airports found with these geographical coordinates\n";
        } else {
            this->best_flight_option_airport_to_airport(vector_airport_pointer, source_code, airline_pointer,
                                                        destination_airport_pointer_vec,
                                                        latitude + "-" + longitude);
        }
    }
}

void menu::best_flight_option_get_city_destination(std::vector<Airport *> vector_airport_pointer,
                                                   std::string source_code,
                                                   Airline *airline_pointer) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - enter city";
        string city = this->print_menu_and_get_string_input("Enter city");
        if (city == "0") {
            return;
        } else if (city == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        string country = this->print_menu_and_get_string_input("Enter country");
        if (country == "0") {
            return;
        } else if (country == "-1") {
            this->go_back_to_main_menu = true;
            return;
        }
        vector<Airport*> destination_airport_pointer_vec = this->Request.get_vector_airport_pointer_from_city(city, country);
        if (destination_airport_pointer_vec.empty()) {
            cout << "No airports found in this city\n";
        } else {
            this->best_flight_option_airport_to_airport(vector_airport_pointer, source_code, airline_pointer,
                                                        destination_airport_pointer_vec,
                                                        city + "-" + country);
        }
    }
}

void menu::best_flight_option_airport_to_airport(vector<Airport*> airport_pointer_vec, string source_code, Airline *airline_pointer,
                                                   vector<Airport*> destination_pointer_vec, string destination_code) {
    while (!this->go_back_to_main_menu) {
        string current_menu = "Best flight option - source - " + source_code + " - destination - "
                              + destination_code;
        vector<Airline*> airline_pointer_vec = {airline_pointer};
        pair<vector<Flight>, Airport*> flights = Request.get_flights_best_option_bfs(airport_pointer_vec,
                                                                 destination_pointer_vec,
                                                                 airline_pointer_vec);
        if (flights.second == nullptr) {
            string current_selection = "No flights found.";
            vector<string> res = {"No flights found from this airport to this destination."};
            int input = this->print_result_and_get_choice_input(current_selection, res);
            switch(input) {
                case -1:
                    this->go_back_to_main_menu = true;
                    return;
                case 0:
                    break;
                default:
                    cout << "Invalid input, please try again\n";
                    break;
            }
        }
        else {
            vector<string> vec_res;
            double full_distance = 0;
            for (Flight flight : flights.first) {
                vec_res.push_back(flight.toString());
                full_distance += flight.getDistance();
            }
            vec_res.push_back("Total distance: " + to_string(full_distance));
            int input = this->print_result_and_get_choice_input(current_menu, vec_res);
            switch(input) {
                case -1:
                    this->go_back_to_main_menu = true;
                    return;
                case 0:
                    break;
                default:
                    cout << "Invalid input, please try again\n";
                    break;
            }
        }
    }
}
