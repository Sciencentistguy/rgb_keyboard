// main class
#ifndef RGB_KEYBOARD
#define RGB_KEYBOARD

#include <algorithm>
#include <array>
#include <deque>
#include <exception>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include <libusb-1.0/libusb.h>

#include "macro.h"

namespace rgb_keyboard {

    /**
     * This class represents the keyboard.
     *
     * The keyboard has 3 profiles with independent settings, all settings are stored on the keyboard.
     * To change the settings on the keyboard, the general procedure is as follows:
     *
     * 1. Open the keyboard with open_keyboard() or open_keyboard_bus_device()
     * 2. Call set_*() or load_*() to change the private variables of this class. The setter functions set the setting for \_profile (=1 by default),
     * therefore to change the settings for a different profile call set_profile() first.
     * 3. Call write\_*() to apply the settings to the keyboard
     * 4. Close the keyboard with close_keyboard()
     *
     * To obtain the current settings from the keyboard:
     * 1. Open the keyboard
     * 2. Call read_*() to read the settings from the keyboard
     * 3. Call get_*() to get the state of the private variables
     * 4. Close the keyboard
     *
     * Due to legacy reasons, the get_*, set_* and most write_* functions act on
     * the profile indicated by _profile (1 by default).
     */
    class keyboard {
     public:
        /// The different led modes
        enum struct modes {
            undefined,
            fixed,
            sine,
            rain,
            waterfall,
            vortex,
            swirl,
            breathing,
            breathing_color,
            reactive_ripple,
            reactive_single,
            reactive_horizontal,
            reactive_color,
            horizontal_wave,
            vertical_wave,
            diagonal_wave,
            pulse,
            hurricane,
            ripple,
            custom,
            off
        };

        /// The directions for animated led patterns
        enum struct directions { undefined, left = 1, right = 2, up = 1, down = 2, inwards = 1, outwards = 2 };

        /// The variants for the reactive_color led mode
        enum struct mode_variants { undefined, color_red, color_yellow, color_green, color_blue };

        /// The available USB poll rates
        enum struct report_rates { r_125Hz, r_250Hz, r_500Hz, r_1000Hz };

        /// Constructor, sets default settings
        keyboard();

        // setter functions: set values for current _profile
        /** Enable/disable Ajazz AK33 compatibility mode.
         * This changes the way data is send, the USB PID, the maximum brightness, etc.
         */
        void set_ajazzak33_compatibility(bool compatibility);
        /** Set the profile to which settings are applied with set_*()
         * \param profile 1-3
         * \return 0 if successful, 1 if invalid argument
         */
        void set_profile(int profile);
        /** Set the profile that is active on the keyboard
         * \param profile 1-3
         * \return 0 if successful, 1 if invalid argument
         * \see write_active_profile()
         */
        void set_active_profile(int profile);
        /// Set the led mode
        void set_mode(modes mode);
        /// Set the led pattern direction
        void set_direction(directions direction);
        /// Set the led brightness
        void set_brightness(int brightness);
        /// Set the led animation speed
        void set_speed(int speed);
        /// Set the led color
        void set_color(uint8_t color_r, uint8_t color_g, uint8_t color_b);
        /// Enables/disables rainbow/multicolor mode
        void set_rainbow(bool rainbow);
        /// Set the variant of the reactive_color led mode
        void set_variant(mode_variants variant);
        /// Set custom color of individual keys
        void set_custom_keys(std::string keys);
        /// Set the USB poll rate
        void set_report_rate(report_rates report_rate);
        /// Set whether to detach the kernel driver for the keyboard
        void set_detach_kernel_driver(bool detach_kernel_driver);
        /// Set whether to open USB interface 0
        void set_open_interface_0(bool open_interface_0);

