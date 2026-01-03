#include <raytracer/ray.h>
#include <raytracer/vec3.h>

struct ray ray_zero()
{
	return ray_create(vec3_zero(), vec3_zero());
}

struct ray ray_create(const point3_t orig, const vec3_t dir)
{
	return (struct ray){
		.orig = orig,
		.dir = dir
	};
}

vec3_t ray_at(const struct ray *r, double t)
{
	return vec3_sum(r->orig, vec3_mscalar(r->dir, t));
}
