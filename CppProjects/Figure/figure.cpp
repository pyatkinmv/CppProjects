#include "figure.h"
#include <stdio.h>
#include <math.h>

bool Triangle::contains(const Point& p) const {
    double l = (a.x - p.x) * (b.y - a.y) - (b.x - a.x) * (a.y - p.y);
    double m = (b.x - p.x) * (c.y - b.y) - (c.x - b.x) * (b.y - p.y);
    double n = (c.x - p.x) * (a.y - c.y) - (a.x - c.x) * (c.y - p.y);
    return ((l >= 0. && m >= 0. && n >= 0.) || (l <= 0. && m <= 0. && n <= 0.));
}

bool Rectangle::contains(const Point& p2) const {
        return (
        p.x <= p2.x && p2.x < p.x + width &&
        p.y <= p2.y && p2.y < p.y + height
        );
    }

bool Circle::contains(const Point& p2) const {
        return centre.distance(p2) <= radius;
    }