        // getter functions
        /// LED mode getter
        [[nodiscard]] modes get_mode() const;
        /// LED animation direction getter
        [[nodiscard]] directions get_direction() const;
        /// LED brightness getter
        [[nodiscard]] int get_brightness() const;
        /// LED animation speed getter
        [[nodiscard]] int get_speed() const;
        /// Color (red component) getter
        [[nodiscard]] uint8_t get_color_r() const;
        /// Color (green component) getter
        [[nodiscard]] uint8_t get_color_g() const;
        /// Color (blue component) getter
        [[nodiscard]] uint8_t get_color_b() const;
        /// LED multicolor mode getter
        [[nodiscard]] bool get_rainbow() const;
        /// LED rective_color variant getter
        [[nodiscard]] mode_variants get_variant() const;
        /// USB poll rate getter
        [[nodiscard]] report_rates get_report_rate() const;
        /// Get whether to detach the kernel driver
        [[nodiscard]] bool get_detach_kernel_driver() const;
        /// Get whether to open usb interface 0 driver
        [[nodiscard]] bool get_open_interface_0() const;
        /// Active profile getter
        [[nodiscard]] int get_active_profile() const;
        /// Get profile to which settings are applied
        [[nodiscard]] int get_profile() const;
        /// Get whether Ajazz AK33 compatibility is enabled
        [[nodiscard]] bool get_ajazzak33_compatibility() const;

        // writer functions (apply settings to keyboard)
        /// Write the brightness to the keyboard
        int write_brightness();
        /// Write the LED animation speed to the keyboard
        int write_speed();
        /// Write the LED mode to the keyboard
        int write_mode();
        /// Write the LED animation direction to the keyboard
        int write_direction();
        /// Write the LED color to the keyboard
        int write_color();
        /// Write the custom LED pattern to the keyboard
        int write_custom();
        /// Write the reactive_color variant to the keyboard
        int write_variant();
        /// Write the USB poll rate to the keyboard
        int write_report_rate();
        /// Write the keymapping to the keyboard, (ANSI layout only)
        int write_key_mapping_ansi();
        /// Write the active profile to the keyboard
        int write_active_profile();

        // reader functions
        /// Read the active profile from the keyboard
        int read_active_profile();
        /** Read the LED settings from the keyboard
         * These are LED mode, brightness, color, speed, direction,
         * reactive_color variant and the usb poll rate
         */
        int read_led_settings();

        // helper functions
        /** Initialize libusb and open keyboard by USB VID and USB PID
         * \see _keyboard_vid
         * \see _keyboard_pid
         * \return 0 if successful
         */
        int open_keyboard();
        /** Initialize libusb and open keyboard with bus number and device id
         * \return 0 if successful
         */
        int open_keyboard_bus_device(uint8_t bus, uint8_t device);
        /// Close the keyboard and libusb
        int close_keyboard();

        // loader functions (read settings from file)
        /** Load custom led pattern from the specified file
         * \return 0 if successful
         * \see write_custom()
         */
        int load_custom(std::string File);
        /** Load keymap from the specified file
         * \return 0 if successful
         */
        int load_keymap(std::string File);

        // prints all valid keycodes
        /// Print all valid key names for custom led patterns to stdout
        static int print_keycodes_led();
        /// Print all valid key names for key remapping to stdout
        static int print_keycodes_remap();
        /// Print all valid options for key remapping to stdout
        static int print_keycodes_options();

     private:
        /// Wrapper around libusb for sending data
        int write_data(const unsigned char* data, int length);

        /** If this is variable is set to true, usb control transfers are used for sending data.
         *  This enables compatibility with other keyboards (Ajazz AK 33).
         */
        bool ajazzak33Compatibility = false;

        /// Profile (1-3): this determines the profile to which the settings are applied
        int profile;

        /// Currently active profile
        int active_profile;

        // rgb control vars
        /// LED mode
        std::array<modes, 3> mode;
        /// LED animation direction
        std::array<directions, 3> direction;
        /// LED brightness
        std::array<int, 3> brightness;
        /// LED animation direction
        std::array<int, 3> speed;
        /// LED color (red component)
        std::array<uint8_t, 3> color_r;
        /// LED color (green component)
        std::array<uint8_t, 3> color_g;
        /// LED color (blue component)
        std::array<uint8_t, 3> color_b;
        /// LED multicolor status
        std::array<bool, 3> rainbow;
        /// Variant for the reactive color LED mode
        std::array<mode_variants, 3> variant;
        /// USB poll rate
        std::array<report_rates, 3> report_rate;

