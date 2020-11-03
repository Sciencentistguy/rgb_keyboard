#include "rgb_keyboard.h"

// reader functions

int rgb_keyboard::keyboard::read_active_profile() {
    // prepare data packet
    uint8_t data_read[64];
    std::copy(std::begin(data_read), std::end(data_read), std::begin(data_read));
    data_read[1] = 0x2f;
    data_read[3] = 0x03;
    data_read[4] = 0x2c;

    int transferred = 0;
    // write data packet to endpoint 3
    int res = libusb_interrupt_transfer(handle, 0x03, data_read, 64, &transferred, 1000);

    // read from endpoint 2
    uint8_t buffer[64];
    res += libusb_interrupt_transfer(handle, 0x82, buffer, 64, &transferred, 1000);

    // check if valid profile number
    if (buffer[18] + 1 >= 1 && buffer[18] + 1 <= 3) {
        active_profile = buffer[18] + 1;
        return 0;
    } else {
        return 1;
    }
}

int rgb_keyboard::keyboard::read_led_settings() {
    // prepare data packets
    uint8_t data_read_1[64], data_read_2[64], data_read_3[64];
    std::copy(std::begin(data_read), std::end(data_read), std::begin(data_read_1));
    std::copy(std::begin(data_read), std::end(data_read), std::begin(data_read_2));
    std::copy(std::begin(data_read), std::end(data_read), std::begin(data_read_3));

    data_read_1[1] = 0x3d;
    data_read_1[3] = 0x05;
    data_read_1[4] = 0x38;
    data_read_1[5] = 0x00;

    data_read_2[1] = 0x67;
    data_read_2[3] = 0x05;
    data_read_2[4] = 0x38;
    data_read_2[5] = 0x2a;

    data_read_3[1] = 0x91;
    data_read_3[3] = 0x05;
    data_read_3[4] = 0x38;
    data_read_3[5] = 0x54;

    int transferred = 0;
    // write data packet 1 to endpoint 3
    int res = libusb_interrupt_transfer(handle, 0x03, data_read_1, 64, &transferred, 1000);

    uint8_t input_buffer[3][64];
    // read from endpoint 2
    res += libusb_interrupt_transfer(handle, 0x82, input_buffer[0], 64, &transferred, 1000);

    // write data packet 2 to endpoint 3
    res += libusb_interrupt_transfer(handle, 0x03, data_read_2, 64, &transferred, 1000);

    // read from endpoint 2
    res += libusb_interrupt_transfer(handle, 0x82, input_buffer[1], 64, &transferred, 1000);

    // write data packet 3 to endpoint 3
    res += libusb_interrupt_transfer(handle, 0x03, data_read_3, 64, &transferred, 1000);

    // read from endpoint 2
    res += libusb_interrupt_transfer(handle, 0x82, input_buffer[2], 64, &transferred, 1000);

    // extract information
    for (int i = 0; i < 3; i++) {
        // color
        color_r[i] = input_buffer[i][13];
        color_g[i] = input_buffer[i][14];
        color_b[i] = input_buffer[i][15];
        if (input_buffer[i][12] == 1) {
            rainbow[i] = true;
        } else {
            rainbow[i] = false;
        }

        // brightness
        if (input_buffer[i][9] >= brightness_min && input_buffer[i][9] <= brightness_max)
            brightness[i] = input_buffer[i][9];

        // speed
        if (3 - input_buffer[i][10] >= speed_min && 3 - input_buffer[i][10] <= speed_max)
            speed[i] = 3 - input_buffer[i][10];

        // direction
        if (input_buffer[i][11] == 0xff)
            direction[i] = directions::left;
        else if (input_buffer[i][11] == 0x00)
            direction[i] = directions::right;

        // led mode
        switch (input_buffer[i][8]) {
            case 0x01:
                mode[i] = modes::horizontal_wave;
                break;
            case 0x02:
                mode[i] = modes::pulse;
                break;
            case 0x03:
                mode[i] = modes::hurricane;
                break;
            case 0x04:
                mode[i] = modes::breathing_color;
                break;
            case 0x05:
                mode[i] = modes::breathing;
                break;
            case 0x06:
                mode[i] = modes::fixed;
                break;
            case 0x07:
                mode[i] = modes::reactive_single;
                break;
            case 0x08:
                mode[i] = modes::reactive_ripple;
                break;
            case 0x09:
                mode[i] = modes::reactive_horizontal;
                break;
            case 0x0a:
                mode[i] = modes::waterfall;
                break;
            case 0x0b:
                mode[i] = modes::swirl;
                break;
            case 0x0c:
                mode[i] = modes::vertical_wave;
                break;
            case 0x0d:
                mode[i] = modes::sine;
                break;
            case 0x0e:
                mode[i] = modes::vortex;
                break;
            case 0x0f:
                mode[i] = modes::rain;
                break;
            case 0x10:
                mode[i] = modes::diagonal_wave;
                break;
            case 0x11:
                mode[i] = modes::reactive_color;
                break;
            case 0x12:
                mode[i] = modes::ripple;
                break;
            case 0x13:
                mode[i] = modes::off;
                break;
            case 0x14:
                mode[i] = modes::custom;
                break;
            default:
                mode[i] = modes::undefined;
                break;
        }

        // reactive-color variant
        if (mode[i] == modes::reactive_color) {
            switch (input_buffer[i][16]) {
                case 0x00:
                    variant[i] = mode_variants::color_red;
                    break;
                case 0x01:
                    variant[i] = mode_variants::color_yellow;
                    break;
                case 0x02:
                    variant[i] = mode_variants::color_green;
                    break;
                case 0x03:
                    variant[i] = mode_variants::color_blue;
                    break;
                default:
                    variant[i] = mode_variants::undefined;
                    break;
            }
        }

        // USB poll rate
        if (input_buffer[i][23] == 0x00)
            report_rate[i] = report_rates::r_125Hz;
        else if (input_buffer[i][23] == 0x01)
            report_rate[i] = report_rates::r_250Hz;
        else if (input_buffer[i][23] == 0x02)
            report_rate[i] = report_rates::r_500Hz;
        else if (input_buffer[i][23] == 0x03)
            report_rate[i] = report_rates::r_1000Hz;
    }

    return 0;
}
