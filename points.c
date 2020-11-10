#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>

#include "points.h"

// initialize the point with an x and y
// returns a pointer of point_t
point_t* point_init(int x, int y) {
	point_t* point = (point_t*) malloc(sizeof(point_t));
	point->x = x;
	point->y = y;
	return point;
}

// delete the point and free it from memory
void point_delete(point_t *point) {
	point = calloc(sizeof(point), sizeof(point_t));
	free(point);
}

// check to see if the point exists within an array.
// return true if the x and y specified in the parameters exist for a point in the array
bool points_contains(point_t **points, int x, int y) {
	for (int i = 0; i < 50; ++i) {
		if (points[i] != NULL && points[i]->x == x && points[i]->y == y) {
			return true;
		}
	}
	return false;
}

// check to see if the points list is empty by checking to see if the first array index is NULL or not
// return true if index of 0 is NULL
// return false otherwise
bool points_is_empty(point_t **points) {
	return (points[0] == NULL);
}

// reset the points array by deleting each point
void points_reset(point_t **points) {
	for (int i = 0; i < 50; ++i) {
		if (points[i] != NULL) point_delete(points[i]);
	}
}

// print the avaiable points on screen
void points_print(point_t **points, int amount) {
	for (int i = 0; i < amount; ++i) {
		printw("%i, %i", points[i]->x, points[i]->y);
		if (i != amount-1) printw(" | ");
	}
}
