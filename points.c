#include <stdlib.h>
#include <stdbool.h>

#include "points.h"

void point_init(point_t *point, int x, int y) {
	point->x = x;
	point->y = y;
}

void point_delete(point_t *point) {
	point = calloc(sizeof(point), sizeof(point_t));
	free(point);
}

void points_add(point_t *points, int points_amount, int x, int y) {
	point_t *point = (point_t*) malloc(sizeof(point_t));
	point_init(point, x, y);
	points[points_amount+1] = point;
}

bool points_contains(point_t *points, int points_amount, int x, int y) {
	for (int i = 0; i < points_amount+1; i++) {
		if (points[i]->x == x && points[i]->y == y) {
			return true;
		}
	}
	return false;
}

void points_reset(point_t* points, int points_amount) {
	for (int i = 0; i < points_amount+1; i++) {
		point_delete(points[i]);
	}
}
