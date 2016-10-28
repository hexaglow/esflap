// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef VEC2I_HPP
#define VEC2I_HPP

struct Vec2i {
    int x;
    int y;

    Vec2i(int x, int y);

    unsigned int get_length_squared() const;

    Vec2i operator+(const Vec2i& other) const;
    Vec2i& operator+=(const Vec2i& other);

    Vec2i operator-(const Vec2i& other) const;
    Vec2i& operator-=(const Vec2i& other);

    Vec2i operator*(int scalar) const;
    Vec2i& operator*=(int scalar);

    Vec2i operator/(int scalar) const;
    Vec2i& operator/=(int scalar);

    bool operator==(const Vec2i& other) const;
    inline bool operator!=(const Vec2i& other) const {
        return !(*this == other);
    }

    static const Vec2i zero;
};

#endif
