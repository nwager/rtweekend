#ifndef SPHERE_H
#define SPHERE_H

#include <raytracer/hittable.h>

struct sphere_data {
	point3_t center;
	double radius;
};

struct sphere_data sphere_create_data(point3_t center, double radius);
struct hittable sphere_create_hittable(struct sphere_data * const d);

#endif // SPHERE_H
