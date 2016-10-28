// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Bird.hpp"
#include "images/smile.xbm.hpp"
#include "pins.hpp"
#include "_safe_arduino.hpp"
#include <OLEDDisplay.h>

const unsigned int Bird::min_time_between_jumps = 10;
const int Bird::jump_velocity = -180;

Bird::Bird(Vec2i top_left)
  : Entity({Vec2i::zero, smile_width * Entity::units_per_pixel, smile_height * Entity::units_per_pixel}),
    _frames_since_last_jump{min_time_between_jumps}
{}

void Bird::update(const World& owner) {
    velocity.y += 5;

    _frames_since_last_jump++;
    if (!digitalRead(flash_button_pin)) {
        if (_frames_since_last_jump >= min_time_between_jumps) {
            velocity.y = jump_velocity;
        }
        _frames_since_last_jump = 0;
    }

    if (rectangle.bottom < Entity::units_per_pixel * -20 || rectangle.top > Entity::units_per_pixel * 72) {
        mark_for_destroy();
    }

    Entity::update(owner);
}

void Bird::render(OLEDDisplay& display, OLEDDisplayUiState& state, Vec2i offset) const {
    int16_t x = get_pixel_rect().left + offset.x;
    int16_t y = get_pixel_rect().top + offset.y;
    display.drawXbm(x, y, smile_width, smile_height, smile_bits);
}

void Bird::on_collision(Entity& other) {
    mark_for_destroy();
}
