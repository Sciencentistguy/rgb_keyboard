#include "rgb_keyboard.h"

// constructor
rgb_keyboard::keyboard::keyboard() {
    // default settings
    _direction.fill(d_undefined);
    _mode.fill(m_fixed);
    _variant.fill(v_undefined);
    _speed.fill(1);
    _profile = 1;
    _active_profile = 1;
}
