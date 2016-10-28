// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include <cinttypes>
#include "entities/Entity.hpp"

class World {
public:
    typedef std::vector<std::unique_ptr<Entity>>::iterator iterator;

    World();
    explicit World(size_t reserved_slots);

    iterator begin();
    iterator end();

    void add(std::unique_ptr<Entity> entity);
    bool remove(const Entity& entity);
    bool contains(const Entity& entity) const;

    void update();

private:
    std::vector<std::unique_ptr<Entity>> _entities;

    static void _handle_possible_collision(Entity& a, Entity& b);
};

#endif /* end of include guard: WORLD_HPP */
