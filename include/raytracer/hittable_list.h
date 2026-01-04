#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <raytracer/hittable.h>

struct hittable_list_data {
	struct hittable **objects;
	int size;
};

struct hittable_list_data hittable_list_create_data(struct hittable * *const objects,
		int size);
struct hittable hittable_list_create_hittable(struct hittable_list_data * const d);

#endif // HITTABLE_LIST_H
