#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

int best_path(int rows, int **matrix){
    int max; 
    for(int i=1; i<rows; i++){
        for(int j=0; j<=i; j++){ 
            if(j==0) {
                matrix[i][j] = matrix[i-1][j] + matrix[i][j]; 
            } else if(j==i) {
                matrix[i][j] = matrix[i-1][j-1] + matrix[i][j]; 
            } else { 
                if(matrix[i-1][j-1] > matrix[i-1][j]){
                    max = matrix[i-1][j-1] + matrix[i][j];
                } else {
                    max = matrix[i-1][j] + matrix[i][j];
                }
                matrix[i][j] = max;
            }
        } 
    }

    max = 0;
    for(int i=0;i<rows;i++){
        if(max < matrix[rows-1][i])
            max = matrix[rows-1][i];
    }

    return max;
}

void algorithm(){
    //readInput
    int input_number,rows;
    int **matrix;
    int *results;
    std::cin >> input_number; 
    for(int k=0; k<input_number; k++){
        std::cin >> rows; 
        matrix = (int**)malloc(sizeof(int*)*rows); 
        results = (int*)malloc(sizeof(int)*rows);
        for(int i=0; i<rows; i++){
            matrix[i] = (int*)malloc(sizeof(int)*i); 
        }
        
        for(int i=0; i<rows;i++){
            for(int j=0; j<=i; j++){
                std::cin >> matrix[i][j]; 
            }   
        }

        results[k]=best_path(rows,matrix);
        printf("%d\n",results[k]); 
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    algorithm();
    return 0;
}