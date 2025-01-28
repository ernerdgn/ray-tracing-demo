#pragma once
#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

struct vec3
{
    float x=0, y=0, z=0;
    float& operator[](const int i)
    {
        return i==0 ? x : (1==i ? y : z);
    }
    const float& operator[](const int i) const 
    {
        return i==0 ? x : (1==i ? y : z);
    }
    vec3  operator*(const float v) const
    {
        return {x*v, y*v, z*v};
    }
    float operator*(const vec3& v) const
    {
        return x*v.x + y*v.y + z*v.z;
    }
    vec3  operator+(const vec3& v) const
    {
        return {x+v.x, y+v.y, z+v.z};
    }
    vec3  operator-(const vec3& v) const
    {
        return {x-v.x, y-v.y, z-v.z};
    }
    vec3  operator-() const
    {
        return {-x, -y, -z};
    }
    float norm() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    vec3 normalized() const 
    {
        return (*this)*(1.f/norm());
    }
};

vec3 cross(const vec3 v1, const vec3 v2)
{
    return { v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x };
}

constexpr vec3 lights[] =
{
    {-20, 20,  20},
    { 30, 50, -25},
    { 30, 20,  30}
};

vec3 reflect(const vec3 &I, const vec3 &N)
{
    return I - N*2.f*(I*N);
}

vec3 refract(const vec3 &I, const vec3 &N, const float eta_t, const float eta_i=1.f)
{
    float cosi = -std::max(-1.f, std::min(1.f, I*N));
    if (cosi < 0) return refract(I, -N, eta_i, eta_t);
    float eta = eta_i / eta_t;
    float k = 1 - eta*eta*(1 - cosi*cosi);
    return k < 0 ? vec3{1,0,0} : I*eta + N*(eta*cosi - std::sqrt(k));
}