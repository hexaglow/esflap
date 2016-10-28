// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include "Vec2i.hpp"

const Vec2i Vec2i::zero = {0, 0};

Vec2i::Vec2i(int p_x, int p_y) : x{p_x}, y{p_y}
{}

unsigned int Vec2i::get_length_squared() const {
    return (x*x) + (y*y);
}

Vec2i& Vec2i::operator+=(const Vec2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2i Vec2i::operator+(const Vec2i& other) const {
    Vec2i self = *this;
    self += other;
    return self;
}

Vec2i& Vec2i::operator-=(const Vec2i& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2i Vec2i::operator-(const Vec2i& other) const {
    Vec2i self = *this;
    self -= other;
    return self;
}

Vec2i& Vec2i::operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2i Vec2i::operator*(int scalar) const {
    Vec2i self = *this;
    self *= scalar;
    return self;
}

Vec2i& Vec2i::operator/=(int scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vec2i Vec2i::operator/(int scalar) const {
    Vec2i self = *this;
    self /= scalar;
    return self;
}

bool Vec2i::operator==(const Vec2i& other) const {
    return (x == other.x) && (y == other.y);
}
