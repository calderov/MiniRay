#ifndef VECTOR3D_H
#define VECTOR3D_H

#include<cmath>
#include<iostream>

class vector3d {
  public:
    double e[3]; // TODO: Make private

    // Constructors
    vector3d() : e{0, 0, 0} {}
    vector3d(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Getters
    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // Invert vector's sense
    vector3d operator-() const { return vector3d(-e[0], -e[1], -e[2]); }
    
    // Element getters
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; } // shoild this be a const function?

    // Vector addition
    vector3d& operator+=(const vector3d &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // Vector scalar multiplication
    vector3d& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // Vector scalar division
    vector3d& operator/=(double t) {
        return *this *= 1/t;
    }

    // Vector length
    double length() const {
        return std::sqrt(length_squared());
    }

    // Vector length squared
    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    // Check if the vector is close to zero in all dimensions
    bool near_zero() const {
        auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    // Random vector
    static vector3d random() {
        return vector3d(random_double(), random_double(), random_double());
    }

    // Restricted random vector
    static vector3d random(double min, double max) {
        return vector3d(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

// Utility functions

// Vector to string
inline std::ostream& operator<<(std::ostream &out, const vector3d &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Vector addition
inline vector3d operator+(const vector3d &u, const vector3d &v) {
    return vector3d(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector substraction
inline vector3d operator-(const vector3d &u, const vector3d &v) {
    return vector3d(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Vector multiplication
inline vector3d operator*(const vector3d &u, const vector3d &v) {
    return vector3d(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Vector scalar multiplication
inline vector3d operator*(double t, const vector3d &v) {
    return vector3d(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vector3d operator*(const vector3d &v, double t) {
    return t * v;
}

// Vector scalar division
inline vector3d operator/(vector3d v, double t) {
    return (1 / t) * v;
}

// Vector dot product
inline double dot(const vector3d &u, const vector3d &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Vector cross product
inline vector3d cross(const vector3d &u, const vector3d &v) {
    return vector3d(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

// Unit vector
inline vector3d unit_vector(vector3d v) {
    return v / v.length();
}

// Random vector in unit sphere
inline vector3d random_in_unit_sphere() {
    while (true)
    {
        vector3d p = vector3d::random(-1, 1);
        if (p.length_squared() < 1) {
            return p;
        }
    }
    
}

// Random unit vector
inline vector3d random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// Random vector on hemisphere
inline vector3d random_on_hemisphere(const vector3d& normal) {
    vector3d on_unit_sphere = random_unit_vector();
    
    // If the vector is in the same hemisphere as the normal
    // return it as is. 
    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    }

    // Otherwise return it with inverted orientation
    return -on_unit_sphere;
}

vector3d reflect(const vector3d& v, const vector3d& n) {
    return v - 2 * dot(v, n) * n;
}

// Set point3d as an alias for vector3d, this helps with clarity on some geometric procedures
using point3d = vector3d;

#endif