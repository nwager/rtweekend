#include <stdio.h>
#include <unistd.h>

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
			double r = (double)i / (image_width - 1);
			double g = (double)j / (image_height - 1);
			double b = 0.0;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);

			fprintf(fp, "%d %d %d\n", ir, ig, ib);
		}
	}

	printf("\rDone.                 \n");

	fclose(fp);
}