        // min and max values
        /// Minimum value for brightness
        const int brightness_min = 0;
        /// Maximum value for brightness for the Ajazz AK 33
        const int brightness_max_ajazzak33 = 5;
        /// Maximum value for brightness for keyboards except the Ajazz AK 33
        const int brightness_max_others = 9;
        /// Maximum value for brightness (this is not constant, the Ajazz AK33 has a different value)
        int brightness_max = brightness_max_others;
        /// Minimum led pattern animation speed
        const int speed_min = 0;
        /// Maximum led pattern animation speed
        const int speed_max = 3;

        // usb device vars
        /// USB vendor id
        const uint16_t keyboard_vid = 0x0c45;

        // TODO! rewrite this
        /// USB product id for the Ajazz AK33
        static constexpr std::array<uint16_t, 5> keyboard_pid_ajazzak33 = {0x7903, 0x5204, 0x5104, 0x5004, 0x8520};
        /** USB product ids for other keyboards
         * Tecware Phantom, GMMK = 0x652f
         * Redragon K550 Yama = 0x5204
         * Redragon K552 Kumara = 0x5104
         * Redragon K556 Devarajas = 0x5004
         * Warrior Kane TC235 = 0x8520
         */
        static constexpr std::array<uint16_t, 5> keyboard_pid_others = {0x5204, 0x5104, 0x5004, 0x8520, 0x652f};
        /// USB product id, this is not constant as the Ajazz AK33 has a different PID
        std::array<uint16_t, 5> keyboard_pid = keyboard_pid_others;

        /// If true, try to detach the kernel driver when opening the keyboard
        bool detach_kernel_driver = true;

        /// Detached  kernel driver? → for attaching after being done
        bool detached_driver_0 = false;
        /// Detached  kernel driver? → for attaching after being done
        bool detached_driver_1 = false;

        /// Try to open usb interface 0 ?
        bool open_interface_0 = true;

        /// libusb device handle
        libusb_device_handle* handle = nullptr;

