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
    for(int i=0; i<sections; i++){
        std::cin >> machines_prob[i] >> machines_cost[i];
    }
    std::cin >> budget;
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
    for(int i=0; i<num; i++) {
        prob_final *= (1-prob);
    }
    return prob_final;
}

// min cost está sempre a zero
// começa na ultima section
// i+1 --> max_budget
void backtrack(int* solution, int section, int max_budget, double matrix_prob[][1001], int min_cost) {
    printf("min cost = %d\n", min_cost);
    int counter = 0;    // Counter = N de maquinas da seccao

    if (section != 1) {

        // b = budget que sobra... b > 0... a cada iteracao tira o custo de uma maquina
        // este ciclo garante todas as possibilidades com o mesmo budget, q é o minimo
        for (int b = max_budget - machines_cost[section-1]; b > min_cost; b -= machines_cost[section-1]) {
            
            // como o counter vai aumentando, garante-se a ordem lexicografica (na direita aumenta)
            counter++;
            // acedemos a section pq matrix_prob começa a 1 (machines_cost e _prob começam a 0)
            double prob_atual = matrix_prob[section][max_budget];   // prob maxima nessa seccao, podia estar antes do ciclo

            // comparar doubles...
            // matrix_prob[section-1][b] para se calcular a probabilidade com counter maquinas
            // a matrix[section-1][b] até section-1 com budget b é a solucao otima até lá (section-1, b)
            double abs = fabs(prob_atual-(matrix_prob[section-1][b]*(1-pow_prob(counter, machines_prob[section-1]))));

            // se a probabilidade com counter maquinas for igual a prob_maxima, chamar backtracking para section-1
            if (abs < 0.0000000000000002220446049) {
                solution[section] = counter;
                // chama para a linha anterior, chama-se com o menor counter logo a direita é chamada primeiro
                backtrack(solution, section-1, b, matrix_prob, min_costs[section]);
            }
        } 
    }

    // 1a seccao, budget que ainda se tem divide-se pelo custo das maquinas na 1a seccao
    if (section == 1) {
        solution[section] = max_budget/machines_cost[section-1];

        // imprimir uma solução
        for(int i=1; i<sections; i++) {
            std::cout << solution[i] << " ";
        }
        std::cout << solution[sections] << std::endl;
    }

    return;
}

void knapsack() {
    double machines_array[401][1001];   // Matrix seccoes x budgets
    double failure_prob;  
    double prob;  
    int solutions[401];   

    for(int i=0; i <= budget; i++){
        machines_array[0][i] = 1;   // primeira linha a 1 pq é elemento neutro p/ multiplicar pq tamos a começar a 1
    }

    for (int i=1; i <= sections; i++) { 
        for (int j=1; j <= budget; j++) {
           machines_array[i][j] = 0;  // Inicializar
           int max = j / machines_cost[i-1];   // max: n maximo de maquinas que podes comprar nesta seccao (machines_cost)
           failure_prob = 1;  // iniciar a 1 para ser neutro dps multiplica-se
           double prob_atual = machines_prob[i-1];  // prob da seccao
           int cost_atual = machines_cost[i-1]; // custo das maquinas da seccao atual (todas as maquinas custam o mesmo)

           // K = nº de maquinas
           // K começa a 1 porque tem de se comprar pelo menos uma máquina
           for(int k=1; k<=max; k++) {
              // (1-P)^n
              failure_prob *= (1-prob_atual);

              // 1-(1-P)^n * Valor Anterior
              prob = (1-failure_prob) * (machines_array[i-1][j-(k*cost_atual)]);

              // Vai se chegar a um ponto em que prob é maximo e constante
              // Se com mais máquinas (k), prob for maior a matriz é atualizada com o novo valor da prob de sucesso (da seccao n falhar)
              if (prob > machines_array[i][j]) {
                  machines_array[i][j] = prob;
              }
           }
        }
    }

    // apos isto a matriz ja esta preenchida com todas as probabilidades

    // Imprimir a melhor probabilidade (ultima linha, ultima coluna da matriz)
    std::cout.precision(12);
    std::cout << std::fixed << machines_array[sections][budget] << std::endl;

    // ciclo na ultima linha para procurar a probabilidade maxima com menor budget
    for(int i=budget; i>0; i--) {
        if(machines_array[sections][i] < machines_array[sections][budget]) { // encontra a primeira prob menor que a maxima
            backtrack(solutions, sections, i+1, machines_array, min_costs[sections]); // passa o i+1, primeiro com a prob maxima
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
