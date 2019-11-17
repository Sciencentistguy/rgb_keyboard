/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

//constructor
rgb_keyboard::keyboard::keyboard(){
	
	_direction = d_undefined;
	_mode = m_undefined;
	_variant = v_undefined;
	
	//keycodes for custom key color
	_keycodes["Esc"] = { 0x57, 0x03, 0x00 };
	_keycodes["F1"] = { 0x5a, 0x06, 0x00 };
	_keycodes["F2"] = { 0x5d, 0x09, 0x00 };
	_keycodes["F3"] = { 0x60, 0x0c, 0x00 };
	_keycodes["F4"] = { 0x63, 0x0f, 0x00 };
	_keycodes["F5"] = { 0x66, 0x12, 0x00 };
	_keycodes["F6"] = { 0x69, 0x15, 0x00 };
	_keycodes["F7"] = { 0x6c, 0x18, 0x00 };
	_keycodes["F8"] = { 0x6f, 0x1b, 0x00 };
	_keycodes["F9"] = { 0x72, 0x1e, 0x00 };
	_keycodes["F10"] = { 0x75, 0x21, 0x00 };
	_keycodes["F11"] = { 0x78, 0x24, 0x00 };
	_keycodes["F12"] = { 0x7b, 0x27, 0x00 };
	_keycodes["PrtSc"] = { 0x93, 0x3e, 0x01 };
	_keycodes["ScrLk"] = { 0x96, 0x41, 0x01 };
	_keycodes["Pause"] = { 0x99, 0x44, 0x01 };
	_keycodes["Tilde"] = { 0x8a, 0x36, 0x00 };
	_keycodes["1"] = { 0x8d, 0x39, 0x00 };
	_keycodes["2"] = { 0x90, 0x3c, 0x00 };
	_keycodes["3"] = { 0x93, 0x3f, 0x00 };
	_keycodes["4"] = { 0x96, 0x42, 0x00 };
	_keycodes["5"] = { 0x99, 0x45, 0x00 };
	_keycodes["6"] = { 0x9c, 0x48, 0x00 };
	_keycodes["7"] = { 0x9f, 0x4b, 0x00 };
	_keycodes["8"] = { 0xa2, 0x4e, 0x00 };
	_keycodes["9"] = { 0xa5, 0x51, 0x00 };
	_keycodes["0"] = { 0xa8, 0x54, 0x00 };
	_keycodes["Minus"] = { 0xab, 0x57, 0x00 };
	_keycodes["Equals"] = { 0xae, 0x5a, 0x00 };
	_keycodes["Backspace"] = { 0x7b, 0x26, 0x01 };
	_keycodes["Insert"] = { 0x9f, 0x4a, 0x01 };
	_keycodes["Home"] = { 0xa2, 0x4d, 0x01 };
	_keycodes["PgUp"] = { 0xa5, 0x50, 0x01 };
	_keycodes["Delete"] = { 0xa8, 0x53, 0x01 };
	_keycodes["End"] = { 0xab, 0x56, 0x01 };
	_keycodes["PgDn"] = { 0xae, 0x59, 0x01 };
	_keycodes["Tab"] = { 0xbd, 0x69, 0x00 };
	_keycodes["q"] = { 0xc0, 0x6c, 0x00 };
	_keycodes["w"] = { 0xc3, 0x6f, 0x00 };
	_keycodes["e"] = { 0xc6, 0x72, 0x00 };
	_keycodes["r"] = { 0xc9, 0x75, 0x00 };
	_keycodes["t"] = { 0xcc, 0x78, 0x00 };
	_keycodes["y"] = { 0xcf, 0x7b, 0x00 };
	_keycodes["u"] = { 0xd2, 0x7e, 0x00 };
	_keycodes["i"] = { 0xd5, 0x81, 0x00 };
	_keycodes["o"] = { 0xd8, 0x84, 0x00 };
	_keycodes["p"] = { 0xdb, 0x87, 0x00 };
	_keycodes["Bracket_l"] = { 0xde, 0x8a, 0x00 };
	_keycodes["Bracket_r"] = { 0xe1, 0x8d, 0x00 };
	_keycodes["Backslash"] = { 0x14, 0xc0, 0x00 };
	_keycodes["Up"] = { 0x75, 0x20, 0x01 };
	_keycodes["Left"] = { 0x6f, 0x1a, 0x01 };
	_keycodes["Down"] = { 0x72, 0x1d, 0x01 };
	_keycodes["Right"] = { 0x78, 0x23, 0x01 };
	_keycodes["Caps_Lock"] = { 0xf0, 0x9c, 0x00 };
	_keycodes["a"] = { 0xf3, 0x9f, 0x00 };
	_keycodes["s"] = { 0xf6, 0xa2, 0x00 };
	_keycodes["d"] = { 0xf9, 0xa5, 0x00 };
	_keycodes["f"] = { 0xfc, 0xa8, 0x00 };
	_keycodes["g"] = { 0xff, 0xab, 0x00 };
	_keycodes["h"] = { 0x02, 0xae, 0x00 };
	_keycodes["j"] = { 0x05, 0xb1, 0x00 };
	_keycodes["k"] = { 0x08, 0xb4, 0x00 };
	_keycodes["l"] = { 0x0b, 0xb7, 0x00 };
	_keycodes["Semicolon"] = { 0x0e, 0xba, 0x00 };
	_keycodes["Apostrophe"] = { 0x11, 0xbd, 0x00 };
	_keycodes["Return"] = { 0x47, 0xf3, 0x00 };
	_keycodes["Shift_l"] = { 0x23, 0xcf, 0x00 };
	_keycodes["z"] = { 0x26, 0xd2, 0x00 };
	_keycodes["x"] = { 0x29, 0xd5, 0x00 };
	_keycodes["c"] = { 0x2c, 0xd8, 0x00 };
	_keycodes["v"] = { 0x2f, 0xdb, 0x00 };
	_keycodes["b"] = { 0x32, 0xde, 0x00 };
	_keycodes["n"] = { 0x35, 0xe1, 0x00 };
	_keycodes["m"] = { 0x38, 0xe4, 0x00 };
	_keycodes["Comma"] = { 0x3b, 0xe7, 0x00 };
	_keycodes["Period"] = { 0x3e, 0xea, 0x00 };
	_keycodes["Slash"] = { 0x41, 0xed, 0x00 };
	_keycodes["Shift_r"] = { 0x44, 0xf0, 0x00 };
	_keycodes["Ctrl_l"] = { 0x57, 0x02, 0x01 };
	_keycodes["Super_l"] = { 0x5a, 0x05, 0x01 };
	_keycodes["Alt_l"] = { 0x5d, 0x08, 0x01 };
	_keycodes["Space"] = { 0x60, 0x0b, 0x01 };
	_keycodes["Alt_r"] = { 0x63, 0x0e, 0x01 };
	_keycodes["Fn"] = { 0x66, 0x11, 0x01 };
	_keycodes["Menu"] = { 0x69, 0x14, 0x01 };
	_keycodes["Ctrl_r"] = { 0x6c, 0x17, 0x01 };
	_keycodes["Num_Lock"] = { 0xb1, 0x5d, 0x00 };
	_keycodes["Num_Slash"] = { 0xb4, 0x60, 0x00 };
	_keycodes["Num_Asterisk"] = { 0xb7, 0x63, 0x00 };
	_keycodes["Num_Minus"] = { 0xb1, 0x5c, 0x01 };
	_keycodes["Num_7"] = { 0xe4, 0x90, 0x00 };
	_keycodes["Num_8"] = { 0xe7, 0x93, 0x00 };
	_keycodes["Num_9"] = { 0xea, 0x96, 0x00 };
	_keycodes["Num_Plus"] = { 0xb4, 0x5f, 0x01 };
	_keycodes["Num_4"] = { 0x17, 0xc3, 0x00 };
	_keycodes["Num_5"] = { 0x1a, 0xc6, 0x00 };
	_keycodes["Num_6"] = { 0x1d, 0xc9, 0x00 };
	_keycodes["Num_1"] = { 0x4a, 0xf6, 0x00 };
	_keycodes["Num_2"] = { 0x4d, 0xf9, 0x00 };
	_keycodes["Num_3"] = { 0x50, 0xfc, 0x00 };
	_keycodes["Num_0"] = { 0x7e, 0x29, 0x01 };
	_keycodes["Num_Period"] = { 0x81, 0x2c, 0x01 };
	_keycodes["Num_Return"] = { 0x84, 0x2f, 0x01 };
	
	//offsets for key remapping
	_keymap_offsets["Esc"] = {{ { 3, 11 }, { 3, 12 }, { 3, 13 } }};
	_keymap_offsets["F1"] = {{ { 3, 14 }, { 3, 15 }, { 3, 16 } }};
	_keymap_offsets["F2"] = {{ { 3, 17 }, { 3, 18 }, { 3, 19 } }};
	_keymap_offsets["F3"] = {{ { 3, 20 }, { 3, 21 }, { 3, 22 } }};
	_keymap_offsets["F4"] = {{ { 3, 23 }, { 3, 24 }, { 3, 25 } }};
	_keymap_offsets["F5"] = {{ { 3, 26 }, { 3, 27 }, { 3, 28 } }};
	_keymap_offsets["F6"] = {{ { 3, 29 }, { 3, 30 }, { 3, 31 } }};
	_keymap_offsets["F7"] = {{ { 3, 32 }, { 3, 33 }, { 3, 34 } }};
	_keymap_offsets["F8"] = {{ { 3, 35 }, { 3, 36 }, { 3, 37 } }};
	_keymap_offsets["F9"] = {{ { 3, 38 }, { 3, 39 }, { 3, 40 } }};
	_keymap_offsets["F10"] = {{ { 3, 41 }, { 3, 42 }, { 3, 43 } }};
	_keymap_offsets["F11"] = {{ { 3, 44 }, { 3, 45 }, { 3, 46 } }};
	_keymap_offsets["F12"] = {{ { 3, 47 }, { 3, 48 }, { 3, 49 } }};
	_keymap_offsets["PrtSc"] = {{ { 8, 46 }, { 8, 47 }, { 8, 48 } }};
	_keymap_offsets["ScrLk"] = {{ { 8, 49 }, { 8, 50 }, { 8, 51 } }};
	_keymap_offsets["Pause"] = {{ { 8, 52 }, { 8, 53 }, { 8, 54 } }};
	_keymap_offsets["Tilde"] = {{ { 3, 62 }, { 3, 63 }, { 4, 8 } }};
	_keymap_offsets["1"] = {{ { 4, 9  }, { 4, 10 }, { 4, 11 } }};
	_keymap_offsets["2"] = {{ { 4, 12 }, { 4, 13 }, { 4, 14 } }};
	_keymap_offsets["3"] = {{ { 4, 15 }, { 4, 16 }, { 4, 17 } }};
	_keymap_offsets["4"] = {{ { 4, 18 }, { 4, 19 }, { 4, 20 } }};
	_keymap_offsets["5"] = {{ { 4, 21 }, { 4, 22 }, { 4, 23 } }};
	_keymap_offsets["6"] = {{ { 4, 24 }, { 4, 25 }, { 4, 26 } }};
	_keymap_offsets["7"] = {{ { 4, 27 }, { 4, 28 }, { 4, 29 } }};
	_keymap_offsets["8"] = {{ { 4, 30 }, { 4, 31 }, { 4, 32 } }};
	_keymap_offsets["9"] = {{ { 4, 33 }, { 4, 34 }, { 4, 35 } }};
	_keymap_offsets["0"] = {{ { 4, 36 }, { 4, 37 }, { 4, 38 } }};
	_keymap_offsets["Minus"] = {{ { 4, 39 }, { 4, 40 }, { 4, 41 } }};
	_keymap_offsets["Equals"] = {{ { 4, 42 }, { 4, 43 }, { 4, 44 } }};
	_keymap_offsets["Backspace"] = {{ { 8, 22 }, { 8, 23 }, { 8, 24 } }};
	_keymap_offsets["Insert"] = {{ { 8, 58 }, { 8, 59 }, { 8, 60 } }};
	_keymap_offsets["Home"] = {{ { 8, 61 }, { 8, 62 }, { 8, 63 } }};
	_keymap_offsets["PgUp"] = {{ { 9, 8 }, { 9, 9 }, { 9, 10 } }};
	_keymap_offsets["Delete"] = {{ { 9, 11 }, { 9, 12 }, { 9, 13 } }};
	_keymap_offsets["End"] = {{ { 9, 14 }, { 9, 15 }, { 9, 16 } }};
	_keymap_offsets["PgDn"] = {{ { 9, 17 }, { 9, 18 }, { 9, 19 } }};
	_keymap_offsets["Tab"] = {{ { 4, 57 }, { 4, 58 }, { 4, 59 } }};
	_keymap_offsets["q"] = {{ { 4, 60 }, { 4, 61 }, { 4, 62 } }};
	_keymap_offsets["w"] = {{ { 5, 7 }, { 5, 8 }, { 5, 9 } }};
	_keymap_offsets["e"] = {{ { 5, 10 }, { 5, 11 }, { 5, 12 } }};
	_keymap_offsets["r"] = {{ { 5, 13 }, { 5, 14 }, { 5, 15 } }};
	_keymap_offsets["t"] = {{ { 5, 16 }, { 5, 17 }, { 5, 18 } }};
	_keymap_offsets["y"] = {{ { 5, 19 }, { 5, 20 }, { 5, 21 } }};
	_keymap_offsets["u"] = {{ { 5, 22 }, { 5, 23 }, { 5, 24 } }};
	_keymap_offsets["i"] = {{ { 5, 25 }, { 5, 26 }, { 5, 27 } }};
	_keymap_offsets["o"] = {{ { 5, 28 }, { 5, 29 }, { 5, 30 } }};
	_keymap_offsets["p"] = {{ { 5, 31 }, { 5, 32 }, { 5, 33 } }};
	_keymap_offsets["Bracket_l"] = {{ { 5, 34 }, { 5, 35 }, { 5, 36 } }};
	_keymap_offsets["Bracket_r"] = {{ { 5, 37 }, { 5, 38 }, { 3, 39 } }};
	_keymap_offsets["Backslash"] = {{ { 6, 32 }, { 6, 33 }, { 6, 34 } }};
	_keymap_offsets["Up"] = {{ { 8, 16 }, { 8, 17 }, { 8, 18 } }};
	_keymap_offsets["Left"] = {{ { 8, 10 }, { 8, 11 }, { 8, 12 } }};
	_keymap_offsets["Down"] = {{ { 8, 13 }, { 8, 14 }, { 8, 15 } }};
	_keymap_offsets["Right"] = {{ { 8, 19 }, { 8, 20 }, { 8, 21 } }};
	_keymap_offsets["Caps_Lock"] = {{ { 5, 52 }, { 5, 53 }, { 5, 54 } }};
	_keymap_offsets["a"] = {{ { 5, 55 }, { 5, 56 }, { 5, 57 } }};
	_keymap_offsets["s"] = {{ { 5, 58 }, { 5, 59 }, { 5, 60 } }};
	_keymap_offsets["d"] = {{ { 5, 61 }, { 5, 62 }, { 5, 63 } }};
	_keymap_offsets["f"] = {{ { 6, 8 }, { 6, 9 }, { 6, 10 } }};
	_keymap_offsets["g"] = {{ { 6, 11 }, { 6, 12 }, { 6, 13 } }};
	_keymap_offsets["h"] = {{ { 6, 14 }, { 6, 15 }, { 6, 16 } }};
	_keymap_offsets["j"] = {{ { 6, 17 }, { 6, 18 }, { 6, 19 } }};
	_keymap_offsets["k"] = {{ { 6, 20 }, { 6, 21 }, { 6, 22 } }};
	_keymap_offsets["l"] = {{ { 6, 23 }, { 6, 24 }, { 6, 25 } }};
	_keymap_offsets["Semicolon"] = {{ { 6, 26 }, { 6, 27 }, { 6, 28 } }};
	_keymap_offsets["Apostrophe"] = {{ { 6, 29 }, { 6, 30 }, { 6, 31 } }};
	_keymap_offsets["Return"] = {{ { 7, 27 }, { 7, 28 }, { 7, 29 } }};
	_keymap_offsets["z"] = {{ { 6, 50 }, { 6, 51 }, { 6, 52 } }};
	_keymap_offsets["x"] = {{ { 6, 53 }, { 6, 54 }, { 6, 55 } }};
	_keymap_offsets["c"] = {{ { 6, 56 }, { 6, 57 }, { 6, 58 } }};
	_keymap_offsets["v"] = {{ { 6, 59 }, { 6, 60 }, { 6, 61 } }};
	_keymap_offsets["b"] = {{ { 6, 62 }, { 6, 63 }, { 7, 8 } }};
	_keymap_offsets["n"] = {{ { 7, 9 }, { 7, 10 }, { 7, 11 } }};
	_keymap_offsets["m"] = {{ { 7, 12 }, { 7, 13 }, { 7, 14 } }};
	_keymap_offsets["Comma"] = {{ { 7, 15 }, { 7, 16 }, { 7, 17 } }};
	_keymap_offsets["Period"] = {{ { 7, 18 }, { 7, 19 }, { 7, 20 } }};
	_keymap_offsets["Slash"] = {{ { 7, 21 }, { 7, 22 }, { 7, 23 } }};
	_keymap_offsets["Shift_l"] = {{ { 6, 47 }, { 6, 48 }, { 6, 49 } }};
	_keymap_offsets["Shift_r"] = {{ { 7, 24 }, { 7, 25 }, { 7, 26 } }};
	_keymap_offsets["Ctrl_l"] = {{ { 7, 42 }, { 7, 43 }, { 7, 44 } }};
	_keymap_offsets["Super_l"] = {{ { 7, 45 }, { 7, 46 }, { 7, 47 } }};
	_keymap_offsets["Alt_l"] = {{ { 7, 48 }, { 7, 49 }, { 7, 50 } }};
	_keymap_offsets["Space"] = {{ { 7, 51 }, { 7, 52 }, { 7, 53 } }};
	_keymap_offsets["Alt_r"] = {{ { 7, 54 }, { 7, 55 }, { 7, 56 } }};
	_keymap_offsets["Fn"] = {{ { 7, 57 }, { 7, 58 }, { 7, 59 } }};
	_keymap_offsets["Menu"] = {{ { 7, 60 }, { 7, 61 }, { 7, 62 } }};
	_keymap_offsets["Ctrl_r"] = {{ { 7, 63 }, { 8, 8 }, { 8, 9 } }};
	_keymap_offsets["Num_Lock"] = {{ { 4, 45 }, { 4, 46 }, { 4, 47 } }};
	_keymap_offsets["Num_Slash"] = {{ { 4, 48 }, { 4, 49 }, { 4, 50 } }};
	_keymap_offsets["Num_Asterisk"] = {{ { 4, 51 }, { 4, 52 }, { 4, 53 } }};
	_keymap_offsets["Num_Minus"] = {{ { 9, 20 }, { 9, 21 }, { 9, 22 } }};
	_keymap_offsets["Num_Plus"] = {{ { 9, 23 }, { 9, 24 }, { 9, 25 } }};
	_keymap_offsets["Num_1"] = {{ { 7, 30 }, { 7, 31 }, { 7, 32 } }};
	_keymap_offsets["Num_2"] = {{ { 7, 33 }, { 7, 34 }, { 7, 35 } }};
	_keymap_offsets["Num_3"] = {{ { 7, 36 }, { 7, 37 }, { 7, 38 } }};
	_keymap_offsets["Num_4"] = {{ { 6, 35 }, { 6, 36 }, { 6, 37 } }};
	_keymap_offsets["Num_5"] = {{ { 6, 38 }, { 6, 39 }, { 6, 40 } }};
	_keymap_offsets["Num_6"] = {{ { 6, 41 }, { 6, 42 }, { 6, 43 } }};
	_keymap_offsets["Num_7"] = {{ { 5, 40 }, { 5, 41 }, { 5, 42 } }};
	_keymap_offsets["Num_8"] = {{ { 5, 43 }, { 5, 44 }, { 5, 45 } }};
	_keymap_offsets["Num_9"] = {{ { 5, 46 }, { 5, 47 }, { 5, 48 } }};
	_keymap_offsets["Num_0"] = {{ { 8, 25 }, { 8, 26 }, { 8, 27 } }};
	_keymap_offsets["Num_Period"] = {{ { 8, 28 }, { 8, 29 }, { 8, 30 } }};
	_keymap_offsets["Num_Return"] = {{ { 8, 31 }, { 8, 32 }, { 8, 33 } }};
	
	//keymap options (what a key can do when pressed)
	_keymap_options["Fn"] = { 0x05, 0x02, 0x02 };
	_keymap_options["Esc"] = { 0x02, 0x02, 0x29 };
	_keymap_options["F1"] = { 0x02, 0x02, 0x3a };
	_keymap_options["F2"] = { 0x02, 0x02, 0x3b };
	_keymap_options["F3"] = { 0x02, 0x02, 0x3c };
	_keymap_options["F4"] = { 0x02, 0x02, 0x3d };
	_keymap_options["F5"] = { 0x02, 0x02, 0x3e };
	_keymap_options["F6"] = { 0x02, 0x02, 0x3f };
	_keymap_options["F7"] = { 0x02, 0x02, 0x40 };
	_keymap_options["F8"] = { 0x02, 0x02, 0x41 };
	_keymap_options["F9"] = { 0x02, 0x02, 0x42 };
	_keymap_options["F10"] = { 0x02, 0x02, 0x43 };
	_keymap_options["F11"] = { 0x02, 0x02, 0x44 };
	_keymap_options["F12"] = { 0x02, 0x02, 0x45 };
	_keymap_options["a"] = { 0x02, 0x02, 0x04 };
	_keymap_options["b"] = { 0x02, 0x02, 0x05 };
	_keymap_options["c"] = { 0x02, 0x02, 0x06 };
	_keymap_options["d"] = { 0x02, 0x02, 0x07 };
	_keymap_options["e"] = { 0x02, 0x02, 0x08 };
	_keymap_options["f"] = { 0x02, 0x02, 0x09 };
	_keymap_options["g"] = { 0x02, 0x02, 0x0a };
	_keymap_options["h"] = { 0x02, 0x02, 0x0b };
	_keymap_options["i"] = { 0x02, 0x02, 0x0c };
	_keymap_options["j"] = { 0x02, 0x02, 0x0d };
	_keymap_options["k"] = { 0x02, 0x02, 0x0e };
	_keymap_options["l"] = { 0x02, 0x02, 0x0f };
	_keymap_options["m"] = { 0x02, 0x02, 0x10 };
	_keymap_options["n"] = { 0x02, 0x02, 0x11 };
	_keymap_options["o"] = { 0x02, 0x02, 0x12 };
	_keymap_options["p"] = { 0x02, 0x02, 0x13 };
	_keymap_options["q"] = { 0x02, 0x02, 0x14 };
	_keymap_options["r"] = { 0x02, 0x02, 0x15 };
	_keymap_options["s"] = { 0x02, 0x02, 0x16 };
	_keymap_options["t"] = { 0x02, 0x02, 0x17 };
	_keymap_options["u"] = { 0x02, 0x02, 0x18 };
	_keymap_options["v"] = { 0x02, 0x02, 0x19 };
	_keymap_options["w"] = { 0x02, 0x02, 0x1a };
	_keymap_options["x"] = { 0x02, 0x02, 0x1b };
	_keymap_options["y"] = { 0x02, 0x02, 0x1c };
	_keymap_options["z"] = { 0x02, 0x02, 0x1d };
	_keymap_options["1"] = { 0x02, 0x02, 0x1e };
	_keymap_options["2"] = { 0x02, 0x02, 0x1f };
	_keymap_options["3"] = { 0x02, 0x02, 0x20 };
	_keymap_options["4"] = { 0x02, 0x02, 0x21 };
	_keymap_options["5"] = { 0x02, 0x02, 0x22 };
	_keymap_options["6"] = { 0x02, 0x02, 0x23 };
	_keymap_options["7"] = { 0x02, 0x02, 0x24 };
	_keymap_options["8"] = { 0x02, 0x02, 0x25 };
	_keymap_options["9"] = { 0x02, 0x02, 0x26 };
	_keymap_options["0"] = { 0x02, 0x02, 0x27 };
	_keymap_options["Comma"] = { 0x02, 0x02, 0x36 };
	_keymap_options["Period"] = { 0x02, 0x02, 0x37 };
	_keymap_options["Slash"] = { 0x02, 0x02, 0x38 };
	_keymap_options["Caps_Lock"] = { 0x02, 0x02, 0x39 };
	_keymap_options["Bracket_l"] = { 0x02, 0x02, 0x2f };
	_keymap_options["Bracket_r"] = { 0x02, 0x02, 0x30 };
	_keymap_options["Tab"] = { 0x02, 0x02, 0x2b };
	_keymap_options["Mediaplayer"] = { 0x03, 0x83, 0x01 };
	_keymap_options["PlayPause"] = { 0x03, 0xcd, 0x00 };
	_keymap_options["Stop"] = { 0x03, 0xb7, 0x00 };
	_keymap_options["Previous"] = { 0x03, 0xb6, 0x00 };
	_keymap_options["Next"] = { 0x03, 0xb5, 0x00 };
	_keymap_options["Volume-"] = { 0x03, 0xea, 0x00 };
	_keymap_options["Volume+"] = { 0x03, 0xe9, 0x00 };
	_keymap_options["Mute"] = { 0x03, 0xe2, 0x00 };
	_keymap_options["BrowserHome"] = { 0x03, 0x23, 0x02 };
	_keymap_options["BrowserRefresh"] = { 0x03, 0x27, 0x02 };
	_keymap_options["BrowserStop"] = { 0x03, 0x26, 0x02 };
	_keymap_options["BrowserBack"] = { 0x03, 0x24, 0x02 };
	_keymap_options["BrowserForward"] = { 0x03, 0x25, 0x02 };
	_keymap_options["BrowserFavorite"] = { 0x03, 0x2a, 0x02 };
	_keymap_options["BrowserSearch"] = { 0x03, 0x21, 0x02 };
	_keymap_options["FileExplorer"] = { 0x03, 0x94, 0x01 };
	_keymap_options["Calculator"] = { 0x03, 0x92, 0x01 };
	_keymap_options["Email"] = { 0x03, 0x8a, 0x01 };
	_keymap_options["Lang1"] = { 0x02, 0x02, 0x90 };
	_keymap_options["Lang2"] = { 0x02, 0x02, 0x91 };
	_keymap_options["Lang3"] = { 0x02, 0x02, 0x92 };
	_keymap_options["Lang4"] = { 0x02, 0x02, 0x93 };
	_keymap_options["Lang5"] = { 0x02, 0x02, 0x94 };
	_keymap_options["Lang6"] = { 0x02, 0x02, 0x95 };
	_keymap_options["Lang7"] = { 0x02, 0x02, 0x96 };
	_keymap_options["Lang8"] = { 0x02, 0x02, 0x97 };
	_keymap_options["Lang9"] = { 0x02, 0x02, 0x98 };
}
