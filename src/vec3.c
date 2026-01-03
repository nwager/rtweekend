#include <math.h>

#include <raytracer/vec3.h>

// Initialization

vec3_t vec3_zero()
{
	return vec3_create(0.0, 0.0, 0.0);
}

vec3_t vec3_create(double e0, double e1, double e2)
{
	return (vec3_t){ .e = {e0, e1, e2} };
}

point3_t point3_create(double e0, double e1, double e2)
{
	return vec3_create(e0, e1, e2);
}

// In-place operations

vec3_t vec3_negate(vec3_t v)
{
	return vec3_create(-v.e[0], -v.e[1], -v.e[2]);
}

void vec3_add(vec3_t *v, const vec3_t *a)
{
	v->e[0] += a->e[0];
	v->e[1] += a->e[1];
	v->e[2] += a->e[2];
}

void vec3_subtract(vec3_t *v, const vec3_t *a)
{
	v->e[0] -= a->e[0];
	v->e[1] -= a->e[1];
	v->e[2] -= a->e[2];
}

void vec3_multiply(vec3_t *v, double t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

void vec3_divide(vec3_t *v, double t)
{
	vec3_multiply(v, 1.0/t);
}

// Properties

double vec3_length(const vec3_t *v)
{
	return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const vec3_t *v)
{
	const double *e = v->e;
	return (e[0]*e[0]) + (e[1]*e[1]) + (e[2]*e[2]);
}

vec3_t vec3_unit(const vec3_t *v)
{
	return vec3_dscalar(*v, vec3_length(v));
}

void vec3_write(FILE *fp, const vec3_t *v)
{
	fprintf(fp, "%lf %lf %lf\n", v->e[0], v->e[1], v->e[2]);
}

// Binary immutable operations

vec3_t vec3_sum(vec3_t u, vec3_t v)
{
	return vec3_create(
			u.e[0] + v.e[0],
			u.e[1] + v.e[1],
			u.e[2] + v.e[2]
		);
}

vec3_t vec3_difference(vec3_t u, vec3_t v)
{
	return vec3_sum(u, vec3_mscalar(v, -1.0));
}

double vec3_dot(vec3_t u, vec3_t v)
{
	return (u.e[0]*v.e[0]) + (u.e[1]*v.e[1]) + (u.e[2]*v.e[2]);
}

vec3_t vec3_cross(vec3_t u, vec3_t v)
{
	return vec3_create(
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]
	);
}

vec3_t vec3_mscalar(vec3_t v, double t)
{
	vec3_multiply(&v, t);
	return v;
}

vec3_t vec3_dscalar(vec3_t v, double t)
{
	vec3_divide(&v, t);
	return v;
}
