#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include <raytracer/ray.h>

struct hit_record {
	point3_t p;
	vec3_t normal;
	double t;
};

// Abstract "class" for hittable objects.
struct hittable {
	bool (*hit)(const struct ray *r, double ray_tmin, double ray_tmax,
			struct hit_record *rec, void *data);
	void *data; // Optional, generic data struct for hittable object
		    // to be passed to hit()
};

#endif // HITTABLE_H
