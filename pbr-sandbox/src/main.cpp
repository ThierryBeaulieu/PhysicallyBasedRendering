#include "core/image.h"
#include "renderers/simple_renderer.h"
#include <iostream>

int main()
{
    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 450;

    Image img(WIDTH, HEIGHT);

    std::cout << "[PBR Sandbox] Rendering " << WIDTH << "x" << HEIGHT << "...\n";
    renderBasic(img);

    const std::string path = "../../output/render.ppm"; // relative to build/bin/
    img.writePPM(path);
    std::cout << "[PBR Sandbox] Saved -> " << path << "\n";

    return 0;
}