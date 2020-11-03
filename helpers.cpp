#include "rgb_keyboard.h"

// helper functions

// init libusb and open keyboard with default vid and pid
int rgb_keyboard::keyboard::open_keyboard() {
    // libusb init
    int res = libusb_init(nullptr);
    if (res < 0) {
        return res;
    }

    // open device, try to open keyboard with each pid
    for (auto pid : keyboard_pid) {
        handle = libusb_open_device_with_vid_pid(nullptr, keyboard_vid, pid);

        if (handle)
            break;
    }

    if (!handle) {  // no device opened
        res++;
        return res;
    }

    if (detach_kernel_driver) {
        if (open_interface_0) {
            // detach kernel driver on interface 0 if active
            if (libusb_kernel_driver_active(handle, 0)) {
                res += libusb_detach_kernel_driver(handle, 0);
                if (res == 0) {
                    detached_driver_0 = true;
                } else {
                    return res;
                }
            }
        }

        // detach kernel driver on interface 1 if active
        if (libusb_kernel_driver_active(handle, 1)) {
            res += libusb_detach_kernel_driver(handle, 1);
            if (res == 0) {
                detached_driver_1 = true;
            } else {
                return res;
            }
        }
    }

    if (open_interface_0) {
        // claim interface 0
        res += libusb_claim_interface(handle, 0);
        if (res != 0) {
            return res;
        }
    }

    // claim interface 1
    res += libusb_claim_interface(handle, 1);
    if (res != 0) {
        return res;
    }

    return res;
}

// init libusb and open keyboard with bus and device id
int rgb_keyboard::keyboard::open_keyboard_bus_device(uint8_t bus, uint8_t device) {
    // libusb init
    int res = libusb_init(nullptr);
    if (res < 0) {
        return res;
    }

    // open device (_handle)

    libusb_device** dev_list;                                       // device list
    ssize_t num_devs = libusb_get_device_list(nullptr, &dev_list);  // get device list

    if (num_devs < 0)
        return 1;

    for (ssize_t i = 0; i < num_devs; i++) {
        // check if correct bus and device
        if (bus == libusb_get_bus_number(dev_list[i]) && device == libusb_get_device_address(dev_list[i])) {
            // open device
            if (libusb_open(dev_list[i], &handle) != 0) {
                return 1;
            } else {
                break;
            }
        }
    }

    // free device list, unreference devices
    libusb_free_device_list(dev_list, 1);

    if (detach_kernel_driver) {
        if (open_interface_0) {
            // detach kernel driver on interface 0 if active
            if (libusb_kernel_driver_active(handle, 0)) {
                res += libusb_detach_kernel_driver(handle, 0);
                if (res == 0) {
                    detached_driver_0 = true;
                } else {
                    return res;
                }
            }
        }

        // detach kernel driver on interface 1 if active
        if (libusb_kernel_driver_active(handle, 1)) {
            res += libusb_detach_kernel_driver(handle, 1);
            if (res == 0) {
                detached_driver_1 = true;
            } else {
                return res;
            }
        }
    }

    if (open_interface_0) {
        // claim interface 0
        res += libusb_claim_interface(handle, 0);
        if (res != 0) {
            return res;
        }
    }

    // claim interface 1
    res += libusb_claim_interface(handle, 1);
    if (res != 0) {
        return res;
    }

    return res;
}

// close keyboard
int rgb_keyboard::keyboard::close_keyboard() {
    // release interface 0 and 1
    if (open_interface_0) {
        libusb_release_interface(handle, 0);
    }
    libusb_release_interface(handle, 1);

    // attach kernel driver for interface 0
    if (detached_driver_0 && open_interface_0) {
        libusb_attach_kernel_driver(handle, 0);
    }

    // attach kernel driver for interface 1
    if (detached_driver_0) {
        libusb_attach_kernel_driver(handle, 1);
    }

    // exit libusb
    libusb_exit(nullptr);

    return 0;
}

// send data
int rgb_keyboard::keyboard::write_data(const unsigned char* data, int length) {
    int result = 0;       // return value
    int transferred = 0;  // transferred bytes, gets ignored for now
    uint8_t buffer[64];   // buffer to receive data

    if (ajazzak33Compatibility) {
        // write data packet to endpoint 0
        result += libusb_control_transfer(handle, 0x21, 0x09, 0x0204, 0x0001, const_cast<unsigned char*>(data), length, 1000);
        // read from endpoint 2
        result += libusb_interrupt_transfer(handle, 0x82, buffer, 64, &transferred, 1000);

    } else {
        // write data packet to endpoint 3
        result += libusb_interrupt_transfer(handle, 0x03, const_cast<unsigned char*>(data), length, &transferred, 1000);
        // read from endpoint 2
        result += libusb_interrupt_transfer(handle, 0x82, buffer, 64, &transferred, 1000);
    }

    return result;
}
