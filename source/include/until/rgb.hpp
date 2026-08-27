#pragma once

#include <array>
#include <cstddef>
#include <glm/glm.hpp>

class RGB Lerp(const RGB &a, const RGB &b, float t);

class RGB
{
public: 
    RGB(int r, int g, int b) : r(r), g(g), b(b) {}

    inline static RGB GenerateHeatmapRGB(float t)
    {
        static const std::array<RGB, 25> color_pallet =
        {
            {
                RGB { 0x44, 0x01, 0x54 }, RGB { 0x47, 0x11, 0x64 }, RGB { 0x48, 0x1F, 0x70 }, RGB { 0x47, 0x2D, 0x7B }, RGB { 0x44, 0x3A, 0x83 },
                RGB { 0x40, 0x46, 0x88 }, RGB { 0x3B, 0x52, 0x8B }, RGB { 0x36, 0x5D, 0x8D }, RGB { 0x31, 0x68, 0x8E }, RGB { 0x2C, 0x72, 0x8E },
                RGB { 0x28, 0x7C, 0x8E }, RGB { 0x24, 0x86, 0x8E }, RGB { 0x21, 0x90, 0x8C }, RGB { 0x1F, 0x9A, 0x8A }, RGB { 0x20, 0xA4, 0x86 },
                RGB { 0x27, 0xAD, 0x81 }, RGB { 0x35, 0xB7, 0x79 }, RGB { 0x47, 0xC1, 0x6E }, RGB { 0x5D, 0xC8, 0x63 }, RGB { 0x75, 0xD0, 0x54 },
                RGB { 0x8F, 0xD7, 0x44 }, RGB { 0xAA, 0xDC, 0x32 }, RGB { 0xC7, 0xE0, 0x20 }, RGB { 0xE3, 0xE4, 0x18 }, RGB { 0xFD, 0xE7, 0x25 }
            }
        };
        if (t <= 0.0F)
        {
            return color_pallet.front();
        }
        if (t >= 1.0F)
        {
            return color_pallet.back();
        }
        const float idx_float = t * static_cast<float>(color_pallet.size() - 1);
        const size_t idx = static_cast<size_t>(glm::floor(idx_float));
        return Lerp(color_pallet[idx], color_pallet[idx + 1], glm::fract(idx_float));
    }

    RGB(const glm::vec3 &color) 
    {
        constexpr float gamma = 1.0F / 2.2F;
        r = static_cast<int>(glm::clamp(glm::pow(color.x, gamma) * 255.0F, 0.0F, 255.0F));
        g = static_cast<int>(glm::clamp(glm::pow(color.y, gamma) * 255.0F, 0.0F, 255.0F));
        b = static_cast<int>(glm::clamp(glm::pow(color.z, gamma) * 255.0F, 0.0F, 255.0F));        
    }

    operator glm::vec3() const
    {
        return glm::vec3 
        {
            glm::pow(r / 255.0F, 2.2F),
            glm::pow(g / 255.0F, 2.2F),
            glm::pow(b / 255.0F, 2.2F)
        };
    }

    int r, g, b;
private:
};

inline RGB Lerp(const RGB &a, const RGB &b, float t)
{
    return RGB 
    {
        static_cast<int>(glm::clamp(static_cast<float>(a.r) + static_cast<float>(b.r - a.r) * t, 0.0F, 255.0F)),
        static_cast<int>(glm::clamp(static_cast<float>(a.g) + static_cast<float>(b.g - a.g) * t, 0.0F, 255.0F)),
        static_cast<int>(glm::clamp(static_cast<float>(a.b) + static_cast<float>(b.b - a.b) * t, 0.0F, 255.0F))
    };
}
