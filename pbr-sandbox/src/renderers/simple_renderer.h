#pragma once
#include "core/ray.h"
#include "core/image.h"
#include "math/math_utils.h"

// ── Sky gradient background ──
inline Color skyColor(const Ray &r)
{
    Vec3 unit = normalize(r.direction);
    double t = 0.5 * (unit.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

// ── Minimal sphere hit test ──
inline double hitSphere(const Point3 &center, double radius, const Ray &ray)
{
    Vec3 oc = ray.origin - center;
    double a = dot(ray.direction, ray.direction);
    double halfB = dot(oc, ray.direction);
    double c = dot(oc, oc) - radius * radius;
    double disc = halfB * halfB - a * c;
    if (disc < 0.0)
        return -1.0;
    return (-halfB - std::sqrt(disc)) / a;
}

inline Color rayColor(const Ray &r)
{
    double t = hitSphere(Point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        Vec3 normal = normalize(r.at(t) - Vec3(0, 0, -1));
        return 0.5 * Color(normal.x + 1, normal.y + 1, normal.z + 1);
    }
    return skyColor(r);
}

inline void renderBasic(Image &img)
{
    const double aspectRatio = static_cast<double>(img.width) / img.height;

    // Camera
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;

    Point3 origin(0, 0, 0);
    Vec3 horizontal(viewportWidth, 0, 0);
    Vec3 vertical(0, viewportHeight, 0);
    Point3 lowerLeft = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

    for (int j = img.height - 1; j >= 0; --j)
    {
        for (int i = 0; i < img.width; ++i)
        {
            double u = double(i) / (img.width - 1);
            double v = double(j) / (img.height - 1);
            Ray r(origin, lowerLeft + u * horizontal + v * vertical - origin);
            img.set(i, img.height - 1 - j, rayColor(r));
        }
    }
}