# ray-tracing-demo
This repo is for understanding the concept of ray tracing.

**What is Ray Tracing?**
*Ray tracing is a rendering technique used to simulate the way light interacts with objects in a virtual environment. It traces the path of rays of light as they travel through a scene, calculating the color and brightness of pixels in an image based on the light's interactions with surfaces. This technique is known for producing highly realistic images, as it accounts for various optical effects such as reflection, refraction, and shadows.*

*This project implements a simple ray tracing application that generates a 3D scene with spheres and a checkerboard plane. The core functionality includes ray-sphere intersection calculations, shading based on material properties, and rendering the scene to a framebuffer. The application utilizes a multi-threaded approach to efficiently compute pixel colors, resulting in a high-quality image output in the PPM format.*

## HEADER FILES
### material.h
*This header defines the Material structure, which encapsulates the properties of materials used in the scene.*

**float refractive_index**: *Represents the material's refractive index, affecting how light bends when entering the material.*

**float albedo**: *An array representing the material's reflectivity and absorption properties across different channels (diffuse, specular, etc.).*

**vec3 diffuse_color**: *The base color of the material when illuminated.*

**float specular_exponent**: *Controls the shininess of the material, affecting the size of specular highlights.*


*The header also defines several material constants (ivory, glass, red rubber, mirror) with specific properties for use in the scene.*

### sphere.h
*This header defines the Sphere structure, which represents spherical objects in the scene.*

**vec3 center**: *The center position of the sphere in 3D space.*

**float radius**: *The radius of the sphere, determining its size.*

**Material material**: *The material associated with the sphere, defining its appearance and optical properties.*


*The header includes an array of predefined spheres with specific positions, sizes, and materials for rendering.*

### vec3.h
*This header defines the vec3 structure, which represents a 3D vector or point in space.*

OPERATOR OVERLOADING:

**float& operator[](const int i)**: *Allows access to vector components using array indexing.*

**vec3 operator(*)(const float v)**: *Scales the vector by a scalar value.*

**float operator(*)(const vec3& v)**: *Computes the dot product with another vector.*

**vec3 operator+(const vec3& v)**: *Adds another vector to this vector.*

**vec3 operator-(const vec3& v)**: *Subtracts another vector from this vector.*

**vec3 operator-()**: *Negates the vector.*

METHODS:

**float norm() const**: *Computes the Euclidean norm (length) of the vector.*

**vec3 normalized() const**: *Returns a normalized version of the vector (unit length).*


MATH:

**vec3 cross(const vec3 v1, const vec3 v2)**: *Computes the cross product of two vectors, resulting in a vector perpendicular to both.*

**vec3 reflect(const vec3 &I, const vec3 &N)**: *Calculates the reflection of a vector I off a surface with normal N.*

**vec3 refract(const vec3 &I, const vec3 &N, const float eta_t, const float eta_i=1.f)**: *Computes the refraction of a vector I through a surface with normal N, applying Snell's law.*

## MAIN SCRIPT
### ray_sphere_intersect
*Determines if a ray intersects with a sphere and calculates the intersection distance.*

PARAMETERS:

**const vec3 &orig**: *The origin of the ray.*

**const vec3 &dir**: *The direction of the ray.*

**const Sphere &s**: *The sphere to check for intersection.*

1.	Calculate the vector L from the ray origin to the sphere center.
2.	Compute tca, the projection of L onto the ray direction.
3.	Calculate d2, the squared distance from the sphere center to the ray.
4.	If d2 exceeds the sphere's radius squared, return no intersection.
5.	Calculate thc, the distance from tca to the intersection points.
6.	Determine the two intersection distances t0 and t1.
7.	Return the closest intersection point that is greater than a small offset (to avoid self-occlusion).

### scene_intersect
*Checks for intersections between a ray and the scene objects (spheres and a checkerboard).*

PARAMETERS:

**const vec3 &orig**: *The origin of the ray.*

**const vec3 &dir**: *The direction of the ray.*

1.	Initialize variables for the nearest intersection point and normal vector.
2.	Check for intersection with the checkerboard plane.
3.	Iterate through all spheres in the scene, checking for intersections.
4.	Update the nearest intersection point and normal if a closer intersection is found.
5.	Return the result indicating whether an intersection occurred, along with the intersection point, normal, and material.

### cast_ray
*Recursively traces a ray through the scene to determine the color at a given point.*

PARAMETERS:

**const vec3 &orig**: *The origin of the ray.*

**const vec3 &dir**: *The direction of the ray.*

**const int depth**: *The recursion depth for reflections and refractions.*

1.	Call scene_intersect to find the nearest intersection.
2.	If no intersection or maximum depth is reached, return the background color.
3.	Calculate reflection and refraction directions.
4.	Recursively call cast_ray for reflection and refraction colors.
5.	Compute diffuse and specular light intensities based on light sources.
6.	Combine the colors based on material properties and return the final color.

### main
1.	Define constants for the framebuffer dimensions and field of view.
2.	Create a framebuffer to store pixel colors.
3.	Use OpenMP to parallelize the rendering loop:
    For each pixel, calculate the ray direction based on pixel coordinates.
    Normalize the direction vector.
    Call cast_ray to compute the color for the pixel.
4.	Open a file stream to write the output image in PPM format.
5.	Write the PPM header and pixel data to the file.
6.	Return 0 to indicate successful execution.
