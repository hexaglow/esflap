#include "Entity.hpp"

const int Entity::units_per_pixel = 100;

static unsigned int _get_entity_id() {
    static unsigned int id = 0;
    return id++;
}

Entity::Entity(Rect r) : rectangle{r.as_normalised()},
    velocity{Vec2i::zero}, _destroy_now{false}, _id{_get_entity_id()}
{}

Entity::Entity() : Entity({{Vec2i::zero}, {Vec2i::zero}})
{}

void Entity::update(const World& owner) {
    rectangle.normalise();

    rectangle.left += velocity.x;
    rectangle.right += velocity.x;
    rectangle.top += velocity.y;
    rectangle.bottom += velocity.y;
}

void Entity::mark_for_destroy() {
    _destroy_now = true;
}

Rect Entity::get_pixel_rect() const {
    return {
        Vec2i{rectangle.left, rectangle.top} / units_per_pixel,
        Vec2i{rectangle.right, rectangle.bottom} / units_per_pixel
    };
}
