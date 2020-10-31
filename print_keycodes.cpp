#include "rgb_keyboard.h"

// prints all keys for custom led pattern
int rgb_keyboard::keyboard::print_keycodes_led() {
    for (auto i : _keycodes) {
        std::cout << i.first << "\n";
    }

    return 0;
}

// prints all keys for remapping
int rgb_keyboard::keyboard::print_keycodes_remap() {
    for (auto i : _keymap_offsets) {
        std::cout << i.first << "\n";
    }

    return 0;
}

// prints all rempping options
int rgb_keyboard::keyboard::print_keycodes_options() {
    for (auto i : _keymap_options) {
        std::cout << i.first << "\n";
    }

    return 0;
}
