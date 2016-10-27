#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Rect.hpp"
#include "Vec2i.hpp"
// Forward declarations.
class World;
class OLEDDisplay;
class OLEDDisplayUiState;

class Entity {
    friend class World;

public:
    Rect rectangle;
    Vec2i velocity;

    void mark_for_destroy();
    inline bool is_waiting_for_destroy() const {
        return _destroy_now;
    }

    inline unsigned int get_id() const {
        return _id;
    }

    Rect get_pixel_rect() const;

    Entity();
    explicit Entity(Rect r);

    virtual void update(const World& owner);
    virtual void render(OLEDDisplay& display, OLEDDisplayUiState& ui_state, Vec2i offset) const = 0;

    virtual ~Entity() = default;

    static const int units_per_pixel;

protected:
    virtual void on_collision(Entity& other) = 0;

private:
    bool _destroy_now;
    unsigned int _id;
};

#endif /* end of include guard: ENTITY_HPP */
