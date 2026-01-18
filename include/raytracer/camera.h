#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include <raytracer/hittable.h>
#include <raytracer/vec3.h>

struct camera {
	point3_t center;
	point3_t pixel00_loc;
	vec3_t pixel_delta_u;
	vec3_t pixel_delta_v;
	double aspect_ratio;
	int image_width;
	int image_height;
};

void camera_initialize(struct camera *c, double aspect_ratio, int image_width);
void camera_render(const struct camera *c, const struct hittable *world, FILE *fp);

#endif // CAMERA_H
