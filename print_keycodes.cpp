#include "rgb_keyboard.h"

// prints all keys for custom led pattern
int rgb_keyboard::keyboard::print_keycodes_led() {
    for (const auto& i : keycodes) {
        std::cout << i.first << "\n";
    }

    return 0;
}

// prints all keys for remapping
int rgb_keyboard::keyboard::print_keycodes_remap() {
    for (const auto& i : keymap_offsets) {
        std::cout << i.first << "\n";
    }

    return 0;
}

// prints all rempping options
int rgb_keyboard::keyboard::print_keycodes_options() {
    for (const auto& i : keymap_options) {
        std::cout << i.first << "\n";
    }

    return 0;
}
