#include <raytracer/hittable.h>
#include <raytracer/ray.h>
#include <raytracer/vec3.h>

void hit_record_set_face_normal(struct hit_record *rec, const struct ray *r,
		const vec3_t outward_normal)
{
	// Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

	rec->front_face = vec3_dot(r->dir, outward_normal) < 0;
	rec->normal = rec->front_face
			? outward_normal
			: vec3_neg(outward_normal);
}
