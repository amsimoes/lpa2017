#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

void input(int &change, int &num_coins, int* &coins) {
	std::cin >> change;
	std::cin >> num_coins;
	
	coins = (int*) malloc(sizeof(int)*num_coins);

	for(int i=0; i<num_coins; i++)
		std::cin >> coins[i];

	for(int j=0; j<num_coins; j++)
		printf("%d ", coins[j]);
	printf("\n");
}

int calc(int change, int* &coins, int num_coins, int index, int value) {
	for(int i=index+1; i<num_coins; i++) {
		if(value == change) {
			// adicionar as solucoes
		} else if(value + coins[i] > change) {
			continue;
		} else if(value + coins[i] < change) {

		} else if(value + coins[i] == change) {

		}

	}
}

void change() {
	int input_number, change, num_coins;
	int *coins = {};

	std::cin >> input_number;
	for(int i=0; i<input_number; i++) {
		input(change, num_coins, coins);

		for(int j=0; j<num_coins-1; j++) {
			calc(change, coins, num_coins, j);
		}

		free(coins);
	}
} 

int main() {
	std::ios::sync_with_stdio(false);
	change();
	return 0;
}
