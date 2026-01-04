#include <stdbool.h>

#include <raytracer/hittable_list.h>
#include <raytracer/hittable.h>

static bool hit(const struct ray *r, double ray_tmin, double ray_tmax,
		struct hit_record *rec, const void *data);

struct hittable_list_data hittable_list_create_data(struct hittable * *const objects,
		const int size)
{
	return (struct hittable_list_data){
		.objects = objects,
		.size = size
	};
}

struct hittable hittable_list_create_hittable(struct hittable_list_data * const d)
{
	return (struct hittable){
		.hit = hit,
		.data = d
	};
}

static bool hit(const struct ray *r, double ray_tmin, double ray_tmax,
		struct hit_record *rec, const void *data)
{
	struct hittable_list_data *d = (struct hittable_list_data *)data;
	struct hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = ray_tmax;

	for (struct hittable *object = *(d->objects);
			object < *(d->objects) + d->size;
			object++) {
		if (object->hit(r, ray_tmin, closest_so_far, &temp_rec, object->data)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
		}
	}

	return hit_anything;
}
