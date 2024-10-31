cmake_minimum_required(VERSION 3.20)

project(VCPKJ_JSON_BUILDER)

find_package(nlohmann_json CONFIG REQUIRED)
add_executable(VCPKJ_JSON_BUILDER main.cpp)
target_link_libraries(VCPKJ_JSON_BUILDER PRIVATE nlohmann_json::nlohmann_json)