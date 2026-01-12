#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>
#include <float.h>

struct interval {
	double min, max;
};

static inline struct interval interval_create(double min, double max)
{
	return (struct interval){ min, max };
}

static inline double interval_size(struct interval i)
{
	return i.max - i.min;
}

static inline bool interval_contains(struct interval i, double x)
{
	return i.min <= x && x <= i.max;
}

static inline bool interval_surrounds(struct interval i, double x)
{
	return i.min < x && x < i.max;
}

static const struct interval EMPTY = { DBL_MAX, DBL_MIN };
static const struct interval UNIVERSE = { DBL_MIN, DBL_MAX };

#endif // INTERVAL_H
