#ifndef VEC3_H
#define VEC3_H

#include <stdio.h>

typedef struct {
	union {
		double e[3];
		struct {
			double x, y, z;
		};
	};
} vec3_t;

typedef vec3_t point3_t;

// Initialization
vec3_t vec3_zero();
vec3_t vec3_create(double e0, double e1, double e2);
point3_t point3_create(double e0, double e1, double e2);

// Properties
double vec3_length(vec3_t v);
double vec3_length_squared(vec3_t v);
vec3_t vec3_unit(vec3_t v);

void vec3_write(FILE *fp, vec3_t v);

// Immutable operations
vec3_t vec3_neg(vec3_t v);
vec3_t vec3_sum(vec3_t u, vec3_t v);
vec3_t vec3_difference(vec3_t u, vec3_t v);
double vec3_dot(vec3_t u, vec3_t v);
vec3_t vec3_cross(vec3_t u, vec3_t v);
vec3_t vec3_mscalar(vec3_t v, double t);
vec3_t vec3_dscalar(vec3_t v, double t);

#endif // VEC3_H
