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

// Set point3d as an alias for vector3d, this helps with clarity on some geometric procedures
using point3d = vector3d;

#endif