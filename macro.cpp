#include "macro.h"

#include <iostream>

void rgb_keyboard::macro::set_repeats(uint8_t repeats) {
    _repeats = repeats ? repeats : 1;
}

uint8_t rgb_keyboard::macro::get_repeats() {
    return _repeats;
}

unsigned int rgb_keyboard::macro::get_number_of_actions() {
    return _num_actions;
}

void rgb_keyboard::macro::clear() {
    _repeats = 1;
    _num_actions = 0;
}

int rgb_keyboard::macro::get_action(unsigned int number, action_type& type, std::string& key, unsigned int& delay) {
    if (number >= _num_actions)
        return 1;

    type = _actions.at(number);
    key = _keys.at(number);
    delay = _delays.at(number);

    return 0;
}

int rgb_keyboard::macro::append_action(action_type type, std::string key, unsigned int delay) {
    if (_num_actions >= max_actions || delay > max_delay)
        return 1;

    _actions.at(_num_actions) = type;
    _keys.at(_num_actions) = key;
    _delays.at(_num_actions) = delay;

    _num_actions++;

    return 0;
}
