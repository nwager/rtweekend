#include <math.h>

#include <raytracer/vec3.h>

// Initialization

struct vec3 vec3_zero()
{
	return (struct vec3){ .e = {0.0, 0.0, 0.0} };
}

struct vec3 vec3_create(double e0, double e1, double e2)
{
	return (struct vec3){ .e = {e0, e1, e2} };
}

// In-place operations

struct vec3 vec3_negate(struct vec3 v)
{
	return vec3_create(-v.e[0], -v.e[1], -v.e[2]);
}

void vec3_add(struct vec3 *v, const struct vec3 *a)
{
	v->e[0] += a->e[0];
	v->e[1] += a->e[1];
	v->e[2] += a->e[2];
}

void vec3_multiply(struct vec3 *v, double t)
{
	v->e[0] *= t;
	v->e[1] *= t;
	v->e[2] *= t;
}

void vec3_divide(struct vec3 *v, double t)
{
	vec3_multiply(v, 1.0/t);
}

// Properties

double vec3_length(const struct vec3 *v)
{
	return sqrt(vec3_length_squared(v));
}

double vec3_length_squared(const struct vec3 *v)
{
	const double *e = v->e;
	return (e[0]*e[0]) + (e[1]*e[1]) + (e[2]*e[2]);
}

struct vec3 vec3_unit(const struct vec3 *v)
{
	return vec3_scalar(1.0/vec3_length(v), *v);
}

void vec3_write(FILE *fp, const struct vec3 *v)
{
	fprintf(fp, "%lf %lf %lf\n", v->e[0], v->e[1], v->e[2]);
}

// Binary immutable operations

struct vec3 vec3_sum(struct vec3 u, struct vec3 v)
{
	return vec3_create(
			u.e[0] + v.e[0],
			u.e[1] + v.e[1],
			u.e[2] + v.e[2]
		);
}

struct vec3 vec3_difference(struct vec3 u, struct vec3 v)
{
	return vec3_sum(u, vec3_scalar(-1.0, v));
}

double vec3_dot(struct vec3 u, struct vec3 v)
{
	return (u.e[0]*v.e[0]) + (u.e[1]*v.e[1]) + (u.e[2]*v.e[2]);
}

struct vec3 vec3_cross(struct vec3 u, struct vec3 v)
{
	return vec3_create(
			u.e[1] * v.e[2] - u.e[2] * v.e[1],
			u.e[2] * v.e[0] - u.e[0] * v.e[2],
			u.e[0] * v.e[1] - u.e[1] * v.e[0]
	);
}

struct vec3 vec3_scalar(double t, struct vec3 v)
{
	vec3_multiply(&v, t);
	return v;
}
