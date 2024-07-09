cmake_minimum_required(VERSION 3.5)

project(DigitalClock)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

set(CMAKE_AUTOMOC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

qt5_add_resources(RESOURCES resources.qrc)

add_executable(DigitalClock main.cpp ${RESOURCES})

target_link_libraries(DigitalClock Qt5::Widgets Qt5::Multimedia)

install(TARGETS DigitalClock DESTINATION /usr/local/bin)

