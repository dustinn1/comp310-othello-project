#ifndef _POINTS_H_
#define _POINTS_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>

typedef struct _point_t {
	int x, y;
} point_t;

extern point_t* point_init(int x, int y);

extern void point_delete(point_t *point);

extern bool points_contains(point_t **points, int x, int y);

extern bool points_is_empty(point_t **points);

extern void points_reset(point_t **points);

extern void points_print(point_t **points, int amount);

#endif
