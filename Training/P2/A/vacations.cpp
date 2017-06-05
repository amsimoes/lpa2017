#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

int n_places;
int end_place;
int min_spent; 
int matrix[200][200];
int already_visited[200];


void dfs(int already_spent, int cur_place) {
	//	printf("cur_place = %d\n", cur_place);
	if(cur_place == end_place)
		return;
	for(int j = 0; j < n_places; j++) {
		if (already_spent + matrix[cur_place-1][j] > min_spent) {
			continue;
		} else if (j == end_place-1 && matrix[cur_place-1][j] != -1) {
			min_spent = matrix[cur_place-1][j] + already_spent;
			continue;
		} else if (already_visited[j] == -2 && (matrix[cur_place-1][j] != -1 && matrix[cur_place-1][j] != 0)) {
			already_visited[j] = 1;
			dfs(already_spent + matrix[cur_place-1][j], j+1);
			already_visited[j] = -2;
		}
	}
}

void floyd() {
	for(int k=0; k < n_places; k++) {
		for(int i=0; i < n_places; i++) {
			for(int j=0; j < n_places; j++) { 
				matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
				//printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
			}
		}
	}
}

void adjust_matrix() {
	for (int i=0; i < n_places; i++) {
		for (int j=0; j < n_places; j++) {
			if (matrix[i][j] == -1) {
				matrix[i][j] = 999999;
				//printf("matrix = %d\n", matrix[i][j]);
			}
		}
	}
}

void input() {
	int useless = 0;
	for(int i = 0; i < n_places; i++){
		scanf("%d ", &useless);
		for(int j = 0; j<n_places; j++){
			scanf("%d ", &matrix[i][j]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);	

	for(int i=0; i<200; i++) {
		for(int j=0; j<200; j++) {
		 		matrix[i][j] = 0;
		}
	}

	for(int i=0; i<200; i++) {
		already_visited[i] = -2;
	}

	min_spent = INT_MAX;
	n_places = 0;
	end_place = 0;

	scanf("%d %d\n", &n_places, &end_place);

	input();

	//dfs(0, 1);

	adjust_matrix();
	floyd();

	//printf("%d\n", min_spent);
	printf("%d\n", matrix[0][end_place-1]);
	return 0;
}