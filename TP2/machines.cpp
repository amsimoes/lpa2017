#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>

std::vector<std::pair<double,int> > machines;
double machines_prob[400];
int machines_cost[400];
int budget;
int *values;


int readInput(){
    int sections; 
    std::cin >> sections; 
    //std::cout << "Number of sections: " << sections << "\n"; 
    for(int i=0; i<sections; i++){
        std::cin >> machines_prob[i] >> machines_cost[i]; 
        //std::cout << "Probability: " << machines_prob[i] << " " << "Cost: " << machines_cost[i] << "\n";
    }
    std::cin >> budget;
    //std::cout << "Budget: " << budget << "\n";
    return sections;
}

void knapsack(int sections, int budget){  
    double machines_array[sections+1][budget+1];
    int machines_solution[sections];
    double failure_prob;
    double prob;
    for(int i=0; i<=budget; i++){
        machines_array[0][i] = 1;      
    }  
    for(int i=1; i<=sections; i++){ 
        for(int j=1; j<=budget; j++){ 
           machines_array[i][j] = 0;
           int max = j/machines_cost[i-1];  
           failure_prob = 1;
           for(int k=1; k<=max; k++){
              // (1-P)^n
              failure_prob *= (1-machines_prob[i-1]);
              // 1-(1-P)^n * Valor Anterior
              prob = (1-failure_prob)*(machines_array[i-1][j-(k*machines_cost[i-1])]); 
              if(prob > machines_array[i][j]){
                  machines_array[i][j] = prob;
              }
           }   
           //printf("i:%d, j:%d, %lf\n",i,j,machines_array[i][j]);
        }
    }
    std::cout.precision(12);
    std::cout << std::fixed << machines_array[sections][budget] << std::endl;
    double max_prob;
    max_prob = machines_array[sections][budget]; 
    int max = budget; 
    for(int i=sections; i>=0; i--){
        for(int j=0; j<=max; j++){ 
            double temp = machines_array[i][j];
            printf("machines_array:%.12f max:%.12f\n",machines_array[i][j], max_prob);
            if(fabs(temp - max_prob) < std::numeric_limits<double>::epsilon()){
                printf("inside if\n");
                printf("%d\n",machines_cost[i-1]);
                printf("%d\n",j-machines_cost[i-1]);
                printf("%.12f\n",machines_array[i-1][j-machines_cost[i-1]]);
                max_prob = machines_array[i-1][j-machines_cost[i-1]]; 
                printf("max_prob: %.12f\n",max_prob);
                max = std::abs(j);  
                printf("max: %d\n",max);
                printf("j:%d, machines_cost:%d\n", j, machines_cost[i-1]);
                machines_solution[i] = j/machines_cost[i-1]; 
                for(int k=sections; k>=0; k--){
                    machines_solution[k] /= machines_solution[i];
                }
                printf("j: %d, machines_cost[i]:%d, machines_solution[i]:%d\n",j,machines_cost[i],machines_solution[i]);
                fflush(stdout); 
                break;
            } 
        } 
        printf("break\n");
    } 
    for(int i=0; i<sections; i++){
        std::cout << machines_solution[i] << std::endl;
    } 
}

int main(void){
    std::ios::sync_with_stdio(false);
    int sections;
    sections = readInput();
    knapsack(sections,budget);
    std::vector<std::pair<int, double> > machines_prob(sections, std::make_pair(0,0));
    return 0;
}
