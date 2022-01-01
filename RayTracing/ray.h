#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    point3 orig;
    vec3 dir;

public:

    // Constructor
    ray() {}

    // Overlaoded constructor
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    // Get origin and directon
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    // Return ray 
    //(P(t) = A + tb where A is start point,
    //b is direction, t is magnitude)
    point3 at(double t) const {
        return orig + t * dir;
    }

};

#endif