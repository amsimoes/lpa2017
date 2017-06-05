#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

int n_places = 0;
int n_roads = 0;

char line[101];

int counter = 0;
int matrix[1000][1000];
int low[1000];
int dfs[1000];
int visited[1000];

int parents[1000];

int art_points = 0;
int flag = 0;

void articulation(int v_index) {
	counter++;
	low[v_index] = counter;
	dfs[v_index] = counter;

	visited[v_index] = 1;

	for (int i=0; i < n_places; i++) {
		if (matrix[v_index][i] == 1 && i != v_index) {
			//int w = matrix[v_index][i];			
			int w = i;

			if (dfs[w] == -1) {
				parents[w] = v_index;
				articulation(w);
				low[v_index] = min(low[v_index], low[w]);

				if (low[w] > dfs[v_index]) {
					flag = 1;
					printf("%d %d\n", min(w, v_index), max(w, v_index));
				}
			} else if (parents[v_index] != w) {
				low[v_index] = min(low[v_index], dfs[w]);
			}
		}
	}
}

void print_adj_matrix() {
	for (int i=0; i<n_places; i++) {
		for (int j=0; j<n_places; j++) {
			printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
		}
	}	
}

int main() {
	ios::sync_with_stdio(false);

	for (int i=0; i < 100; i++) {
		for (int j=0; j < 100; j++) {
			matrix[i][j] = -1;
		}
	}
	n_places = 0;
	n_roads = 0;
	art_points = 0;

	while (scanf("%d %d", &n_places, &n_roads) == 2) {
		for (int i=0; i < n_roads; i++) {
			int p1, p2;
			scanf("%d %d", &p1, &p2);

			matrix[p1][p2] = 1;
			matrix[p2][p1] = 1;	
		}

        for (int v = 0; v < 1000; v++) {
            low[v] = -1;
            dfs[v] = -1;
            parents[v] = 0;
            visited[v] = 0;
        }
 		
        //printf("haha\n");

 		for (int i=0; i < n_places; i++) {
	 		if (dfs[i] == -1)       
				articulation(i);	
 		}

 		/*int road = 0;
 		for (int i=0; i < 1000; i++) {
			if (low[i] > dfs[parents[i]]) {
				road = 1;
				printf("%d %d\n", min(parents[i], i), max(parents[i], i));
			}
 		}*/
 		if (!flag)
 			printf("No road\n");

		counter = 0;
		art_points = 0;
		flag = 0;

		for (int i=0; i < 1000; i++) {
			for (int j=0; j < 1000; j++) {
				matrix[i][j] = -1;
			}
			visited[i] = 0;
			low[i] = 0;
			dfs[i] = 0;
			parents[i] = 0;
		}
	}
	
	return 0;
}