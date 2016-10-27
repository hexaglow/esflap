#include "World.hpp"

#include <iterator>
#include <algorithm>

World::World(size_t initial_capacity) : _entities(initial_capacity)
{}

World::World() : _entities()
{}

World::iterator World::begin() {
    using std::begin;
    return begin(_entities);
}

World::iterator World::end() {
    using std::end;
    return end(_entities);
}

void World::add(std::unique_ptr<Entity> entity) {
    _entities.push_back(std::move(entity));
}

bool World::remove(const Entity& entity) {
    using std::begin;
    using std::end;

    auto new_end = std::remove_if(begin(_entities), end(_entities),
        [&entity](const std::unique_ptr<Entity>& ptr) {
            return ptr.get() == &entity;
        }
    );
    auto num_removed = std::distance(new_end, end(_entities));
    _entities.erase(new_end, end(_entities));

    return num_removed != 0;
}

void World::_handle_possible_collision(Entity &a, Entity &b) {
    if (&a == &b) return;

    if (a.rectangle.intersects_with(b.rectangle)) {
        a.on_collision(b);
    }
}

void World::update() {
    for (auto& entity_ptr : *this) {
        entity_ptr->update(*this);
    }

    using std::begin; using std::end;
    _entities.erase(std::remove_if(begin(_entities), end(_entities),
        [](const std::unique_ptr<Entity>& ent) { return ent->is_waiting_for_destroy(); }
    ), end(_entities));

    for (auto& a_ptr : *this) {
        for (auto& b_ptr : *this) {
            _handle_possible_collision(*a_ptr, *b_ptr);
        }
    }
}
