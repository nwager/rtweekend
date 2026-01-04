#include <math.h>

#include <raytracer/vec3.h>

// Initialization

vec3_t vec3_zero()
{
	return vec3_create(0.0, 0.0, 0.0);
}

vec3_t vec3_create(const double e0, const double e1, const double e2)
{
	return (vec3_t){ .e = {e0, e1, e2} };
}

point3_t point3_create(const double e0, const double e1, const double e2)
{
	return vec3_create(e0, e1, e2);
}

// Properties

double vec3_length(const vec3_t v)
{
	return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const vec3_t v)
{
	return (v.e[0]*v.e[0]) + (v.e[1]*v.e[1]) + (v.e[2]*v.e[2]);
}

vec3_t vec3_unit(const vec3_t v)
{
	return vec3_dscalar(v, vec3_length(v));
}

void vec3_write(FILE *fp, const vec3_t v)
{
	fprintf(fp, "%lf %lf %lf\n", v.e[0], v.e[1], v.e[2]);
}

// Immutable operations

vec3_t vec3_neg(const vec3_t v)
{
	return vec3_create(-v.e[0], -v.e[1], -v.e[2]);
}

vec3_t vec3_sum(const vec3_t u, const vec3_t v)
{
	return vec3_create(
			u.e[0] + v.e[0],
			u.e[1] + v.e[1],
			u.e[2] + v.e[2]
		);
}

vec3_t vec3_difference(const vec3_t u, const vec3_t v)
{
	return vec3_sum(u, vec3_mscalar(v, -1.0));
}

double vec3_dot(const vec3_t u, const vec3_t v)
{
	return (u.e[0]*v.e[0]) + (u.e[1]*v.e[1]) + (u.e[2]*v.e[2]);
}

vec3_t vec3_cross(const vec3_t u, const vec3_t v)
{
	return vec3_create(
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]
	);
}

vec3_t vec3_mscalar(const vec3_t v, const double t)
{
	return vec3_create(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

vec3_t vec3_dscalar(const vec3_t v, const double t)
{
	return vec3_mscalar(v, 1.0/t);
}
