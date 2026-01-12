#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include <raytracer/raytracer.h>
#include <raytracer/vec3.h>
#include <raytracer/color.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>
#include <raytracer/sphere.h>

color_t ray_color(const struct ray *r, const struct hittable *world)
{
	// Render object if hit
	struct hit_record rec;
	if (world->hit(r, 0, INFINITY, &rec, world->data)) {
		return vec3_mscalar(vec3_sum(rec.normal, color_create(1,1,1)), 0.5);
	}

	// Render background
	vec3_t unit_direction = vec3_unit(r->dir);
	double a = 0.5 * (unit_direction.y + 1.0);
	color_t start_color = color_create(1.0, 1.0, 1.0);
	color_t end_color = color_create(0.5, 0.7, 1.0);
	return vec3_sum(vec3_mscalar(start_color, 1.0 - a), vec3_mscalar(end_color, a));
}

int main()
{
	// Image
	const char fname[] = "image.ppm";

	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;

	// Calculate the image height, and ensure that it's at least 1.
	int image_height = (int)(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera

	// Viewport widths less than one are ok since they are real valued.
	const double focal_length = 1.0;
	const double viewport_height = 2.0;
	const double viewport_width = viewport_height * (double)image_width / image_height;
	const point3_t camera_center = point3_create(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	const vec3_t viewport_u = vec3_create(viewport_width, 0, 0);
	const vec3_t viewport_v = vec3_create(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	const vec3_t pixel_delta_u = vec3_dscalar(viewport_u, image_width);
	const vec3_t pixel_delta_v = vec3_dscalar(viewport_v, image_height);

	// Calculate the position of the upper left pixel.
	point3_t viewport_upper_left = camera_center;
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_create(0, 0, focal_length));
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_dscalar(viewport_u, 2));
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_dscalar(viewport_v, 2));
	const point3_t pixel00_loc = vec3_sum(
			viewport_upper_left,
			vec3_mscalar(vec3_sum(pixel_delta_u, pixel_delta_v), 0.5)
			);

	// File

	FILE *fp;
	fp = fopen(fname, "w");

	// World
	
	// Sphere 0
	struct sphere_data s0d = sphere_create_data(point3_create(0,0,-1), 0.5);
	struct hittable s0 = sphere_create_hittable(&s0d);
	// Sphere 1
	struct sphere_data s1d = sphere_create_data(point3_create(0,-100.5,-1), 100);
	struct hittable s1 = sphere_create_hittable(&s1d);

	struct hittable *objects[] = { &s0, &s1 };

	struct hittable_list_data world_data = hittable_list_create_data(objects, sizeof(objects) / sizeof(*objects));
	struct hittable world = hittable_list_create_hittable(&world_data);

	// Render

	fprintf(fp, "P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++) {
		printf("\rScanlines remaining: %d ", image_height - j);
		fflush(stdout);
		for (int i = 0; i < image_width; i++) {
			const vec3_t du = vec3_mscalar(pixel_delta_u, i);
			const vec3_t dv = vec3_mscalar(pixel_delta_v, j);
			point3_t pixel_center = pixel00_loc;
			pixel_center = vec3_sum(pixel_center, du);
			pixel_center = vec3_sum(pixel_center, dv);

			vec3_t ray_direction = vec3_difference(pixel_center, camera_center);
			struct ray r = ray_create(camera_center, ray_direction);

			const color_t pixel_color = ray_color(&r, &world);

			color_write(fp, pixel_color);
		}
	}

	printf("\rDone.                 \n");

	fclose(fp);
}
