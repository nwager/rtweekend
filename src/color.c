#include <stdio.h>

#include <raytracer/color.h>
#include <raytracer/vec3.h>

void color_write(FILE *fp, const struct vec3 *color)
{
	double r = color->x;
	double g = color->y;
	double b = color->z;

	// Translate the [0,1] component values to the byte range [0,255].
	int rbyte = (int)(255.999 * r);
	int gbyte = (int)(255.999 * g);
	int bbyte = (int)(255.999 * b);

	// Write out the pixel color components.
	fprintf(fp, "%d %d %d\n", rbyte, gbyte, bbyte);
}
