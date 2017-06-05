#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <limits.h>
#include <algorithm>

using namespace std;

int matrix[801][801];
int distances[800];

int main() {
	ios::sync_with_stdio(false);
	int n_followers;
	
	while (scanf("%d", &n_followers) == 1) {
		for(int i=0; i<n_followers; i++){
			matrix[i][0] = 0;
		}
		for(int i = 0; i<n_followers; i++){
			int follower_followers, n;
			scanf("%d", &follower_followers);
			//matrix[i][0] = follower_followers;
			for(int j=1; j<=follower_followers; j++){
				scanf("%d", &n);
				matrix[n-1][0]++;
				matrix[n-1][matrix[n-1][0]] = i;
				printf("matrix[%d][%d] = %d\n", n-1, matrix[n-1][0], matrix[n-1][matrix[n-1][0]]);
			}
		}
		int better = 0;
		int best[801];
		int best_result = matrix[0][0]+1;
		for(int i=0; i<n_followers; i++){
			if(matrix[i][0] == best_result){
				best[better] = matrix[i][0];
				better++;
			}
			else if(matrix[i][0] > best_result){
				best_result = matrix[i][0];
				best[0] = matrix[i][0];
				better = 1;
			}
		}
		if(better == 0)
			printf("King of popularity!\n");
		else{
			for(int i=0; i<800; i++){
				distances[i] = 800*800;
			}
			distances[0] = 0;
			for(int i=0; i<n_followers; i++){
					for(int j=1; j<=matrix[i][0]; j++){
						/*if(matrix[i][j] == 5)
							printf("distances[%d]=%d, distances[%d]=%d\n", matrix[i][j], distances[matrix[i][j]], i, distances[i]);
						printf("matrix[%d][%d] = %d\n", i,j,matrix[i][j]);*/
						//printf("distances[%d]= %d\n", i, distances[i]);
						distances[matrix[i][j]-1] = min(distances[matrix[i][j]-1], distances[i]+1);
						//printf("distances[%d]=%d\n", matrix[i][j], distances[matrix[i][j]]);
					}
			}
			int best_distance = 800*800;
			for(int i=0; i<better; i++){
				//printf("best[%d]=%d\n", i, best[i]);
				if(distances[best[i]] < best_distance){
					//printf("better_distance\n");
					best_distance = distances[best[i]];
				}
			}
			if(best_distance != 640000)
				printf("%d\n", best_distance);
			else
				printf("King of popularity!\n");
		}
	}
	
	return 0;
}