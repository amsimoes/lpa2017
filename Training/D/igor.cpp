#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>

void print_matrix(int **matrix, int rows, int cols) {
	for(int i=0; i<rows; i++) {
		for(int j=0; j<cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}


void input( int &change,  int &num_coins,  int* &coins) {
	std::cin >> change;
	std::cin >> num_coins;
	
	coins = ( int*) malloc(sizeof( int)*num_coins);

	for(int i=0; i<num_coins; i++)
		std::cin >> coins[i];

	/*for(int j=0; j<num_coins; j++)
		printf("%d ", coins[j]);
	printf("\n");*/
}

void change() {
	 int input_number, num_coins;
	 int change;
	 int *coins;

	std::cin >> input_number;
	for(int i=0; i<input_number; i++) {
		input(change, num_coins, coins);
		int **matrix = (int**) malloc(sizeof(int*)*num_coins+1);
		for(int i=0; i<=num_coins; i++)
			matrix[i] = (int*) malloc(sizeof(int)*change+1);

		//int matrix[num_coins+1][change+1];


		for (int j = 0; j <=num_coins; j++){
		 	matrix[j][0] = 1;
		}
		for (int i = 1; i <=change; i++) {
		 	matrix[0][i] = 0;
		}

		for(int i = 0; i< num_coins; i++){
			printf("coins[%d] = %d\n", i, coins[i]);
		}
		for (int i = 1; i <=num_coins; i++){
			for (int j = 1; j <change; j++){
				//printf("MANO J = %d\n", j);
		  		if(coins[i-1]>j){
		  			matrix[i][j]=matrix[i-1][j];
		  		}
		  		else{
		  			/*printf("coins[i-1] = %d, com i = %d\n", coins[i-1],i);
		  			printf("matrix[i-1][j-coins[i]] = %d\n", matrix[i-1][j-coins[i-1]]);
		  			printf("matrix[i-1][j] = %d\n", matrix[i-1][j]);*/
		  			matrix[i][j] = matrix[i-1][j] + matrix[i-1][j-coins[i-1]];
		  		}
		  	}
		}
		print_matrix(matrix, num_coins, change);

		printf("%d\n", matrix[num_coins-1][change-1]);
		free(coins);
	}
} 

int main() {
	std::ios::sync_with_stdio(false);
	change();
	return 0;
}