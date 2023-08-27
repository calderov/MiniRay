#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class ray {
  private:
    point3d orig;
    vector3d dir;

  public:
    // Constructors
    ray() {}    
    ray(const point3d& origin, const vector3d& direction) : orig(origin), dir(direction) {}

    // Getters
    point3d origin() const { return orig; }
    point3d direction() const { return dir;}

    // Point at
    point3d at(double t) const { return orig + t * dir; } 
};

#endif