cmake_minimum_required(VERSION 3.30)
project(CS162_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS162_Project main.cpp
        plant.h
        plant.cpp
        gardenLog.cpp
        gardenLog.h)
