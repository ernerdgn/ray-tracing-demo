#pragma once
#include "vec3.h"
#include "Material.h"

struct Sphere
{
    vec3 center;
    float radius;
    Material material;
};

constexpr Sphere spheres[] = 
{
    {{-3, 0, -16}, 2, ivory},
    {{-1.0, -1.5, -12}, 2, glass},
    {{1.5, -0.5, -18}, 3, red_rubber},
    {{7, 5, -18}, 4, mirror}
};