cmake_minimum_required(VERSION 3.12)
project(DayZServicePipeline)

set(CMAKE_CXX_STANDARD 17)

set(THIRD_PARTY_SOURCES ThirdParty/cxxopts/cxxopts.hpp)

add_executable(DayZServicePipeline main.cpp
                                   LibraryLoader.cpp
                                   LibraryLoader.hpp
                                   ServicePipeline.cpp
                                   ServicePipeline.hpp
                                   Workload.cpp
                                   Workload.hpp
                                   WorkloadProcessor.cpp
                                   WorkloadProcessor.hpp
                                   ${THIRD_PARTY_SOURCES})