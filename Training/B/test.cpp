#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

int best_path(int num_coins, int *coins){
    int max_sum=0, weight,result, cena=0; 

    for(int i = 0; i< num_coins; i++){
        max_sum += coins[i];
    }

    if(max_sum % 2 == 0) {
        weight = max_sum / 2;
    } else {
        weight = (max_sum+1) / 2;
    }

    int **matrix = (int**) malloc(sizeof(int*)*num_coins);
    for(int i = 0; i<weight; i++){
        matrix[i] = (int*) malloc(sizeof(int)*weight);
    }
    for(int i=0; i<num_coins; i++) {
        for(int j=0; j<weight; j++) {
            matrix[i][j] = 0;
        }
    }

    for(int i = 1; i<=num_coins; i++) {
        int vali = coins[i-1];
        for(int j=1; j<=weight; j++) {
            if(vali > j) {
                matrix[i][j] = matrix[i-1][j];
            } else {
                //printf("%d\n", std::max(matrix[i-1][j],matrix[i-1][j-vali] + vali));
                matrix[i][j] = std::max(matrix[i-1][j],matrix[i-1][j-vali] + vali);
            }
        }
    }

    result = max_sum - matrix[num_coins][weight];
    int cenas = abs(result - matrix[num_coins][weight]);
    printf("%d\n",cenas);
    return 0;
}

void algorithm(){
    //readInput
    int input_number,num_coins, result;
    int *coins;
    std::cin >> input_number; 
    for(int k=0; k<input_number; k++){
        std::cin >> num_coins; 
        coins = (int*)malloc(sizeof(int)*num_coins);
        for(int i=0; i<num_coins; i++){
            std::cin >> coins[i]; 
        }

        result=best_path(num_coins,coins);  
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    algorithm();
    return 0;
}