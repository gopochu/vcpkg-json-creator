cmake_minimum_required(VERSION 3.20)

project(BUILDER)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(BUILDER main.cpp)
target_link_libraries(BUILDER PRIVATE nlohmann_json::nlohmann_json)