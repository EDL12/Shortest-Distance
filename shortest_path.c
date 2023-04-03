//shortest_path.c
/* Based on the x and y coordinates iterating between the spool 
and elements arrays, find the shortest distance reaching all starting
from (0,0) */

/* Write shortest distance algorithm here*/

#include "shortest_path.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ELEMENTS 100

double distance(element *a, element *b) {
    double x1 = atof(a->x_pos);
    double y1 = atof(a->y_pos);
    double x2 = atof(b->x_pos);
    double y2 = atof(b->y_pos);
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void swap_elements(element *a, element *b) {
    element temp = *a;
    *a = *b;
    *b = temp;
}

void permute_elements(element *arr[], int start, int end, double *min_distance, element *min_path[], double curr_distance, element *curr_path[]) {
    if (start == end) {
        if (curr_distance < *min_distance) {
            *min_distance = curr_distance;
            memcpy(min_path, curr_path, MAX_ELEMENTS * sizeof(element*));
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap_elements(arr[start], arr[i]);
            double new_distance = curr_distance;
            if (start > 0) {
                new_distance += distance(arr[start-1], arr[start]);
            }
            if (new_distance < *min_distance) {
                curr_path[start] = arr[start];
                permute_elements(arr, start+1, end, min_distance, min_path, new_distance, curr_path);
            }
            swap_elements(arr[start], arr[i]);
        }
    }
}

void shortest_distance(element *arr[], int n) {
    double min_distance = INFINITY;
    element *min_path[MAX_ELEMENTS];
    element *curr_path[MAX_ELEMENTS];
    for (int i = 0; i < n; i++) {
        curr_path[i] = NULL;
    }
    permute_elements(arr, 0, n-1, &min_distance, min_path, 0, curr_path);
    memcpy(arr, min_path, n * sizeof(element*));
}

//sorts workList based on shortest possible path between all elements.
//returns nothing. Sorts array given to it. 


    //declare int minDistance, and currentDistance

    //iterate through every possible combination of paths. 
    //test distance
    //if distance < minDistance, workList = testArray, minDistance = currentDistance

    //end when done with possible combinations.



