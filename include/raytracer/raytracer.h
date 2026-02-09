/**
 * Common header for raytracer project.
 */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdlib.h>

// Constants

const double PI = 3.1415926535897932385;

// Utility Functions

double degrees_to_radians(double degrees)
{
	return degrees * PI / 180.0;
}

double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

double random_double_range(double min, double max)
{
	return min + (max-min)*random_double();
}

#endif // RAYTRACER_H
