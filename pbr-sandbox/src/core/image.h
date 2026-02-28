#pragma once
#include "vec3.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

class Image {
public:
    int width, height;
    std::vector<Color> pixels;

    Image(int w, int h) : width(w), height(h), pixels(w * h, Color(0,0,0)) {}

    void set(int x, int y, const Color& c) {
        pixels[y * width + x] = c;
    }
    Color get(int x, int y) const {
        return pixels[y * width + x];
    }

    // Write a .ppm file (simplest format, no dependencies needed)
    void writePPM(const std::string& path) const {
        std::ofstream f(path);
        if (!f) throw std::runtime_error("Cannot open: " + path);
        f << "P3\n" << width << " " << height << "\n255\n";
        for (const auto& c : pixels) {
            // Gamma-correct (gamma 2) and clamp
            auto toInt = [](double v) {
                v = std::sqrt(std::clamp(v, 0.0, 1.0)); // gamma 2
                return static_cast<int>(255.999 * v);
            };
            f << toInt(c.r()) << " " << toInt(c.g()) << " " << toInt(c.b()) << "\n";
        }
    }
};