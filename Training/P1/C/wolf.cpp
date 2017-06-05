#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

int algorithm(int width, int height, int wolves, int **wolves_coords){
    int **matrix;
    matrix = (int**) malloc(sizeof(int*)*(width+2));
    for(int i=0; i<=width; i++){
        matrix[i] = (int*) malloc(sizeof(int)*(height+2));
    }
    for(int i =0; i<=width; i++){
        matrix[i][0] = 1; 
    }
    for(int i=0; i<=height; i++){
        matrix[0][i] = 1; 
    }
    for(int i=0; i<=width; i++){
        for(int j=0; j<=height; j++){
            if(wolves_coords[i-1][j-1]==1){
                matrix[i][j] = 0;
            } 
            else{
                if(i==0 && j==0){
                    matrix[i][j] = 0;
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
    int width,height;
    int wolves;
    int **wolves_coords; 
    int w,h;
    int result;
    std::ios::sync_with_stdio(false);
    std::cin >> width >> height;
    while(height != 0 && width != 0){
        std::cin >> wolves; 
        wolves_coords = (int**) malloc(sizeof(int*)*width);
        for(int i=0; i<=width; i++){
            wolves_coords[i] = (int*) malloc(sizeof(int)*height);
        }

        for(int i=0;i<wolves;i++){
            std::cin >> w >> h;
            wolves_coords[w][h] = 1;
        } 
        printf("width:%d height:%d\n",width,height);
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
