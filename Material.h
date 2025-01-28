#pragma once
#include "vec3.h"

struct Material
{
    float refractive_index = 1;
    float albedo[4] = {2,0,0,0};
    vec3 diffuse_color = {0,0,0};
    float specular_exponent = 0;
};

constexpr Material ivory = {1.0, {0.9, 0.5, 0.1, 0.0}, {0.4, 0.4, 0.3}, 50.};
constexpr Material glass = {1.5, {0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8}, 125.};
constexpr Material red_rubber = {1.0, {1.4, 0.3, 0.0, 0.0}, {0.3, 0.1, 0.1}, 10.};
constexpr Material mirror = {1.0, {0.0, 16.0, 0.8, 0.0}, {1.0, 1.0, 1.0}, 1425.};