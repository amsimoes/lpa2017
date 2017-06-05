#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <limits>
#include <time.h>

//double best = std::numeric_limits<double>::infinity();
double best = 100000;
int visited = 0;

void input(int &n_places, int** &places) {
	std::cin >> n_places;
	places = (int **) malloc(sizeof(int*) * n_places);
	for(int i=0; i<n_places; i++) 
		places[i] = (int*) malloc(sizeof(int) * 3);
	for(int i=0; i<n_places; i++) {
		std::cin >> places[i][0];
		std::cin >> places[i][1];
		places[i][2] = 0;
	}
}

void shortPath(int index, double distance, int n_places, int** places) {
	if(distance > best)
		return;
	if(visited == n_places) {
		if(distance < best) {
			best = distance;
			return;
		}
	}
	for(int i=0; i<n_places; i++) {
		if(places[i][2] == 0) {
			places[i][2] = 1;
			visited++;
			double cenas = distance + sqrt((places[i][0] - places[index][0])*(places[i][0] - places[index][0])+(places[i][1] - places[index][1])*(places[i][1] - places[index][1]));
			if(cenas < best)
				shortPath(i, cenas, n_places, places);
			places[i][2] = 0;
			visited--;
		}
	}
}

void rowan() {
	//clock_t begin = clock();
	int n_places;
	int **places;

	input(n_places, places);

	for(int i=0; i<n_places; i++) {
		double distance = 0;
		shortPath(i, distance, n_places, places);
	}
	printf("%.3f\n", best);

	//clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("%f\n", time_spent);
}

int main() {
	std::ios::sync_with_stdio(false);
	rowan();
	return 0;
}