        // usb data packets
        constexpr static uint8_t data_start[] = {0x04, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        constexpr static uint8_t data_end[] = {0x04, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        constexpr static uint8_t data_settings[] = {0x04, 0x00, 0x00, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        // key mapping data
        constexpr static uint8_t data_remap_1[] = {0x04, 0x2a, 0x01, 0x0a, 0x10, 0x00, 0x00, 0x00, 0xaa, 0x55, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00,
                                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        constexpr static uint8_t data_remap_2[] = {
            0x04, 0xcd, 0x07, 0x08, 0x38, 0x00, 0x00, 0x00, /* ....8... */
            0x05, 0xa2, 0xa2, 0x02, 0x02, 0x29, 0x02, 0x02, /* .....).. */
            0x3a, 0x02, 0x02, 0x3b, 0x02, 0x02, 0x3c, 0x02, /* :..;..<. */
            0x02, 0x3d, 0x02, 0x02, 0x3e, 0x02, 0x02, 0x3f, /* .=..>..? */
            0x02, 0x02, 0x40, 0x02, 0x02, 0x41, 0x02, 0x02, /* ..@..A.. */
            0x42, 0x02, 0x02, 0x43, 0x02, 0x02, 0x44, 0x02, /* B..C..D. */
            0x02, 0x45, 0x03, 0xb6, 0x00, 0x03, 0xcd, 0x00, /* .E...... */
            0x03, 0xb5, 0x00, 0x05, 0xa2, 0x01, 0x02, 0x02  /* ........ */
        };

        constexpr static uint8_t data_remap_3[] = {
            0x04, 0x8b, 0x04, 0x08, 0x38, 0x38, 0x00, 0x00, /* ....88.. */
            0x35, 0x02, 0x02, 0x1e, 0x02, 0x02, 0x1f, 0x02, /* 5....... */
            0x02, 0x20, 0x02, 0x02, 0x21, 0x02, 0x02, 0x22, /* . ..!.." */
            0x02, 0x02, 0x23, 0x02, 0x02, 0x24, 0x02, 0x02, /* ..#..$.. */
            0x25, 0x02, 0x02, 0x26, 0x02, 0x02, 0x27, 0x02, /* %..&..'. */
            0x02, 0x2d, 0x02, 0x02, 0x2e, 0x02, 0x02, 0x53, /* .-.....S */
            0x02, 0x02, 0x54, 0x02, 0x02, 0x55, 0x05, 0xa2, /* ..T..U.. */
            0x02, 0x02, 0x02, 0x2b, 0x02, 0x02, 0x14, 0x02  /* ...+.... */
        };

        constexpr static uint8_t data_remap_4[] = {
            0x04, 0x2c, 0x04, 0x08, 0x38, 0x70, 0x00, 0x00, /* .,..8p.. */
            0x02, 0x1a, 0x02, 0x02, 0x08, 0x02, 0x02, 0x15, /* ........ */
            0x02, 0x02, 0x17, 0x02, 0x02, 0x1c, 0x02, 0x02, /* ........ */
            0x18, 0x02, 0x02, 0x0c, 0x02, 0x02, 0x12, 0x02, /* ........ */
            0x02, 0x13, 0x02, 0x02, 0x2f, 0x02, 0x02, 0x30, /* ..../..0 */
            0x02, 0x02, 0x5f, 0x02, 0x02, 0x60, 0x02, 0x02, /* .._..`.. */
            0x61, 0x05, 0xa2, 0x03, 0x02, 0x02, 0x39, 0x02, /* a.....9. */
            0x02, 0x04, 0x02, 0x02, 0x16, 0x02, 0x02, 0x07  /* ........ */
        };

        constexpr static uint8_t data_remap_5[] = {
            0x04, 0x2a, 0x04, 0x08, 0x38, 0xa8, 0x00, 0x00, /* .*..8... */
            0x02, 0x02, 0x09, 0x02, 0x02, 0x0a, 0x02, 0x02, /* ........ */
            0x0b, 0x02, 0x02, 0x0d, 0x02, 0x02, 0x0e, 0x02, /* ........ */
            0x02, 0x0f, 0x02, 0x02, 0x33, 0x02, 0x02, 0x34, /* ....3..4 */
            0x02, 0x02, 0x31, 0x02, 0x02, 0x5c, 0x02, 0x02, /* ..1..\.. */
            0x5d, 0x02, 0x02, 0x5e, 0x05, 0xa2, 0x04, 0x02, /* ]..^.... */
            0x01, 0x02, 0x02, 0x02, 0x1d, 0x02, 0x02, 0x1b, /* ........ */
            0x02, 0x02, 0x06, 0x02, 0x02, 0x19, 0x02, 0x02  /* ........ */
        };

        constexpr static uint8_t data_remap_6[] = {
            0x04, 0x11, 0x05, 0x08, 0x38, 0xe0, 0x00, 0x00, /* ....8... */
            0x05, 0x02, 0x02, 0x11, 0x02, 0x02, 0x10, 0x02, /* ........ */
            0x02, 0x36, 0x02, 0x02, 0x37, 0x02, 0x02, 0x38, /* .6..7..8 */
            0x02, 0x01, 0x20, 0x02, 0x02, 0x28, 0x02, 0x02, /* .. ..(.. */
            0x59, 0x02, 0x02, 0x5a, 0x02, 0x02, 0x5b, 0x05, /* Y..Z..[. */
            0xa2, 0x05, 0x02, 0x01, 0x01, 0x02, 0x01, 0x08, /* ........ */
            0x02, 0x01, 0x04, 0x02, 0x02, 0x2c, 0x02, 0x01, /* .....,.. */
            0x40, 0x05, 0x02, 0x02, 0x02, 0x02, 0x65, 0x02  /* @.....e. */
        };

        constexpr static uint8_t data_remap_7[] = {
            0x04, 0xdf, 0x06, 0x08, 0x38, 0x18, 0x01, 0x00, /* ....8... */
            0x01, 0x10, 0x02, 0x02, 0x50, 0x02, 0x02, 0x51, /* ....P..Q */
            0x02, 0x02, 0x52, 0x02, 0x02, 0x4f, 0x02, 0x02, /* ..R..O.. */
            0x2a, 0x02, 0x02, 0x62, 0x02, 0x02, 0x63, 0x02, /* *..b..c. */
            0x02, 0x58, 0x02, 0x02, 0x91, 0x02, 0x02, 0x90, /* .X...... */
            0x02, 0x01, 0x80, 0x02, 0x02, 0x64, 0x02, 0x02, /* .....d.. */
            0x46, 0x02, 0x02, 0x47, 0x02, 0x02, 0x48, 0x02, /* F..G..H. */
            0x02, 0x38, 0x02, 0x02, 0x49, 0x02, 0x02, 0x4a  /* .8..I..J */
        };

        constexpr static uint8_t data_remap_8[] = {
            0x04, 0xd7, 0x07, 0x08, 0x15, 0x50, 0x01, 0x00, /* .....P.. */
            0x02, 0x02, 0x4b, 0x02, 0x02, 0x4c, 0x02, 0x02, /* ..K..L.. */
            0x4d, 0x02, 0x02, 0x4e, 0x02, 0x02, 0x56, 0x02, /* M..N..V. */
            0x02, 0x57, 0x03, 0xe2, 0x00, 0x02, 0x63, 0x02, /* .W....c. */
            0x02, 0x58, 0x02, 0x02, 0x91, 0x02, 0x02, 0x90, /* .X...... */
            0x02, 0x01, 0x80, 0x02, 0x02, 0x64, 0x02, 0x02, /* .....d.. */
            0x46, 0x02, 0x02, 0x47, 0x02, 0x02, 0x48, 0x02, /* F..G..H. */
            0x02, 0x38, 0x02, 0x02, 0x49, 0x02, 0x02, 0x4a  /* .8..I..J */
        };

        constexpr static uint8_t data_profile[] = {
            0x04, 0xe0, 0x03, 0x04, 0x2c, 0x00, 0x00, 0x00, /* ....,... */
            0x55, 0xaa, 0xff, 0x02, 0x45, 0x0c, 0x2f, 0x65, /* U...E./e */
            0x03, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, /* ........ */
            0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08, 0x07, /* ........ */
            0x09, 0x0b, 0x0a, 0x0c, 0x0d, 0x0f, 0x0e, 0x10, /* ........ */
            0x12, 0x11, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* ........ */
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  /* ........ */
        };

        constexpr static uint8_t data_macros[] = {0x04, 0x5d, 0x06, 0x0a, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        constexpr static uint8_t data_read[] = {0x04, 0x2f, 0x00, 0x03, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

        /// Stores the key names for custom key colors
        const static std::map<std::string_view, std::array<uint8_t, 3>> keycodes;
        /// Stores custom key colors
        std::array<std::map<std::string, std::array<uint8_t, 3>>, 3> key_colors;

        /// Offsets for key remapping ( key → data positon ) ["string":[ [x,y], [x,y], [x,y] ]]
        const static std::map<std::string_view, std::array<std::array<uint8_t, 2>, 3>> keymap_offsets;
        /// Keymap options (what a key can do when pressed)  ( option → code )
        const static std::map<std::string_view, std::array<uint8_t, 3>> keymap_options;
        /// Stores current keymapping ( key → option)
        std::array<std::map<std::string, std::string>, 3> keymap;

        /// All macros
        std::array<rgb_keyboard::macro, 100> macros;
    };

}  // namespace rgb_keyboard

#endif
