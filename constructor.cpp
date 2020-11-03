#include "rgb_keyboard.h"

// constructor
rgb_keyboard::keyboard::keyboard() {
    // default settings
    direction.fill(directions::undefined);
    mode.fill(modes::fixed);
    variant.fill(mode_variants::undefined);
    speed.fill(1);
    profile = 1;
    active_profile = 1;
}
