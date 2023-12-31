cmake_minimum_required(VERSION 3.26)
project(projeto_aed_2nd)

set(CMAKE_CXX_STANDARD 23)

add_executable(projeto_aed_2nd main.cpp
        source/csv_reader.h
        source/csv_reader.cpp
        source/menu.h
        source/menu.cpp
        source/request.h
        source/request.cpp
        source/Airport.cpp
        source/Airport.h
        source/Flight.cpp
        source/Flight.h
        source/Airline.cpp
        source/Airline.h
)

include_directories(source)