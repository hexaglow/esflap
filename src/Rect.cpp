// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include "Rect.hpp"
#include <algorithm>

Rect::Rect(Vec2i top_left, Vec2i bottom_right)
  : left{top_left.x}, top{top_left.y},
    right{bottom_right.x}, bottom{bottom_right.y}
{
    normalise();
}

Rect::Rect(Vec2i top_left, int width, int height)
  : Rect(top_left, {top_left.x + width, top_left.y + height})
{}

unsigned int Rect::get_area() const {
    int area = (bottom - top) * (right - left);
    return area < 0 ? -area : area;
}

void Rect::normalise() {
    if (top > bottom) {
        std::swap(top, bottom);
    }
    if (left > right) {
        std::swap(left, right);
    }
}

Rect Rect::as_normalised() const {
    Rect self = *this;
    self.normalise();
    return self;
}

bool Rect::intersects_with(const Rect& other_) const {
    Rect other = other_.as_normalised();
    Rect self = as_normalised();
    return self.left <= other.right && self.right >= other.left
        && self.top <= other.bottom && self.bottom >= other.top;
}

Rect& Rect::operator&=(const Rect& other_) {
    Rect other = other_.as_normalised();
    Rect self = as_normalised();
    if (self.intersects_with(other)) {
        top = std::max(self.top, other.top);
        bottom = std::min(self.bottom, other.bottom);
        left = std::max(self.left, other.left);
        right = std::min(self.right, other.right);
    } else {
        top = bottom = left = right = 0;
    }

    return *this;
}

Rect Rect::operator&(const Rect& other) const {
    Rect result = *this;
    result &= other;
    return result;
}

bool Rect::operator==(const Rect& other_) const {
    Rect self = as_normalised();
    Rect other = other_.as_normalised();
    return self.top == other.top && self.bottom == other.bottom
        && self.left == other.left && self.right == other.right;
}
