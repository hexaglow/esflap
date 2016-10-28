// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef PIPE_HPP
#define PIPE_HPP
#include "Entity.hpp"

class Pipe : public Entity {
public:
    Pipe(Vec2i top_left);

    void update(const World& owner) override;
    void render(OLEDDisplay& display, OLEDDisplayUiState& state, Vec2i offset) const override;

    void on_collision(Entity& other) override;

private:
    void reset_size();
};

#endif
