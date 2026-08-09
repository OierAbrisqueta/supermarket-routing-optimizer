cmake_minimum_required(VERSION 3.10)

project(RoutingOptimizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(server src/main.cpp
        include/Node.h
        src/Node.cpp
        include/Item.h
        src/Item.cpp
        include/Edge.h
        src/Edge.cpp
        include/StoreLayout.h
        src/StoreLayout.cpp)