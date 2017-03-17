#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>

std::vector<int> trocos;
std::vector< std::vector<int> > values;

void print_trocos() {
	for(unsigned int i=0; i<trocos.size(); i++) {
		printf("%d ", trocos[i]);
	}
	printf("\n");
}

void input(int &change, int &num_coins, int* &coins) {
	std::cin >> change;
	std::cin >> num_coins;
	
	coins = (int*) malloc(sizeof(int)*num_coins);

	for(int i=0; i<num_coins; i++)
		std::cin >> coins[i];

	/*for(int j=0; j<num_coins; j++)
		printf("%d ", coins[j]);
	printf("\n");*/
}

int calc(int change, int* &coins, int num_coins, int index, int value) {
	for(int i=index+1; i<num_coins; i++) {
		if(value + coins[i] > change) {
			continue;
		} else if(value + coins[i] < change) {
			value += coins[i];
			trocos.push_back(coins[i]);
		} else if(value + coins[i] == change) {
			//printf("value = %d | coins[i] = %d\n", value, coins[i]);
			trocos.push_back(coins[i]);
			//print_trocos();
			// sortear trocos e ver se a combinacao ja existe
			std::vector<int> temp = trocos;
			std::sort(temp.begin(), temp.end());
			if(std::find(values.begin(), values.end(), temp) == values.end()) {
				values.push_back(temp);
			}
			trocos.pop_back();
			//print_trocos();
		}
	}
	return 0;
}

void change() {
	int input_number, change, num_coins;
	int *coins;

	std::cin >> input_number;
	for(int i=0; i<input_number; i++) {
		input(change, num_coins, coins);

		for(int j=0; j<=num_coins-1; j++) {
			//printf("Coins[%d] = %d\n", j, coins[j]);
			if(coins[j] > change) {
				continue;
			} else if(coins[j] == change) {
				trocos.push_back(coins[j]);
				if(std::find(values.begin(), values.end(), trocos) == values.end()) {
					values.push_back(trocos);
				}
			} else if(coins[j] < change) {
				trocos.push_back(coins[j]);
				calc(change, coins, num_coins, j, coins[j]);
			}
			trocos.clear();
		}

		/*for(unsigned int k=0; k<values.size(); k++) {
			for(unsigned int h=0; h<values.at(k).size(); h++)
				printf("%d ", values[k][h]);
			printf("\n");
		}*/

		printf("%ld\n", values.size());
		values.clear();
		free(coins);
	}
} 

int main() {
	std::ios::sync_with_stdio(false);
	change();
	return 0;
}
