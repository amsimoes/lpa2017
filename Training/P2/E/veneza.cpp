#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

using namespace std;

int n_cases = 0;
int n_connections = 0;

int gond1[27][27], gond2[27][27];
int conns1[27][27], conns2[27][27];


void floyd_warshall() {
	for (int i=0; i<27; i++) {
		for (int j=0; j<27; j++) {
			if (gond1[i][j] == 1) {
				conns1[i][j] = 1;
			} else {
				conns1[i][j] = 0;
			}
			if (gond2[i][j] == 1) {
				conns2[i][j] = 1;
			} else {
				conns2[i][j] = 0;
			}
		}
	}

	for (int k=0; k<27; k++) {
		for (int i=0; i<27; i++) {
			for (int j=0; j<27; j++) {
				conns1[i][j] = conns1[i][j] || (conns1[i][k] && conns1[k][j]);
				conns2[i][j] = conns2[i][j] || (conns2[i][k] && conns2[k][j]);
				/*if (gond1[i][k] == 1 && gond1[k][j] == 1) {
					conns1[i][j] = 1;
				}
				if (gond2[i][k] == 1 && gond2[k][j] == 1) {
					conns2[i][j] = 1;
				}*/
			}
		}
	}
	for (int i=0; i<27; i++) {
		for (int j=0; j<27; j++) {
			if (conns1[i][j] != conns2[i][j]) {
				//printf("conns1[%d][%d] = %d / conns2[%d][%d] = %d\n", i, j, conns1[i][j], i, j, conns2[i][j]);
				printf("NO\n");
				return;
			}
		}
	}
	printf("YES\n");
}


void input() {
	for (int k=0; k<=1; k++) {
		scanf("%d\n", &n_connections);

		for (int i=0; i < n_connections; i++) {
			char from, to;

			scanf("%c %c\n", &from, &to);
			int index1 = (int) (from - 65);
			int index2 = (int) (to - 65);

			if (k == 0) {
				gond1[index1][index2] = 1;
			} else {
				gond2[index1][index2] = 1;
			}
		}
	}
}

void print_places() {
	for (int i=0; i < 26; i++) {
		for (int j=0; j < 26; j++) {
			if (gond1[i][j] || gond2[i][j])
				printf("gond1[%d][%d] = %d / gond2[%d][%d] = %d\n", i, j, gond1[i][j], i, j, gond2[i][j]);
		}
	}
}

void print_connections() {
	for (int i=0; i < 26; i++) {
		for (int j=0; j < 26; j++) {
			if (conns1[i][j] || conns2[i][j])
				printf("conns1[%d][%d] = %d / conns2[%d][%d] = %d\n", i, j, conns1[i][j], i, j, conns2[i][j]);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);	

	for (int i=0; i<27; i++) {
		for (int j=0; j<27; j++) {
			gond1[i][j] = 0;
			gond2[i][j] = 0;
			conns1[i][j] = 0;
			conns2[i][j] = 0;
		}
	} 

	scanf("%d", &n_cases);
	for (int i=0; i < n_cases; i++) {
		input();

		//print_places();
		floyd_warshall();
		//print_connections();

		for (int j=0; j<27; j++) {
			for (int k=0; k<27; k++) {
				gond1[j][k] = 0;
				gond2[j][k] = 0;
				conns1[j][k] = 0;
				conns2[j][k] = 0;
			}
		}
		n_connections = 0; 

		if (n_cases > 1 && i != n_cases-1)
			printf("\n");
	}

	return 0;
}