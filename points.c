#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>

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

bool points_contains(point_t **points, int x, int y) {
	for (int i = 0; i < 50; ++i) {
		if (points[i] != NULL && points[i]->x == x && points[i]->y == y) {
			return true;
		}
	}
	return false;
}

bool points_is_empty(point_t **points) {
	return (points[0] == NULL);
}

void points_reset(point_t **points) {
	for (int i = 0; i < 50; ++i) {
		if (points[i] != NULL) point_delete(points[i]);
	}
}

void points_print(point_t **points, int amount) {
	for (int i = 0; i < amount; ++i) {
		printw("%i, %i", points[i]->x, points[i]->y);
		if (i != amount-1) printw(" | ");
	}
}
