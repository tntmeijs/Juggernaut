cmake_minimum_required(VERSION 3.1...3.15)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project (Juggernaut
    VERSION 0.1.0
    DESCRIPTION "GPU path tracer"
    LANGUAGES CXX)

add_subdirectory(src)
