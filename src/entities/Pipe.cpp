#include "Pipe.hpp"
#include <OLEDDisplay.h>
#include "images/pipe.xbm.hpp"
#include "images/pipe_end.xbm.hpp"

Pipe::Pipe(Vec2i top_left)
  : Entity({top_left, Entity::units_per_pixel * pipe_width, 64 * Entity::units_per_pixel})
{
    velocity.x = -150;
    reset_size();
}

void Pipe::update(const World& owner) {
    Entity::update(owner);

    // is offscreen
    if (rectangle.right < 0) {
        rectangle.right += 128 * Entity::units_per_pixel;
        rectangle.left += 128 * Entity::units_per_pixel;
        reset_size();
    }
}

void Pipe::render(OLEDDisplay& display, OLEDDisplayUiState& state, Vec2i offset) const {
    Rect draw_rect = get_pixel_rect();
    draw_rect.left += offset.x;
    draw_rect.right += offset.x;
    draw_rect.top += offset.y;
    draw_rect.bottom += offset.y;
    draw_rect.normalise();

    display.setColor(WHITE);
    display.drawXbm(draw_rect.left, draw_rect.top,
        pipe_end_width, pipe_end_height, pipe_end_bits);
    for (int y = draw_rect.top + pipe_end_height; y + pipe_height <= draw_rect.bottom; y++) {
        display.drawXbm(draw_rect.left, y, pipe_width, pipe_height, pipe_bits);
    }
}

void Pipe::on_collision(Entity &other) {}

void Pipe::reset_size() {
    rectangle.top = random(Entity::units_per_pixel * 22, Entity::units_per_pixel * 56);
}
