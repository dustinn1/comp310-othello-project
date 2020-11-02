#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "points.h"

point_t* point_init(int x, int y) {
	point_t* point = (point_t*) malloc(sizeof(point_t));
	point->x = x;
	point->y = y;
	return point;
}

void point_delete(point_t *point) {
	point = calloc(sizeof(point), sizeof(point_t));
	free(point);
}

bool points_contains(point_t **points, int points_amount, int x, int y) {
	for (int i = 0; i < points_amount; ++i) {
		if (points[i]->x == x && points[i]->y == y) {
			return true;
		}
	}
	return false;
}

void points_reset(point_t **points, int points_amount) {
	for (int i = 0; i < points_amount; ++i) {
		point_delete(points[i]);
	}
}

void points_print(point_t **points, int points_amount) {
	for (int i = 0; i < points_amount; ++i) {
		printf("%i, %i", points[i]->x, points[i]->y);
		if (i != points_amount-1) printf(" | ");
	}
}
