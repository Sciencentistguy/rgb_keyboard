cmake_minimum_required(VERSION 3.10)

project(rgb_keyboard)

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
