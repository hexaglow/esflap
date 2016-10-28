// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2i.hpp"

struct Rect {
    int top;
    int bottom;
    int left;
    int right;

    Rect(Vec2i top_left, Vec2i bottom_right);
    Rect(Vec2i top_left, int width, int height);

    void normalise();
    Rect as_normalised() const;

    unsigned int get_area() const;

    bool intersects_with(const Rect& other) const;

    // operator& and instersection_with do the same thing.
    Rect operator&(const Rect& other) const;
    Rect& operator&=(const Rect& other);
    inline Rect instersection_with(const Rect& other) const {
        return *this & other;
    }

    bool operator==(const Rect& other) const;
    inline bool operator!=(const Rect& other) const {
        return !(*this == other);
    }
};

#endif /* end of include guard: RECT_HPP */
