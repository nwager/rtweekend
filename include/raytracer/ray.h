#ifndef RAY_H
#define RAY_H

#include <raytracer/vec3.h>

struct ray {
	struct vec3 orig, dir;
};

struct ray ray_zero();
struct ray ray_create(const struct vec3 orig, const struct vec3 dir);

struct vec3 ray_at(const struct ray *r, double t);

#endif // RAY_H
