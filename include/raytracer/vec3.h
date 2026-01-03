#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>

struct vec3 {
	union {
		double e[3];
		struct {
			double x;
			double y;
			double z;
		};
	};
};

// Initialization
struct vec3 vec3_zero();
struct vec3 vec3_create(double e0, double e1, double e2);

// In-place operations
void vec3_add(struct vec3 *v, const struct vec3 *a);
void vec3_multiply(struct vec3 *v, double t);
void vec3_divide(struct vec3 *v, double t);

// Properties
double vec3_length(const struct vec3 *v);
double vec3_length_squared(const struct vec3 *v);
struct vec3 vec3_unit(const struct vec3 *v);

void vec3_write(FILE *fp, const struct vec3 *v);

// Binary immutable operations
struct vec3 vec3_negate(struct vec3 v);
struct vec3 vec3_sum(struct vec3 u, struct vec3 v);
struct vec3 vec3_difference(struct vec3 u, struct vec3 v);
double vec3_dot(struct vec3 u, struct vec3 v);
struct vec3 vec3_cross(struct vec3 u, struct vec3 v);
struct vec3 vec3_scalar(double t, struct vec3 v);

#endif // VEC3_H
