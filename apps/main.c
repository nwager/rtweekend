#include <stdio.h>

#include <raytracer/raytracer.h>
#include <raytracer/vec3.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>
#include <raytracer/sphere.h>
#include <raytracer/camera.h>

// Prototypes
int usage(int argc, char **argv);

// Definitions
int usage(int argc, char **argv)
{
	if (argc != 2) {
		printf("USAGE: %s <output_file>\n", argv[0]);
		return -1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	int ret = usage(argc, argv);
	if (ret)
		return ret;

	// Image
	const char *fname = argv[1];


	// File

	FILE *fp;
	fp = fopen(fname, "w");
	if (!fp) {
		printf("ERROR: Could not open file '%s'\n", fname);
		return -1;
	}

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

	// Camera
	struct camera cam;
	camera_initialize(&cam, 16.0/9.0, 400, 100);

	camera_render(&cam, &world, fp);

	fclose(fp);
}
