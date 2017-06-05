#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

int* nodes;
int visited;
int n_nodes;
int matrix[200][200];

void input() {
	scanf("%d", &n_nodes);
	for (int i=0; i<n_nodes; i++) {

	}
}

int main() {
	ios::sync_with_stdio(false);	

	for(int i=0; i<200; i++) {
		for(int j=0; j<200; j++) {
		 	matrix[i][j] = -1;
		}
	}

	n_nodes = 0;


	return 0;
}