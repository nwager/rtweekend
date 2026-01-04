#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <raytracer/hittable.h>

struct hittable_list_data {
	struct hittable **objects;
	int size;
};

struct hittable_list_data create_hittable_list_data(struct hittable * *const objects,
		int size);
struct hittable create_hittable_list_hittable(struct hittable_list_data * const d);

#endif // HITTABLE_LIST_H
