#include "rgb_keyboard.h"

void rgb_keyboard::keyboard::set_ajazzak33_compatibility(bool compatibility) {
    this->ajazzak33Compatibility = compatibility;

    if (compatibility) {
        keyboard_pid = keyboard_pid_ajazzak33;      // different PID
        brightness_max = brightness_max_ajazzak33;  // different maximum brightness
    } else {
        keyboard_pid = keyboard_pid_others;
        brightness_max = brightness_max_others;
    }
}

void rgb_keyboard::keyboard::set_mode(modes mode) {
    this->mode[profile - 1] = mode;
}

void rgb_keyboard::keyboard::set_direction(directions direction) {
    this->direction[profile - 1] = direction;
}

void rgb_keyboard::keyboard::set_speed(int speed) {
    if (speed >= speed_min && speed <= speed_max) {
        this->speed[profile - 1] = speed;
    } else {
        throw std::runtime_error("Speed not in valid range.");
    }
}

void rgb_keyboard::keyboard::set_brightness(int brightness) {
    if (brightness >= brightness_min && brightness <= brightness_max) {
        this->brightness[profile - 1] = brightness;
    } else {
        throw std::runtime_error("Brightness not in valid range.");
    }
}

void rgb_keyboard::keyboard::set_color(uint8_t color_r, uint8_t color_g, uint8_t color_b) {
    this->color_r[profile - 1] = color_r;
    this->color_g[profile - 1] = color_g;
    this->color_b[profile - 1] = color_b;
}

void rgb_keyboard::keyboard::set_rainbow(bool rainbow) {
    this->rainbow[profile - 1] = rainbow;
}

void rgb_keyboard::keyboard::set_variant(mode_variants variant) {
    this->variant[profile - 1] = variant;
}

void rgb_keyboard::keyboard::keyboard::set_custom_keys(std::string keys) {
    std::size_t position1;

    while ((position1 = keys.find('=')) != std::string::npos) {
        std::size_t position2 = keys.find(';');
        if (position2 != std::string::npos) {
            auto value1 = keys.substr(0, position1);
            auto value2 = keys.substr(position1 + 1, position2 - position1 - 1);
            keys.erase(0, position2 + 1);

            // store values in map
            if (value2.length() == 6) {
                uint8_t val_r = stoi(value2.substr(0, 2), nullptr, 16);
                uint8_t val_g = stoi(value2.substr(2, 2), nullptr, 16);
                uint8_t val_b = stoi(value2.substr(4, 2), nullptr, 16);
                std::array<uint8_t, 3> val_rgb = {val_r, val_g, val_b};
                key_colors[profile - 1][value1] = val_rgb;
            }
        } else {
            break;
        }
    }
}

void rgb_keyboard::keyboard::set_report_rate(report_rates report_rate) {
    this->report_rate[profile - 1] = report_rate;
}

void rgb_keyboard::keyboard::set_profile(int profile) {
    this->profile = profile;
}

void rgb_keyboard::keyboard::set_active_profile(int profile) {
    active_profile = profile;
}

void rgb_keyboard::keyboard::set_detach_kernel_driver(bool detach_kernel_driver) {
    this->detach_kernel_driver = detach_kernel_driver;
}

void rgb_keyboard::keyboard::set_open_interface_0(bool open_interface_0) {
    this->open_interface_0 = open_interface_0;
}
