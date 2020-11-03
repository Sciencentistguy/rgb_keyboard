#include "print_help.h"

#include <iostream>

void print_help() {
    std::cout << R"(This software controls the RGB lighting on some keyboards.
Licensed under the GNU GPL version 3 or later.

Options:;
    -h --help                   Displays this message
    -L --list-keys=arg          List valid keynames (arg: led, map, option)

    -p --profile=arg            Set profile to which the settings are applied (1-3)
    -a --active=arg             Set currently active profile (1-3)

    -c --color=color            Sets color of the current animation
    -b --brightness=brightness  Sets brightness of the current animation.
                            Integer from 0 to 9 (0-5 for AjazzAK33).
    -s --speed=speed            Sets speed of the current animation.
                            Integer from 0 to 3.
    -d --direction=direction    Sets direction of the current animation.
                            "left", "right", "up", "down", "inwards", "outwards".

    -l --leds=arg               Sets the led mode (pattern), valid values are:
                            "fixed", "sine", "rain", "waterfall", "vortex", "swirl", "breathing", "breathing-color",
                            "reactive-ripple", "reactive-single", "reactive-horizontal", "reactive-color", "horizontal-wave",
                            "vertical-wave", "diagonal-wave", "pulse", "hurricane", "ripple", "custom", "off"

    -v --variant=arg            Sets the variant of the reactive color mode, valid values are:
                            "red", "yellow", "green", "blue"

    -P --custom-pattern=file    Sets pattern in custom mode
    -K --custom-keys=keys       Sets pattern in custom mode

    -R --report-rate=rate       Sets USB report rate (125, 250, 500, 1000) Hz

    -M --keymap=file            Load keymap from specified file

    -r --read                   Read and print stored settings from the keyboard (experimental)

    -B --bus=number             Specify USB bus id, must be used with --device
    -D --device=number          Specify USB device number, must be used with --bus
    -k --kernel-driver          Don't try to detach the kernel driver, required on some systems
    -I --interface0             Don't open usb interface 0

    -A --ajazzak33              Enable experimental support for the AjazzAK33

Colors need to be specified in hexadecimal without any prefix (rrggbb).
"multi" can also be used to create a rainbow effect.)";
}
