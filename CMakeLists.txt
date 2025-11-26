cmake_minimum_required(VERSION 3.20)
project(QtMVPDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SRC
    "*.cpp"
    "*.h"
    "data/*.h" "data/*.cpp"
    "service/*.h" "service/*.cpp"
    "parser/*.h" "parser/*.cpp"
    "presenter/*.h" "presenter/*.cpp"
    "pages/*.h" "pages/*.cpp"
    "devices/*.h" "devices/*.cpp"
)

add_executable(QtMVPDemo ${SRC})

target_include_directories(QtMVPDemo PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(QtMVPDemo PRIVATE Qt6::Widgets)