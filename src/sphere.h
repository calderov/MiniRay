#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

class sphere : public hittable {
  private:
    point3d center;
    double radius;
    shared_ptr<material> mat;

  public:
    sphere(point3d _center, double _radius, shared_ptr<material> _material) : center(_center), radius(_radius), mat(_material) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vector3d oc = r.origin() - center;
        double a = r.direction().length_squared();
        double half_b = dot(oc, r.direction());
        double c = oc.length_squared() - radius*radius;

        double discriminant = half_b * half_b - a * c;

        if (discriminant < 0) {
            return false;
        }

        // Find the nearest root that lies in the acceptable range.
        double sqrtd = sqrt(discriminant);
        double root = (-half_b - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (-half_b + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(root);
        vector3d outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        // Set the spehere material
        rec.mat = mat;

        return true;
    }
};
#endif