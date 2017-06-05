#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

int n_places;
char line[101];

int counter = 0;
int matrix[101][101];
int low[101];
int dfs[101];

int pre[101];

int art_points = 0;

int check_parent(int w, int v) {
	for (int j=0; j<n_places; j++) {
		//printf("matrix[%d][%d] = %d\n", w, j, matrix[w][j]);
		if (matrix[w][j] == v)
			return 0;
	}
	return 1;
}

void articulation(int v_index) {
	counter++;
	low[v_index] = counter;
	dfs[v_index] = counter;
	int flag = 0;

	//printf("v_index = %d\n", v_index);
	for (int i=0; i < n_places; i++) {
		if (matrix[v_index][i] != -1) {
			int w = matrix[v_index][i];
			//printf("w = %d\n", matrix[v_index][i]);

			//printf("v = %d / w = %d / i = %d / dfs[%d] = %d / art_points = %d \n", v_index, w, i, v_index, dfs[v_index], art_points);
			if (dfs[w] == -1) {
				articulation(w);
				low[v_index] = min(low[v_index], low[w]);

				if (dfs[v_index] == 1 && dfs[w] != 2) {
					if (!flag)
						art_points++;
					flag = 1;
				} else if (dfs[v_index] != 1 && low[w] >= dfs[v_index]) {
					if (!flag)
						art_points++;
					flag = 1;
				}
			} else if (check_parent(w, v_index)) {
				//printf("not parent\n");
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

void insert_matrix(int index, int value) {
	for (int j=0; j<n_places; j++) {
		if (matrix[index][j] == -1) {
			matrix[index][j] = value;
			break;
		}
	}
}

void input() {
	int parent;
	scanf("%d", &n_places);
	
	if (n_places == 0)
		exit(0);
	for (int i=0; i<=n_places; i++) {
		scanf("%d", &parent);
		if (parent == 0) 
			break;

		fgets(line, 101, stdin);
		char* tk = strtok(line, " ");
		while (tk != NULL) {
			insert_matrix(parent-1, atoi(tk)-1);
			insert_matrix(atoi(tk)-1, parent-1);
			tk = strtok(NULL, " ");
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
	art_points = 0;

	while (1) {
		input();
		//print_adj_matrix();

        for (int v = 0; v < 101; v++) {
            low[v] = -1;
            dfs[v] = -1;
        }
        
		articulation(0);

		printf("%d\n", art_points);
		counter = 0;
		art_points = 0;

		for (int i=0; i < 100; i++) {
			for (int j=0; j < 100; j++) {
				matrix[i][j] = -1;
			}
		}
	}
	
	return 0;
}