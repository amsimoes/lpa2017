#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

using namespace std;

int n_functions;
int matrix[200][200];
int already_visited[200];
int cycles[101];

void dfs(int cur_place) {
	//printf("cur_place = %d\n", cur_place);
	//printf("ainda nao estourei, curr place = %d\n", cur_place);
	int n_calls = matrix[cur_place][0];
	already_visited[cur_place] = 1;
	for(int j=0; j<n_calls; j++) {
		int index = matrix[cur_place][j+1];
		if (already_visited[index] == 1){
			cycles[index] = 1;
			continue;
		}
		dfs(index);
	}
	already_visited[cur_place] = -2;
}

void floyd() {
	for (int k=0; k<n_functions; k++) {
		for (int i=0; i<n_functions; i++) {
			for (int j=0; j<n_functions; j++) {
				matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
			}
		}
	}
}

void input() {
	for(int i = 0; i < n_functions; i++){
		int n_calls;
		scanf("%d ", &n_calls);
		for(int j = 0; j<n_calls; j++){
			int aux;
			scanf("%d ", &aux);
			matrix[i][aux] = 1;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);	
	for(int i=0; i<200; i++) {
		for(int j=0; j<200; j++) {
			matrix[i][j] = 0;
		}
		already_visited[i] = -2;
	}

	for(int i=0; i<101; i++) {
		cycles[i] = -1;
	}

	n_functions = 0;

	scanf("%d\n", &n_functions);

	input();

	floyd();

	for (int i=0; i<n_functions; i++) {
		if (matrix[i][i] == 1)
			printf("%d\n", i);
	}


	return 0;
}