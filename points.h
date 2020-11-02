#ifndef _POINTS_H_
#define _POINTS_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct _point_t {
	int x, y;
} point_t;

extern void point_init(point_t *point, int x, int y);

extern void point_delete(point_t *point);

extern void points_add(point_t *points, int x, int y);

extern bool points_contains(point_t *points, int x, int y);

extern void points_reset(point_t *points, int points_amount);

#endif
