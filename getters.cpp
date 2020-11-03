#include "rgb_keyboard.h"

int rgb_keyboard::keyboard::get_speed() const {
    return speed[profile - 1];
}

int rgb_keyboard::keyboard::get_brightness() const {
    return brightness[profile - 1];
}

rgb_keyboard::keyboard::modes rgb_keyboard::keyboard::get_mode() const {
    return mode[profile - 1];
}

rgb_keyboard::keyboard::directions rgb_keyboard::keyboard::get_direction() const {
    return direction[profile - 1];
}

uint8_t rgb_keyboard::keyboard::get_color_r() const {
    return color_r[profile - 1];
}

uint8_t rgb_keyboard::keyboard::get_color_g() const {
    return color_g[profile - 1];
}

uint8_t rgb_keyboard::keyboard::get_color_b() const {
    return color_b[profile - 1];
}

bool rgb_keyboard::keyboard::get_rainbow() const {
    return rainbow[profile - 1];
}

rgb_keyboard::keyboard::mode_variants rgb_keyboard::keyboard::get_variant() const {
    return variant[profile - 1];
}

rgb_keyboard::keyboard::report_rates rgb_keyboard::keyboard::get_report_rate() const {
    return report_rate[profile - 1];
}

bool rgb_keyboard::keyboard::get_detach_kernel_driver() const {
    return detach_kernel_driver;
}

bool rgb_keyboard::keyboard::get_open_interface_0() const {
    return open_interface_0;
}

int rgb_keyboard::keyboard::get_active_profile() const {
    return active_profile;
}

int rgb_keyboard::keyboard::get_profile() const {
    return profile;
}

bool rgb_keyboard::keyboard::get_ajazzak33_compatibility() const {
    return ajazzak33Compatibility;
}
