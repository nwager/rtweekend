#include <stdio.h>

#include <raytracer/color.h>
#include <raytracer/vec3.h>

color_t color_create(double r, double g, double b)
{
	return vec3_create(r, g, b);
}

void color_write(FILE *fp, const color_t *color)
{
	// Translate the [0,1] component values to the byte range [0,255].
	int rbyte = (int)(255.999 * color->x);
	int gbyte = (int)(255.999 * color->y);
	int bbyte = (int)(255.999 * color->z);

	// Write out the pixel color components.
	fprintf(fp, "%d %d %d\n", rbyte, gbyte, bbyte);
}
