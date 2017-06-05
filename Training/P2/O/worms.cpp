#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

struct edges_t {
	int from;
	int dest;
	int years;
};

int n_cases;
int n_functions;
int n_stars;
int n_holes;

int* nodes;
edges_t** edges;

void bellman_ford() {
	nodes[0] = 0;
	for (int i=0; i<n_stars; i++) {
		//printf("ciclo 1, i = %d\n", i);
		for (int j=0; j<n_holes; j++) {
			//printf("ciclo 1, j = %d\n", j);
			if (edges[j]->from == i) {
				nodes[edges[j]->dest] = min(nodes[edges[j]->dest], nodes[i] + edges[j]->years);
			}
			
		}
	}
	for (int j=0; j<n_holes; j++) {
		//printf("entrei segundo ciclo\n");
		int old = nodes[edges[j]->dest];
		nodes[edges[j]->dest] = min(nodes[edges[j]->dest], nodes[edges[j]->from] + edges[j]->years);
		if(old > nodes[edges[j]->dest]){
			printf("possible\n");
			return;
		}
	}
	printf("not possible\n");
}

void input() {
	scanf("%d %d", &n_stars, &n_holes);

	nodes = (int*) malloc (sizeof(int) * 1000);
	for (int k=0; k<=n_stars; k++) {
		nodes[k] = 99999;
	}

	edges = (edges_t**) malloc (2000 * sizeof(edges_t*)); 
	for (int i=0; i<=n_holes; i++) {
		edges[i] = (edges_t*) malloc (sizeof(edges_t));
		edges[i]->from = 0;
		edges[i]->dest = 0;
		edges[i]->years = 0;	
	}

	for (int i=0; i < n_holes; i++) {
		scanf("%d %d %d", &edges[i]->from, &edges[i]->dest, &edges[i]->years);
	}
}

int main() {
	ios::sync_with_stdio(false);	

	n_cases = 0;

	scanf("%d\n", &n_cases);
	for (int i=0; i<n_cases; i++) {
		input();
		bellman_ford();
	}

	return 0;
}