cmake_minimum_required(VERSION 3.10)

project(rgb_keyboard)

add_executable(
        rgb_keyboard
            rgb_keyboard.cpp
            include/data.cpp
            include/macro.cpp
            include/fileio.cpp
            include/getters.cpp
            include/getters.cpp
            include/helpers.cpp
            include/readers.cpp
            include/setters.cpp
            include/writers.cpp
            include/print_help.cpp
            include/constructor.cpp
            include/print_keycodes.cpp
    )

target_link_libraries(rgb_keyboard usb-1.0)
