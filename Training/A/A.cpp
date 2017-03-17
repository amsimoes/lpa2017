#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

void init_matrix(int** &matrix, int rows) {
    matrix = (int**) malloc(sizeof(int*) * rows);
    for(int i=0; i<=rows; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * i);
    }
}

void input(int** &matrix, int *input_number, int *rows) {
    std::cin >> *input_number;
    std::cin >> *rows;
    init_matrix(matrix, *rows);

    for(int k=0; k<*input_number; k++) {
        for(int i=0; i<=*rows; i++) {
            for(int j=0; j<i; j++) {
                std::cin >> matrix[i][j];
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
}

void print_matrix(int** matrix, int rows) {
    for(int i=0; i<=rows; i++) {
        for(int j=0; j<i; j++) {
            std::cin >> matrix[i][j];
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int best_path(int rows, int **matrix){
    int **new_matrix, max;
    init_matrix(new_matrix, rows);
    new_matrix[0][0] = matrix[0][0];
    
    for(int i=1; i<=rows; i++){
        for(int j=1; j<=i; j++){
            max = std::max(new_matrix[i-1][j-1],new_matrix[i-1][j]) + matrix[i][j]; 
            new_matrix[i][j] = max;
        } 
    }
    print_matrix(new_matrix, rows);
    max = 0;
    for(int i=0;i<=rows;i++){
        if(max < new_matrix[rows-1][i])
            max = new_matrix[rows-1][i];
    }
    return max;
}

void algorithm(){
    int input_number,rows;
    int **matrix;
    int *results;

    input(matrix, &input_number, &rows);

    results = (int*)malloc(sizeof(int)*rows);

    for(int k=0; k<input_number; k++){
        for(int i=0; i<rows;i++){
            for(int j=0; j<i; j++){
                std::cin >> matrix[i][j];
            }
        }
    }
    
    for(int i=0; i<input_number; i++){
        results[i] = best_path(rows, matrix);
        printf("%d\n",results[i]);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    algorithm();
    return 0;
}
