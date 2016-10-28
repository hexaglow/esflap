// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef SMILE_XBM_HPP
#define SMILE_XBM_HPP

#include "_safe_arduino.hpp"

constexpr int16_t smile_width = 10;
constexpr int16_t smile_height = 10;
const char smile_bits[] PROGMEM = {
    0x78, 0x00, 0xfe, 0x01, 0xfe, 0x01, 0x33, 0x03, 0x33, 0x03, 0xff, 0x03,
    0xb7, 0x03, 0xce, 0x01, 0xfe, 0x01, 0x78, 0x00 };

#endif
