// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BIRD_HPP
#define BIRD_HPP

#include "Entity.hpp"
#include "Vec2i.hpp"

class Bird : public Entity {
public:
    Bird(Vec2i top_left);

    void update(const World& owner) override;
    void render(OLEDDisplay& display, OLEDDisplayUiState& state, Vec2i offset) const override;

protected:
    void on_collision(Entity& other) override;

    static const unsigned int min_time_between_jumps;
    static const int jump_velocity;

private:
    unsigned int _frames_since_last_jump;
};

#endif /* end of include guard: BIRD_HPP */
