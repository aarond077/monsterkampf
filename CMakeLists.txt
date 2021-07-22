cmake_minimum_required(VERSION 3.10)
project(eis_klausur2021)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\msvc2017")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Multimedia REQUIRED)

add_executable(eis_klausur2021 main.cpp)

target_link_libraries(eis_klausur2021 Qt5::Core)
target_link_libraries(eis_klausur2021 Qt5::Widgets)
target_link_libraries(eis_klausur2021 Qt5::Quick)
target_link_libraries(eis_klausur2021 Qt5::Multimedia)
