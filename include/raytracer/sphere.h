#ifndef SPHERE_H
#define SPHERE_H

#include <raytracer/hittable.h>

struct sphere_data {
	point3_t center;
	double radius;
};

struct sphere_data create_sphere_data(point3_t center, double radius);
struct hittable create_sphere_hittable(struct sphere_data * const d);

#endif // SPHERE_H
