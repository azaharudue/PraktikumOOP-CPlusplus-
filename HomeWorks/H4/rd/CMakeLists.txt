cmake_minimum_required(VERSION 3.2)

project(station)

set(SOURCES time.cpp train.cpp station.cpp main.cpp)

add_executable(station ${SOURCES})