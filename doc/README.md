# Source code documentation

Doxygen is used to document the source code, if you have it installed run

```
doxygen Doxyfile
```

to generate the documentation in html format. The files will be placed in a new directory called documentation.

# Basic information about the USB protocol

The individual data packets send to the keyboard have a length of 64 bytes + 64 bytes of usb header (this can be ignored, they show up as length 128 in wireshark though). Data is written to usb
endpoint 3, and read from usb endpoint 2. After each write, 64 bytes must be read.

To set some property on the keyboard, first a start packet (data_start) is send, this packet starts with 0x04 0x01 0x00 0x01 and the rest are zeroes. The next step are some packets for the specific
property. Depending on the specific setting, the number of these packets varies. To finish the process the data_end packet is written (containing 0x04 0x02 0x00 0x02, rest zeroes).

The data packets can be found in include/data*.cpp.

When using the official software in many cases some bytes in the beginning of the settings data are changed depending on the particular values for the setting, this appears to be some sort of
checksum. However these don't seem to be important and are therefore ignored.

## Example

To accomodate the differences between the the Ajazz AK33 and other keyboards sending data is done through the write_data() function (include/helpers.cpp).

The following code example shows how the process would be done without the write_data() function.

```
//write start data packet to endpoint 3
res += libusb_interrupt_transfer( handle, 0x03, data_start,	64, &transferred, 1000);

//read from endpoint 2
res += libusb_interrupt_transfer( handle, 0x82, buffer, 64, &transferred, 1000);

//write brightness data packet to endpoint 3
res += libusb_interrupt_transfer( handle, 0x03, data_settings, 64, &transferred, 1000);

//read from endpoint 2
res += libusb_interrupt_transfer( handle, 0x82, buffer, 64, &transferred, 1000);

//write end data packet to endpoint 3
res += libusb_interrupt_transfer( handle, 0x03, data_end, 64, &transferred, 1000);

//read from endpoint 2
res += libusb_interrupt_transfer( handle, 0x82, buffer, 64, &transferred, 1000);
```

## Keymapping

On the ANSI version of the software 8 data packets are send, on the ISO version 11, (in addition to that the start and end packets). The function of each key is represented by 3 bytes each, the
position of these bytes in the 8 or 11 data packets is specified by the map keymap_offsets (include/constructor.cpp and include/writers.cpp). The meaning of these bytes can be found in the map
keymap_options (include/constructor.cpp).

# Capturing USB data

For this section i am assuming you are running wireshark on linux, and have a VM with the official software and USB passthrough set up. The process is identical if you want to capture the
communication of any Linux software. For further questions and if you are on Windows consult the wireshark documentation.

1. load the usbmon kernel module ``sudo modprobe usbmon``
2. identify the USB bus id and device number by running lsusb
3. open wireshark (may require root) and open the correct usbmon interface
4. set up the display filter in wireshark (see screenshot for an example)
5. start the capture, trigger some action, stop the capture, save if needed, repeat

![wireshark screenshot](https://github.com/dokutan/rgb_keyboard/raw/master/doc/screenshot-wireshark.png "wireshark screenshot")
