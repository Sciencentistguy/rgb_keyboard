#include "rgb_keyboard.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include <cxxopts.hpp>
#include <getopt.h>

#include "print_help.h"

int main(int argc, char** argv) {
    cxxopts::Options parser{"rgb_keyboard", "This software controls the RGB lighting on some keyboards."};
    // clang-format off
    parser.add_options()
        ("h,help", "")
        ("c,color", "", cxxopts::value<std::string>())
        ("b,brightness", "", cxxopts::value<int>())
        ("s,speed", "", cxxopts::value<int>())
        ("d,direction", "", cxxopts::value<std::string>())
        ("l,leds", "", cxxopts::value<std::string>())
        ("v,variant", "", cxxopts::value<std::string>())
        ("P,custom-pattern", "", cxxopts::value<std::string>())
        ("K,custom-keys", "", cxxopts::value<std::string>())
        ("R,report-rate", "", cxxopts::value<int>())
        ("M,keymap", "", cxxopts::value<int>())
        ("L,list-keys", "", cxxopts::value<int>())
        ("B,bus", "", cxxopts::value<int>())
        ("D,device", "", cxxopts::value<int>())
        ("p,profile", "", cxxopts::value<int>())
        ("a,active", "", cxxopts::value<int>())
        ("k,kernel-driver", "")
        ("A,ajazzak33", "")
        ("I,interface0", "")
        ("r,read", "");
    // clang-format on

    // these variables store the commandline options
    auto options = parser.parse(argc, argv);

    //    bool flag_direction = false;
    //    bool flag_leds = false;
    //    bool flag_variant = false;
    //    bool flag_custom_pattern = false;
    //    bool flag_custom_keys = false;
    //    bool flag_report_rate = false;
    //    bool flag_keymap = false;
    //    bool flag_list_keys = false;
    //    bool flag_bus = false;
    //    bool flag_device = false;
    //    bool flag_profile = false;
    //    bool flag_active = false;
    //    bool flag_kernel_driver = false;
    //    bool flag_ajazzak33 = false;
    //    bool flag_read = false;

    //    if (options["help"].as<bool>()) {
    //        print_help();
    //        return -1;
    //    }

    //    std::string string_direction;
    //    std::string string_leds;
    //    std::string string_variant;
    //    std::string string_custom_pattern;
    //    std::string string_custom_keys;
    //    std::string string_report_rate;
    //    std::string string_keymap;
    //    std::string string_list_keys;
    //    std::string string_bus;
    //    std::string string_device;
    //    std::string string_active;
    //    std::string string_profile;

    // check number of commandline options
    //    if (argc == 1) {
    //        print_help();
    //        return 0;
    //    }
    // keyboard object
    rgb_keyboard::keyboard kbd;

    // set compatbility mode
    if (options.count("ajazzak33") != 0) {
        kbd.set_ajazzak33_compatibility(true);
    }

    // parse list keys flag
    if (options.count("list-keys") != 0) {
        const auto& list_keys = options["list-keys"].as<std::string>();
        if (list_keys == "led" or list_keys == "custom") {
            // list physical keys for custom led pattern
            std::cout << "Keynames for custom pattern:\n(Some keys might have multiple names)\n\n";
            rgb_keyboard::keyboard::print_keycodes_led();
        } else if (list_keys == "map" or list_keys == "keymap") {
            // list physical keys for key remapping
            std::cout << "Keynames of physical keys for remapping:\n(Some keys might have multiple names)\n\n";
            rgb_keyboard::keyboard::print_keycodes_remap();
        } else if (list_keys == "function" or list_keys == "option") {
            // list options for remapping
            std::cout << "Options for key remapping:\n(Some options might have multiple names)\n\n";
            rgb_keyboard::keyboard::print_keycodes_options();
        } else {
            std::cout << "Valid options:\n";
            std::cout << "\"--list-keys led\" or \"--list-keys custom\"\n";
            std::cout << "\"--list-keys map\" or \"--list-keys keymap\"\n";
            std::cout << "\"--list-keys function\" or \"--list-keys option\"\n";
        }

        return 0;
    }

    // detach kernel driver ?
    if (options.count("kernel-driver") != 0)
        kbd.set_detach_kernel_driver(false);

    // open interface 0 ?
    if (options.count("interface0") != 0)
        kbd.set_open_interface_0(false);

    // open keyboard, apply settigns, close keyboard
    try {
        // open keyboard
        if ((options.count("bus") != 0) != (options.count("device") != 0)) {  // only -B xor -D: error
            std::cerr << "--bus and --device must be used together\n";
            return 1;
        }
        if ((options.count("bus") != 0) and (options.count("device") != 0)) {  // -B and -D
            const auto& bus = options["bus"].as<int>();
            const auto& device = options["device"].as<int>();

            // check -B and -D arguments
            if (kbd.open_keyboard_bus_device(bus, device) != 0) {
                std::cerr << "Could not open keyboard, check hardware and permissions.\nTry with or without the --kernel-driver option.\n";
                return 1;
            }

        } else {  // open with default vid and pid
            if (kbd.open_keyboard() != 0) {
                std::cerr << "Could not open keyboard, check hardware and permissions.\nTry with or without the --kernel-driver option.\n";
                return 1;
            }
        }

        // read settings from keyboard
        if ((options.count("read") != 0) && (options.count("ajazzak33") != 0)) {
            std::cout << "This feature is currently not supported for the Ajazz AK33\n";
            std::cout << "You can help to implement it by capturing USB communication, for more information open an issue on Github.\n";
        } else if (options.count("read") != 0) {
            // a copy of the main kbd object, this prevents unintentional behaviour
            rgb_keyboard::keyboard kbd_in = kbd;

            std::cout << "This feature is experimental, not everything is read, please report bugs\n";

            // active profile
            kbd_in.read_active_profile();
            std::cout << "Active profile: " << kbd_in.get_active_profile() << "\n";

            // read settings
            kbd_in.read_led_settings();

            // iterate over profiles and print settings
            for (int i = 1; i < 4; i++) {
                kbd_in.set_profile(i);
                std::cout << "\nProfile " << kbd_in.get_profile() << ":\n";

                // led mode
                std::cout << "Led mode: ";
                switch (kbd_in.get_mode()) {
                    case rgb_keyboard::keyboard::modes::horizontal_wave:
                        std::cout << "horizontal-wave\n";
                        break;
                    case rgb_keyboard::keyboard::modes::pulse:
                        std::cout << "pulse\n";
                        break;
                    case rgb_keyboard::keyboard::modes::hurricane:
                        std::cout << "hurricane\n";
                        break;
                    case rgb_keyboard::keyboard::modes::breathing_color:
                        std::cout << "breathing-color\n";
                        break;
                    case rgb_keyboard::keyboard::modes::breathing:
                        std::cout << "breathing\n";
                        break;
                    case rgb_keyboard::keyboard::modes::fixed:
                        std::cout << "fixed\n";
                        break;
                    case rgb_keyboard::keyboard::modes::reactive_single:
                        std::cout << "reactive-single\n";
                        break;
                    case rgb_keyboard::keyboard::modes::reactive_ripple:
                        std::cout << "reactive-ripple\n";
                        break;
                    case rgb_keyboard::keyboard::modes::reactive_horizontal:
                        std::cout << "reactive-horizontal\n";
                        break;
                    case rgb_keyboard::keyboard::modes::waterfall:
                        std::cout << "waterfall\n";
                        break;
                    case rgb_keyboard::keyboard::modes::swirl:
                        std::cout << "swirl\n";
                        break;
                    case rgb_keyboard::keyboard::modes::vertical_wave:
                        std::cout << "vertical-wave\n";
                        break;
                    case rgb_keyboard::keyboard::modes::sine:
                        std::cout << "sine\n";
                        break;
                    case rgb_keyboard::keyboard::modes::vortex:
                        std::cout << "vortex\n";
                        break;
                    case rgb_keyboard::keyboard::modes::rain:
                        std::cout << "rain\n";
                        break;
                    case rgb_keyboard::keyboard::modes::diagonal_wave:
                        std::cout << "diagonal-wave\n";
                        break;
                    case rgb_keyboard::keyboard::modes::reactive_color:
                        std::cout << "reactive-color\n";
                        break;
                    case rgb_keyboard::keyboard::modes::ripple:
                        std::cout << "ripple\n";
                        break;
                    case rgb_keyboard::keyboard::modes::off:
                        std::cout << "off\n";
                        break;
                    case rgb_keyboard::keyboard::modes::custom:
                        std::cout << "custom\n";
                        break;
                    default:
                        std::cout << "unknown\n";
                        break;
                }

                // reactive-color variant
                if (kbd_in.get_mode() == rgb_keyboard::keyboard::modes::reactive_color) {
                    std::cout << "Variant: ";
                    switch (kbd_in.get_variant()) {
                        case rgb_keyboard::keyboard::mode_variants::color_red:
                            std::cout << "red\n";
                            break;
                        case rgb_keyboard::keyboard::mode_variants::color_yellow:
                            std::cout << "yellow\n";
                            break;
                        case rgb_keyboard::keyboard::mode_variants::color_green:
                            std::cout << "green\n";
                            break;
                        case rgb_keyboard::keyboard::mode_variants::color_blue:
                            std::cout << "blue\n";
                            break;
                        default:
                            std::cout << "unknown\n";
                            break;
                    }
                }

                // direction
                if (kbd_in.get_direction() == rgb_keyboard::keyboard::directions::left)
                    std::cout << "Direction: left\n";
                else if (kbd_in.get_direction() == rgb_keyboard::keyboard::directions::right)
                    std::cout << "Direction: right\n";

                // color
                if (kbd_in.get_rainbow()) {
                    std::cout << "Color: multi\n";
                } else {
                    std::cout << "Color: ";
                    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) kbd_in.get_color_r();
                    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) kbd_in.get_color_g();
                    std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) kbd_in.get_color_b();
                    std::cout << "\n" << std::dec << std::setfill(' ') << std::setw(0);
                }

                // brightness
                std::cout << "Brightness: " << kbd_in.get_brightness() << "\n";

                // speed
                std::cout << "Speed: " << kbd_in.get_speed() << "\n";

                // usb poll rate
                std::cout << "Report rate: ";
                if (kbd_in.get_report_rate() == rgb_keyboard::keyboard::report_rates::r_125Hz)
                    std::cout << "125 Hz\n";
                else if (kbd_in.get_report_rate() == rgb_keyboard::keyboard::report_rates::r_250Hz)
                    std::cout << "250 Hz\n";
                else if (kbd_in.get_report_rate() == rgb_keyboard::keyboard::report_rates::r_500Hz)
                    std::cout << "500 Hz\n";
                else if (kbd_in.get_report_rate() == rgb_keyboard::keyboard::report_rates::r_1000Hz)
                    std::cout << "1000 Hz\n";
                else
                    std::cout << "unknown\n";
            }
        }

        // parse active flag, set active profile
        if (options.count("active") != 0) {
            const auto& active = options["active"].as<int>();
            if (active > 3 or active < 1) {
                std::cerr << "Invalid profile, expected 1-3\n";
                kbd.close_keyboard();
                return 1;
            }
            kbd.set_active_profile(active);
            kbd.write_active_profile();
        }

        // parse profile flag, set profile (to which profile settings are applied)
        if (options.count("profile") != 0) {
            const auto& profile = options["profile"].as<int>();
            if (profile > 3 or profile < 1) {
                std::cerr << "Invalid profile, expected 1-3\n";
                kbd.close_keyboard();
                return 1;
            }
            kbd.set_profile(profile);
        }

        // parse leds flag, set led pattern
        if (options.count("leds") != 0) {
            const auto& leds = options["leds"].as<std::string>();
            const std::map<std::string, rgb_keyboard::keyboard::modes> mode_list{{"fixed", rgb_keyboard::keyboard::modes::fixed},
                                                                                 {"sine", rgb_keyboard::keyboard::modes::sine},
                                                                                 {"rain", rgb_keyboard::keyboard::modes::rain},
                                                                                 {"waterfall", rgb_keyboard::keyboard::modes::waterfall},
                                                                                 {"vortex", rgb_keyboard::keyboard::modes::vortex},
                                                                                 {"swirl", rgb_keyboard::keyboard::modes::swirl},
                                                                                 {"breathing", rgb_keyboard::keyboard::modes::breathing},
                                                                                 {"breathing-color", rgb_keyboard::keyboard::modes::breathing_color},
                                                                                 {"reactive-ripple", rgb_keyboard::keyboard::modes::reactive_ripple},
                                                                                 {"reactive-single", rgb_keyboard::keyboard::modes::reactive_single},
                                                                                 {"reactive-horizontal", rgb_keyboard::keyboard::modes::reactive_horizontal},
                                                                                 {"reactive-color", rgb_keyboard::keyboard::modes::reactive_color},
                                                                                 {"horizontal-wave", rgb_keyboard::keyboard::modes::horizontal_wave},
                                                                                 {"vertical-wave", rgb_keyboard::keyboard::modes::vertical_wave},
                                                                                 {"diagonal-wave", rgb_keyboard::keyboard::modes::diagonal_wave},
                                                                                 {"pulse", rgb_keyboard::keyboard::modes::pulse},
                                                                                 {"hurricane", rgb_keyboard::keyboard::modes::hurricane},
                                                                                 {"ripple", rgb_keyboard::keyboard::modes::ripple},
                                                                                 {"custom", rgb_keyboard::keyboard::modes::custom},
                                                                                 {"off", rgb_keyboard::keyboard::modes::off}};

            if (mode_list.find(leds) != mode_list.end()) {
                // parse variant flag (variant for reactive-color)
                if (options.count("variant") != 0) {
                    const auto& variant = options["variant"].as<std::string>();
                    if (variant == "red") {
                        kbd.set_variant(rgb_keyboard::keyboard::mode_variants::color_red);
                    } else if (variant == "yellow") {
                        kbd.set_variant(rgb_keyboard::keyboard::mode_variants::color_yellow);
                    } else if (variant == "green") {
                        kbd.set_variant(rgb_keyboard::keyboard::mode_variants::color_green);
                    } else if (variant == "blue") {
                        kbd.set_variant(rgb_keyboard::keyboard::mode_variants::color_blue);
                    } else {
                        std::cerr << "Unknown variant for reactive-color.\n";
                        kbd.close_keyboard();
                        return 1;
                    }

                    kbd.write_variant();
                }

                // parse custom pattern flag
                if (options.count("custom-pattern") != 0) {
                    const auto& custom_pattern = options["custom-pattern"].as<std::string>();
                    // set custom pattern
                    if (kbd.load_custom(custom_pattern) == 0) {
                        kbd.write_custom();
                    } else {
                        std::cerr << "Couldn't open custom pattern file.\n";
                        kbd.close_keyboard();
                        return 1;
                    }
                }

                // write led pattern
                kbd.set_mode(mode_list.at(leds));
                kbd.write_mode();

            } else {
                std::cerr << "Unknown led pattern '" << leds << "'. Valid options are:\n";
                std::cerr << "fixed, sine, rain, waterfall, vortex, swirl, breathing, breathing-color,\n";
                std::cerr << "reactive-ripple, reactive-single, reactive-horizontal, reactive-color,\n";
                std::cerr << "horizontal-wave, vertical-wave, diagonal-wave, pulse, hurricane, ripple, custom, off\n";
                kbd.close_keyboard();
                return 1;
            }
        }

        // parse custom keys flag
        if (options.count("custom-keys") != 0) {
            const auto& custom_keys = options["custom-keys"].as<std::string>();
            kbd.set_custom_keys(custom_keys);
            kbd.write_custom();
        }

        // parse color flag
        if (options.count("color") != 0) {
            const auto& color = options["color"].as<std::string>();
            // set color
            if (color == "multi") {  // multicolor
                kbd.set_rainbow(true);
                kbd.write_color();
            } else if (std::regex_match(color, std::regex("[0-9a-fA-F]{6}"))) {  // normal color
                kbd.set_rainbow(false);
                kbd.set_color(stoi(color.substr(0, 2), nullptr, 16), stoi(color.substr(2, 2), nullptr, 16), stoi(color.substr(4, 2), nullptr, 16));
                kbd.write_color();
            } else {  // wrong format
                std::cerr << "Wrong color format, expected rrggbb or 'multi'.\n";
                kbd.close_keyboard();
                return 1;
            }
        }

        // parse brightness flag
        if (options.count("brightness") != 0) {
            // set brightness
            const auto& brightness = options["brightness"].as<int>();
            if (brightness > 9 or brightness < 0) {
                std::cerr << "Wrong brightness format, expected 0-9 (0-5 for AjazzAK33).\n";
                kbd.close_keyboard();
                return 1;
            }
            kbd.set_brightness(brightness);
            kbd.write_brightness();
        }

        // parse speed flag
        if (options.count("speed") != 0) {
            const auto& speed = options["speed"].as<int>();
            if (speed > 3 or speed < 0) {
                std::cerr << "Wrong speed format, expected 0-3.\n";
                kbd.close_keyboard();
                return 1;
            }
            kbd.set_speed(speed);
            kbd.write_speed();
        }
        // parse direction flag
        if (options.count("direction") != 0) {
            const auto& direction = options["direction"].as<std::string>();
            // set direction
            if (direction == "left" or direction == "up" or direction == "inwards") {
                kbd.set_direction(rgb_keyboard::keyboard::directions::left);
                kbd.write_direction();
            } else if (direction == "right" or direction == "down" or direction == "outwards") {
                kbd.set_direction(rgb_keyboard::keyboard::directions::right);
                kbd.write_direction();
            } else {
                std::cerr << "Unknown direction.\n";
                kbd.close_keyboard();
                return 1;
            }
        }

        // parse report rate flag
        if (options.count("report-rate") != 0) {
            const auto& report_rate = options["report-rate"].as<int>();

            switch (report_rate) {
                case 125:
                    kbd.set_report_rate(rgb_keyboard::keyboard::report_rates::r_125Hz);
                    kbd.write_report_rate();
                    break;
                case 250:
                    kbd.set_report_rate(rgb_keyboard::keyboard::report_rates::r_250Hz);
                    kbd.write_report_rate();
                    break;
                case 500:
                    kbd.set_report_rate(rgb_keyboard::keyboard::report_rates::r_500Hz);
                    kbd.write_report_rate();
                    break;
                case 1000:
                    kbd.set_report_rate(rgb_keyboard::keyboard::report_rates::r_1000Hz);
                    kbd.write_report_rate();
                    break;
                default:
                    std::cerr << "Unsupported report rate.\n";
                    kbd.close_keyboard();
                    return 1;
            }
        }

        // parse keymap flag
        if ((options.count("keymap") != 0) and !(options.count("ajazzak33") != 0)) {
            const auto& keymap = options["keymap"].as<std::string>();
            // ask user for confirmation?
            std::cout << R"(Remapping the keys is experimental and potentially dangerous.
On ISO-layout boards and on the Ajazz AK33 this has been reported to mess up all keys.
You can help to improve it by capturing USB communication, for more information open an issue on Github.
If you accept the risk of permanent damage to the keyboard, type YES and press enter to continue.
Anything else will cancel this process.
)";

            std::string user_input;
            std::cin >> user_input;

            if (user_input == "YES") {
                if (kbd.load_keymap(keymap) == 0) {
                    kbd.write_key_mapping_ansi();
                } else {
                    std::cerr << "Couldn't open keymap file.\n";
                    kbd.close_keyboard();
                    return 1;
                }
            } else {
                std::cout << "Not remapping the keys.\n";
            }
        }

        // catch exception
    } catch (std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
        kbd.close_keyboard();
        return 1;
    }

    // close keyboard
    kbd.close_keyboard();
    return 0;
}
