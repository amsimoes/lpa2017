#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n_cidades;
int matrix[501][501];
int costs[501][501];


int main()
{
    ios::sync_with_stdio(false);

    for (int i=0; i < n_cidades; i++) {
        for (int j=0; j < n_cidades; j++) {
            matrix[i][j] = 0;
            costs[i][j] = 0;
        }
    }

    scanf("%d", &n_cidades);
    for (int i=0; i < n_cidades; i++) {
        for (int j=0; j < n_cidades-1; j++) {
            int cost = 0;

            scanf("%d ", &cost);
            if (cost == -1) {
                matrix[i][j] = 99999;
            } else {
                matrix[i][j] = cost;
            }
        }
        int c;
        scanf("%d", &c);
        if (c == -1) {
            matrix[i][n_cidades-1] = 99999;
        } else {
            matrix[i][n_cidades-1] = c;
        }
    }

    int s1, t1;

    for (int i=0; i < n_cidades; i++) {
            for (int j=0; j < n_cidades; j++) {
                costs[i][j] = matrix[i][j];
            }
        }

    for (int k=0; k < n_cidades; k++) {
            for (int i=0; i < n_cidades; i++) {
                for (int j=0; j < n_cidades; j++) {
                    if (costs[i][j] > costs[i][k] + costs[k][j]) {
                        costs[i][j] = costs[i][k] + costs[k][j];
                    }
                }
            }
        }

    while (scanf("%d %d", &s1, &t1) == 2) {
        /*for (int i=0; i < n_cidades; i++) {
            for (int j=0; j < n_cidades; j++) {
                costs[i][j] = matrix[i][j];
            }
        }*/



        printf("%d\n", costs[s1-1][t1-1]);
    }



    return 0;
}
