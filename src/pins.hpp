// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef PINS_HPP
#define PINS_HPP

#include "_safe_arduino.hpp"

// Low when pressed (PTC in a pulldown configuration)
constexpr uint8_t flash_button_pin = D3;
// Low for on
constexpr uint8_t builtin_tx_led = D4;

constexpr uint8_t spi_oled_cs = D1;
constexpr uint8_t spi_oled_dc = D2;

constexpr uint8_t softserial_tx = D0;
constexpr uint8_t softserial_rx = D6;

#endif /* end of include guard: PINS_HPP */
