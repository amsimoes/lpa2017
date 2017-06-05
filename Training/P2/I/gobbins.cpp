#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <limits.h>
#include <algorithm>
#include <queue>

using namespace std;

typedef struct node {
	vector<int> connections;
	int color;
} node;

vector <node> Graph;
int n_trains, n_stations;

bool BFS(int vertice) {
	queue <node> nodes_q;
	Graph[vertice].color = 1;

	nodes_q.push(Graph[vertice]);
	while (!nodes_q.empty()) {
		node t = nodes_q.front();
		nodes_q.pop();

		for (unsigned int i=0; i<t.connections.size(); i++) {
			if (Graph[t.connections[i]-1].color == 0) {
				if (t.color == 1) {
					Graph[t.connections[i]-1].color = 2;
				} else if (t.color == 2) {
					Graph[t.connections[i]-1].color = 1;
				}

				nodes_q.push(Graph[t.connections[i]-1]);
			} else if (Graph[t.connections[i]-1].color == t.color) {
				return false;
			}
		}
	}
	return true;
}


int main() {
	ios::sync_with_stdio(false);	

	while (scanf("%d %d\n", &n_trains, &n_stations) == 2) {

		for (int i=0; i < n_trains; i++) {
			node n;
			n.color = 0;
			Graph.push_back(n);
		}

		for(int i=0; i < n_stations; i++) {
			int train, station = 0;
			scanf("%d %d\n", &train, &station);

			Graph[train-1].connections.push_back(station);
			Graph[station-1].connections.push_back(train);
		}

		if (BFS(0)) {
			printf("No\n");
		} else {
			printf("Yes\n");
		}

		Graph.clear();
	}

	return 0;
}