#pragma once
#include <cmath>
#include <random>
#include "core/vec3.h"

constexpr double PI = 3.14159265358979323846;

inline double degToRad(double deg) { return deg * PI / 180.0; }
inline double radToDeg(double rad) { return rad * 180.0 / PI; }

// ── RNG ──
inline double randomDouble(double min = 0.0, double max = 1.0) {
    static std::mt19937_64 rng(std::random_device{}());
    return std::uniform_real_distribution<double>(min, max)(rng);
}

// ── Sampling helpers ──
inline Vec3 randomInUnitSphere() {
    while (true) {
        Vec3 p(randomDouble(-1,1), randomDouble(-1,1), randomDouble(-1,1));
        if (p.lengthSquared() < 1.0) return p;
    }
}
inline Vec3 randomUnitVector()       { return normalize(randomInUnitSphere()); }
inline Vec3 randomOnHemisphere(const Vec3& normal) {
    Vec3 v = randomUnitVector();
    return dot(v, normal) > 0.0 ? v : -v;
}
inline Vec3 randomInUnitDisk() {
    while (true) {
        Vec3 p(randomDouble(-1,1), randomDouble(-1,1), 0);
        if (p.lengthSquared() < 1.0) return p;
    }
}

// ── Schlick approximation for Fresnel ──
inline double schlick(double cosine, double ior) {
    double r0 = (1.0 - ior) / (1.0 + ior);
    r0 *= r0;
    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0);
}