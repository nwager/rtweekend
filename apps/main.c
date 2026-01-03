#include <stdio.h>
#include <unistd.h>

#include <raytracer/vec3.h>
#include <raytracer/color.h>

int main()
{
	// Image
	const int image_width = 256;
	const int image_height = 256;
	const char fname[] = "image.ppm";

	// File
	FILE *fp;
	fp = fopen(fname, "w");

	// Render
	fprintf(fp, "P3\n%d %d\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++) {
		printf("\rScanlines remaining: %d ", image_height - j);
		fflush(stdout);
		for (int i = 0; i < image_width; i++) {
			struct vec3 pixel_color = vec3_create(
					(double)i / (image_width - 1),
					(double)j / (image_height - 1),
					0.0);

			color_write(fp, &pixel_color);
		}
	}

	printf("\rDone.                 \n");

	fclose(fp);
}
