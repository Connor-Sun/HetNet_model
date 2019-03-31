cmake_minimum_required(VERSION 3.13)
project(HetNet_model)

set(CMAKE_CXX_STANDARD 14)

add_executable(HetNet_model main.cpp BaseStation.cpp BaseStation.h UserEquipment.cpp UserEquipment.h initialize.cpp initialize.h QLA.cpp QLA.h)