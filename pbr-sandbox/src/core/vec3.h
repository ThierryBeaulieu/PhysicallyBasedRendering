#pragma once
#include <cmath>
#include <iostream>

struct Vec3 {
    double x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    Vec3 operator*(double t)       const { return {x*t,   y*t,   z*t};   }
    Vec3 operator*(const Vec3& v)  const { return {x*v.x, y*v.y, z*v.z}; }
    Vec3 operator/(double t)       const { return *this * (1.0/t); }
    Vec3 operator-()               const { return {-x, -y, -z}; }

    Vec3& operator+=(const Vec3& v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    Vec3& operator*=(double t)      { x*=t;   y*=t;   z*=t;   return *this; }

    double lengthSquared() const { return x*x + y*y + z*z; }
    double length()        const { return std::sqrt(lengthSquared()); }
    bool   nearZero()      const {
        constexpr double s = 1e-8;
        return std::fabs(x) < s && std::fabs(y) < s && std::fabs(z) < s;
    }

    // Aliases
    double r() const { return x; }
    double g() const { return y; }
    double b() const { return z; }
};

// Free functions
inline Vec3 operator*(double t, const Vec3& v) { return v * t; }

inline double dot(const Vec3& a, const Vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return { a.y*b.z - a.z*b.y,
             a.z*b.x - a.x*b.z,
             a.x*b.y - a.y*b.x };
}
inline Vec3 normalize(const Vec3& v) { return v / v.length(); }
inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2.0 * dot(v, n) * n;
}
inline Vec3 refract(const Vec3& uv, const Vec3& n, double etaiOverEtat) {
    double cosTheta = std::fmin(dot(-uv, n), 1.0);
    Vec3 rOutPerp  = etaiOverEtat * (uv + cosTheta * n);
    Vec3 rOutParal = -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;
    return rOutPerp + rOutParal;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    return os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
}

using Point3 = Vec3;
using Color  = Vec3;