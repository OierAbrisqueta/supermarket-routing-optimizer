cmake_minimum_required(VERSION 3.10)

project(RoutingOptimizer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG v0.53.1
)
FetchContent_MakeAvailable(httplib)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

include_directories(include)

find_package(SQLite3 REQUIRED)

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
        src/RouteEngine.cpp
        include/database.h
        src/Database.cpp
        include/ThreadPool.h
        src/ThreadPool.cpp)

add_executable(server src/main.cpp)
target_link_libraries(server PRIVATE
        routing_engine
        SQLite::SQLite3
        httplib::httplib
        nlohmann_json::nlohmann_json
)

add_executable(test_runner src/test_runner.cpp)
target_link_libraries(test_runner PRIVATE
        routing_engine
        SQLite::SQLite3)