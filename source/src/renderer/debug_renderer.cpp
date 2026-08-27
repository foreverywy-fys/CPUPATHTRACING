#include "renderer/debug_render.hpp"
#include "until/rgb.hpp"

glm::vec3 BoundsTestCountRenderer::renderPixel(const glm::ivec3 &pixel_coord)
{
    #ifdef WITH_DEBUG_INFO
    auto ray = camera.generateRay({ pixel_coord.x, pixel_coord.y });
    auto hit_info = scene.intersect(ray);
    if (hit_info.has_value())
    {
        return RGB::GenerateHeatmapRGB(ray.bounds_test_count / 200.f);
    }
    return {};
    #else
    return {};
    #endif
}

glm::vec3 TriangleTestCountRenderer::renderPixel(const glm::ivec3 &pixel_coord)
{
    #ifdef WITH_DEBUG_INFO
    auto ray = camera.generateRay({ pixel_coord.x, pixel_coord.y });
    auto hit_info = scene.intersect(ray);
    if (hit_info.has_value())
    {
        return RGB::GenerateHeatmapRGB(ray.triangle_test_count / 20.f);
    }
    return {};
    #else
    return {};
    #endif
    
}
