#ifndef RAY_H
#define RAY_H

#include <raytracer/vec3.h>

struct ray {
	point3_t orig;
	vec3_t dir;
};

struct ray ray_zero();
struct ray ray_create(const point3_t orig, const vec3_t dir);

vec3_t ray_at(const struct ray *r, double t);

#endif // RAY_H
