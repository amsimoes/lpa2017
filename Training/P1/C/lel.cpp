#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

long int algorithm(long int width, long int height, long int wolves, long int **wolves_coords){
    long int **matrix;
    matrix = (long int**) malloc(sizeof(long int*)*(width+2));
    for(int i=0; i<=width; i++){
        matrix[i] = (long int*) malloc(sizeof(long int)*(height+2));
    }
    for(long int i =0; i<=width; i++){
        matrix[i][0] = 1; 
    }
    for(long int i=0; i<=height; i++){
        matrix[0][i] = 1; 
    }
    for(long int i=0; i<=width; i++){
        for(long int j=0; j<=height; j++){
            if(wolves_coords[i][j]==1){
                matrix[i][j] = 0;
            } 
            else{
                if(i==0 && j==0){
                    matrix[i][j] = 1;
                }
                else if(i==0){
                    matrix[i][j] = matrix[i][j-1];
                }
                else if(j==0){
                    matrix[i][j] = matrix[i-1][j];
                }
                else{
                    matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
                }
            } 
        }
    }
    return matrix[width][height];
}

int main(){
    long int width,height;
    long int wolves;
    long int **wolves_coords; 
    long int w,h;
    long int result;
    std::ios::sync_with_stdio(false);
    std::cin >> width >> height;
    while(height != 0 && width != 0){
        std::cin >> wolves; 
        wolves_coords = (long int**) malloc(sizeof(long int*)*width);
        for(long int i=0; i<=width; i++){
            wolves_coords[i] = (long int*) malloc(sizeof(long int)*height);
        }

        for(long int i=0;i<wolves;i++){
            std::cin >> w >> h;
            wolves_coords[w][h] = 1;
        } 
        result = algorithm(width,height,wolves,wolves_coords);
        if(result == 0){
            std::cout << "There is no path.\n";
        }
        else if(result == 1){
            std::cout << "There is one path from Little Red Riding Hood's house to her grandmother's house.\n";
        }
        else{
            std::cout << "There are " << result << " paths from Little Red Riding Hood's house to her grandmother's house.\n";
        }
        std::cin >> width >> height; 
    }
    return 0;
}
