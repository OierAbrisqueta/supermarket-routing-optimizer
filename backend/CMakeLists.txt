cmake_minimum_required(VERSION 3.10)

project(RoutingOptimizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(routing_engine
        include/Node.h
        src/Node.cpp
        include/Item.h
        src/Item.cpp
        include/Edge.h
        src/Edge.cpp
        include/StoreLayout.h
        src/StoreLayout.cpp
        include/RouteEngine.h
        src/RouteEngine.cpp)

add_executable(server src/main.cpp)
target_link_libraries(server PRIVATE routing_engine)

add_executable(test_runner src/test_runner.cpp)
target_link_libraries(test_runner PRIVATE routing_engine)