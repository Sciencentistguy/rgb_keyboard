cmake_minimum_required(VERSION 3.10)

project(rgb_keyboard)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")

add_executable(
        rgb_keyboard
        rgb_keyboard.cpp
        data.cpp
        macro.cpp
        fileio.cpp
        getters.cpp
        getters.cpp
        helpers.cpp
        readers.cpp
        setters.cpp
        writers.cpp
        print_help.cpp
        constructor.cpp
        print_keycodes.cpp
)

target_link_libraries(rgb_keyboard usb-1.0)
