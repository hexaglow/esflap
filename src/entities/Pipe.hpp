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
