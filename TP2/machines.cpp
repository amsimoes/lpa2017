#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>

double machines_prob[401];
int machines_cost[401];
int min_costs[401];
int sections;
int budget;
int *values;

void readInput(){ 
    std::cin >> sections; 
    //std::cout << "Number of sections: " << sections << "\n"; 
    for(int i=0; i<sections; i++){
        std::cin >> machines_prob[i] >> machines_cost[i]; 
        //std::cout << "Probability: " << machines_prob[i] << " " << "Cost: " << machines_cost[i] << "\n";
    }
    std::cin >> budget;
    //std::cout << "Budget: " << budget << "\n";
}

void print_matrix(double matrix_prob[][1001]) {
    for(int i=0; i<=sections; i++) {
        for(int j=0; j<=budget; j++) {
            printf("%.12f ", matrix_prob[i][j]);
        }
        printf("\n");
    }
}

void calc_min_costs(){
  int sum=0;
  for (int i = 0; i<sections; i++){
    sum+=machines_cost[i];
    min_costs[i] = sum;
  }
}

double pow_prob(int num, double prob) {
    double prob_final = 1.0;
    //printf("prob = %.12f\n", prob);
    for(int i=0; i<num; i++) {
        prob_final *= (1-prob);
    }
    //printf("prob_final = %f\n", prob_final);
    return prob_final;
}

void backtrack(int* solution, int section, int max_budget, double matrix_prob[][1001], int min_cost) {
    int counter = 0;
    
    //print_matrix(matrix_prob);
    if(section!=1) {
        for(int b=max_budget-machines_cost[section-1]; b>min_cost; b-=machines_cost[section-1]) {
            counter++;
            //printf("b = %d\n", b);
            //printf("section = %d | max_budget = %d\n", section, max_budget);
            double prob_atual = matrix_prob[section][max_budget];
            //printf("prob_atual = %.12f\n", prob_atual);
            double abs = fabs(prob_atual-(matrix_prob[section-1][b]*(1-pow_prob(counter, machines_prob[section-1]))));
            if(abs < 0.0000000000000002220446049) {
                solution[section] = counter;
                backtrack(solution, section-1, b, matrix_prob, min_costs[section]);
            }    
        }    
    }
    
    if(section==1) {
        solution[section] = max_budget/machines_cost[section-1];
        for(int i=1; i<sections; i++) {
            std::cout << solution[i] << " ";
        }
        std::cout << solution[sections] << std::endl;
    }
    return;
}

void knapsack(){  
    double machines_array[401][1001];
    double failure_prob;
    double prob;
    int solutions[401];

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

    for(int i=budget; i>0; i--){
        if(machines_array[sections][i] < machines_array[sections][budget]){
            backtrack(solutions, sections, i+1, machines_array, min_costs[sections]);
            break;
        }
    }
}

int main(void){
    std::ios::sync_with_stdio(false);
    readInput();
    knapsack();
    return 0;
}