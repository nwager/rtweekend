#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include <raytracer/vec3.h>

typedef vec3_t color_t;

color_t color_create(double r, double g, double b);

void color_write(FILE *fp, color_t color);

#endif // COLOR_H
