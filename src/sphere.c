#include <raytracer/sphere.h>
#include <raytracer/hittable.h>
#include <raytracer/vec3.h>
#include <stdbool.h>
#include <math.h>

static bool hit(const struct ray *r, double ray_tmin, double ray_tmax,
		struct hit_record *rec, void *data);

struct sphere_data create_sphere_data(const point3_t center, double radius)
{
	return (struct sphere_data){
		.center = center,
		.radius = radius
	};
}

struct hittable create_sphere_hittable(struct sphere_data * const d)
{
	return (struct hittable){
		.hit = hit,
		.data = d
	};
}

static bool hit(const struct ray *r, double ray_tmin, double ray_tmax,
		struct hit_record *rec, void *data)
{
	struct sphere_data *s = (struct sphere_data *)data;

	vec3_t oc = vec3_difference(s->center, r->orig);
	double a = vec3_length_squared(&r->dir);
	double h = vec3_dot(r->dir, oc);
	double c = vec3_length_squared(&oc) - (s->radius * s->radius);
	double discriminant = h*h - a*c;

	if (discriminant < 0)
		return false;

	double sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	double root = (h - sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root) {
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return false;
	}

	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vec3_dscalar(vec3_difference(rec->p, s->center), s->radius);
	vec3_t outward_normal = vec3_dscalar(vec3_difference(rec->p, s->center), s->radius);
	hit_record_set_face_normal(rec, r, &outward_normal);

	return true;
}
