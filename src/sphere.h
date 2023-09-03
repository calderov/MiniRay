#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vector3d.h"

class sphere: public hittable {
  private:
    point3d center;
    double radius;

  public:
    sphere(point3d _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        vector3d oc = r.origin() - center;
        
        double a = r.direction().length_squared();
        double half_b = dot(r.direction(), oc);
        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;

        if (discriminant < 0) {
            return false;
        }

        // Compute the two possible roots
        double sqrt_discriminant =  sqrt(discriminant);
        double root1 = (-half_b - sqrt_discriminant) / a;
        double root2 = (-half_b + sqrt_discriminant) / a;
        
        // Return false if none of the roots are in the acceptable range
        if ((root1 <= ray_tmin || root1 >= ray_tmax) && (root2 <= ray_tmin || root2 >= ray_tmax)) {
            return false;
        }

        // Pick the nearest root
        double root = root1 < root2 ? root1 : root2;
        
        rec.t = root;
        rec.p = r.at(root);
        rec.normal = (rec.p - center) / radius;

        return true;
    };
};
#endif