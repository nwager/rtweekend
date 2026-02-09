#include <float.h>
#include <stdio.h>

#include <raytracer/camera.h>
#include <raytracer/hittable.h>
#include <raytracer/vec3.h>
#include <raytracer/color.h>
#include <raytracer/ray.h>
#include <raytracer/raytracer.h>

static struct ray get_ray(const struct camera *c, int i, int j);
static vec3_t sample_square();
static color_t ray_color(const struct ray *r, const struct hittable *world);

void camera_initialize(struct camera *c, double aspect_ratio, int image_width,
		int samples_per_pixel)
{
	c->image_width = image_width;
	c->aspect_ratio = aspect_ratio;
	c->samples_per_pixel = samples_per_pixel;
	c->pixel_samples_scale = 1.0 / samples_per_pixel;

	// Calculate the image height, and ensure that it's at least 1.
	c->image_height = (int)(c->image_width / c->aspect_ratio);
	c->image_height = (c->image_height < 1) ? 1 : c->image_height;

	// Viewport widths less than one are ok since they are real valued.
	const double focal_length = 1.0;
	const double viewport_height = 2.0;
	const double viewport_width = viewport_height * (double)c->image_width / c->image_height;
	c->center = point3_create(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	const vec3_t viewport_u = vec3_create(viewport_width, 0, 0);
	const vec3_t viewport_v = vec3_create(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	c->pixel_delta_u = vec3_dscalar(viewport_u, c->image_width);
	c->pixel_delta_v = vec3_dscalar(viewport_v, c->image_height);

	// Calculate the position of the upper left pixel.
	point3_t viewport_upper_left = c->center;
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_create(0, 0, focal_length));
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_dscalar(viewport_u, 2));
	viewport_upper_left = vec3_difference(viewport_upper_left, vec3_dscalar(viewport_v, 2));
	c->pixel00_loc = vec3_sum(
			viewport_upper_left,
			vec3_mscalar(vec3_sum(c->pixel_delta_u, c->pixel_delta_v), 0.5));
}

void camera_render(const struct camera *c, const struct hittable *world, FILE *fp)
{
	fprintf(fp, "P3\n%d %d\n255\n", c->image_width, c->image_height);

	for (int j = 0; j < c->image_height; j++) {
		printf("\rScanlines remaining: %d ", c->image_height - j);
		fflush(stdout);
		for (int i = 0; i < c->image_width; i++) {
			color_t pixel_color = color_create(0, 0, 0);
			for (int sample = 0; sample < c->samples_per_pixel; sample++) {
				struct ray r = get_ray(c, i, j);
				pixel_color = vec3_sum(pixel_color, ray_color(&r, world));
			}
			color_write(fp, pixel_color);
		}
	}

	printf("\rDone.                 \n");
}

static struct ray get_ray(const struct camera *c, int i, int j)
{
	// Construct a camera ray originating from the origin and directed at a
	// randomly sampled point around pixel location (i, j).

	vec3_t offset = sample_square();
	point3_t pixel_sample = c->pixel00_loc;
	pixel_sample = vec3_sum(pixel_sample, vec3_mscalar(c->pixel_delta_u, i + offset.x));
	pixel_sample = vec3_sum(pixel_sample, vec3_mscalar(c->pixel_delta_v, j + offset.y));

	point3_t ray_origin = c->center;
	vec3_t ray_direction = vec3_difference(pixel_sample, ray_origin);

	return ray_create(ray_origin, ray_direction);
}

static vec3_t sample_square()
{
	// Returns the vector to a random point in the [-0.5.-0.5]-[+0.5,+0.5]
	// unit square.
	return vec3_create(random_double() - 0.5, random_double() - 0.5, 0);
}

static color_t ray_color(const struct ray *r, const struct hittable *world)
{
	// Render object if hit
	struct hit_record rec;
	if (world->hit(r, interval_create(0, DBL_MAX), &rec, world->data)) {
		return vec3_mscalar(vec3_sum(rec.normal, color_create(1,1,1)), 0.5);
	}

	// Render background
	vec3_t unit_direction = vec3_unit(r->dir);
	double a = 0.5 * (unit_direction.y + 1.0);
	color_t start_color = color_create(1.0, 1.0, 1.0);
	color_t end_color = color_create(0.5, 0.7, 1.0);
	return vec3_sum(vec3_mscalar(start_color, 1.0 - a),
			vec3_mscalar(end_color, a));
}

