#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include <raytracer/ray.h>
#include <raytracer/interval.h>

struct hit_record {
	point3_t p;
	vec3_t normal;
	double t;
	bool front_face;
};

/**
 * Abstract "class" for hittable objects.
 *
 * The pattern I've come up with is that each implementation of hittable can
 * specify a data struct that will get passed in to the hit function. I add
 * helper functions to create the data (caller-managed memory), and also a
 * helper function to create the actual hittable instance. For example:
 *
 * struct object_data {...};
 * struct object_data object_create_data(...);
 * struct hittable object_create_hittable(struct object_data * const d);
 */
struct hittable {
	bool (*hit)(const struct ray *r, struct interval ray_t,
			struct hit_record *rec, const void *data);
	void *data; // Optional, generic data struct for hittable object
		    // to be passed to hit()
};

void hit_record_set_face_normal(struct hit_record *rec, const struct ray *r,
		vec3_t outward_normal);

#endif // HITTABLE_H
