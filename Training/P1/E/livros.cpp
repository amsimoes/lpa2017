#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>

int Knipsick(int proposals[2000][2], int* num_proposals, int num_researchers, int max_budget){

    //maximize number of papers
    //funding not used will be returned, so use as much as we can
    int matrix[num_researchers+2][max_budget+2];
    int researcher_proposals = 0;
    int spent_money = 0;
    int offset = 0;

    for(int j = 0; j<= max_budget; j++){
        for (int i = 0; i <= num_researchers; i++){
            matrix[i][j] = 0;
        }
    }
    for(int i = 1; i<=num_researchers; i++){
        researcher_proposals = num_proposals[i-1];
        for (int j = 1; j<=max_budget; j++){
            int value = 0;
            for(int k = 0; k<researcher_proposals; k++){
                //temos de ver o max para o researcher com diferente budget, no max so pode ter 1 projeto aprovado
                //temos de ver se compensa usar ou nao, mas so se passar de max budget
                printf("i = %d\n", i);
                printf("j= %d\n", j);
                printf("k = %d\n", k);
                printf("offset = %d\n", offset+k);
                printf("valor = %d\n", proposals[offset+k][0]);
                //matrix[i-1][j] -> nao usar a proposta
                if((proposals[offset+k][0] + spent_money) < j)
                    value = std::max(matrix[i-1][j],proposals[offset+k][1] + matrix[i-1][j-proposals[offset+k][0]]);
                if(value > matrix[i][j]){
                    matrix[i][j] = value;
                }   
            }
            
        }
        offset += researcher_proposals;
    }

    return matrix[num_researchers-1][max_budget-1];
}

void algorithm(){
    //readInput
    int num_researchers= 0;
    int max_budget = 0;
    int result = 0;
    std::cin >> num_researchers;
    std::cin >> max_budget;
    int num_proposals[num_researchers];
    int proposals[2000][2];

    for(int i = 0; i<num_researchers; i++){
      std::cin >> num_proposals[i];
    }
    int aux=0;
    for(int i = 0; i< num_researchers; i++){
        int j = num_proposals[i];  
        
        for(int k = 0; k < j; k++){
            std::cin >> proposals[aux+k][0];    //budget
            std::cin >> proposals[aux+k][1];    //number of papers

        }
        aux+=j;
    } 
    
    result=Knipsick(proposals, num_proposals, num_researchers, max_budget); 
   printf("%d\n", result);
    }



int main(){
    std::ios::sync_with_stdio(false);
    algorithm();
    return 0;
}