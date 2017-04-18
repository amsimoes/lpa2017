#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <time.h>

using namespace std;

int constants[45];
int xs_in_eq[45];
int constraints[1000][47];
int constraints_count;
int x_count;

void get_constraints(){ 
	char scan;
	int max_x;
	string number = "";
	int x_count_c = 0;
	int positive = 1;

	while((scan = getchar())) {
		//cout << "scan " << scan << endl;
		if(scan == 'x') {
			//printf("dentro do x das constraints o mano\n");
			//cout << "x_count " << x_count << endl;
			x_count_c++;
			string x_number = "";
			int x;
			scan = getchar();

			while(scan != '+' && scan != '-' && scan != '\n' && scan != '>' && scan != '<' && scan != '=') {
				x_number += scan;
				scan = getchar();
			}

			x = atoi(x_number.c_str());

			if(x > max_x)
				max_x = x;
			xs_in_eq[x_count_c-1] = x-1;

			int n;
			if(number == "")
				number = "1";
			if(positive == 0) {
				n = 0 - atoi(number.c_str());
			} else {
				n = atoi(number.c_str());
			}
			constraints[constraints_count][x-1] = n;

			if(scan == '+') {
				number = "";
				positive = 1;
			} else if(scan == '-') {
				number = "";
				positive = 0;
			}
		}

		if(scan == '+') {
			//printf("dentro do + das constraints o mano \n");
			number = "";
			positive = 1;
		} else if(scan == '=') {
			//printf("dentro do - das constraints o mano \n");
			string constraint_number = "";

			scan = getchar();
			while(scan != '\n') {
					constraint_number += scan;
					scan = getchar();
			}
			constraints[constraints_count][46] = atoi(constraint_number.c_str());
			constraints[constraints_count][45] = 0;
			constraint_number = "";
			
			number = "";
			x_count_c = 0;
			constraints_count++;
			positive = 1;
		} else if(scan == '<') {
			//printf("dentro do < das constraints o mano \n");
			if((scan = getchar()) == '=') {
				string constraint_number = "";

				scan = getchar();
				while(scan != '\n') {
					constraint_number += scan;
					scan = getchar();
				}
				constraints[constraints_count][46] = atoi(constraint_number.c_str());
				constraints[constraints_count][45] = -1;
				constraint_number = "";

				//reset
				number = "";
				x_count_c = 0;
				constraints_count++;
				positive = 1;
			}
		} else if(scan == '>') {
			//printf("dentro do > das constraints o mano \n");
			if((scan = getchar()) == '=') {
				string constraint_number = "";

				scan = getchar();
				while(scan != '\n') {
					constraint_number += scan;
					scan = getchar();
				}
				constraints[constraints_count][46] = atoi(constraint_number.c_str());
				constraints[constraints_count][45] = 1;
				constraint_number = "";
				
				//reset
				number = "";
				x_count_c = 0;
				constraints_count++;
				positive = 1;
			}
		} else if(scan == '-') {
			//printf("dentro do - de fora das constraints o mano \n");
			number = "";
			positive = 0;
		} else if(scan == '\n') {
			//printf("dentro do barra n das constraints o mano \n");
			number = "";
			x_count_c = 0;
			constraints_count++;
		} else if(scan == 'B') {
			//printf("dentro do B das constraints o mano \n");
			//binary
			char* line = (char*) malloc(50*sizeof(char));
			scanf("%s", line);
			if(strcmp(line,"INARY") == 0){
				return;
			}
		} else {
			number += scan;
		}
	}
	//return max_x;
}

int test_constraints(int array[45]) {
	int sum = 0;
	
	//printf("estou a testar constraints lul\n");
	for(int i = 0; i <= constraints_count-1; i++) { // passar por todas as constraints
		sum = 0; 
		for(int j = 0; j < 45; j++) { //passar por todos os x numa constraint
			sum += constraints[i][j] * array[j];
			//printf("sum = %d para a constraint %d, testar o x%d\n", sum, i,j);
		
			if(sum > constraints[i][47]) {
				//printf("constraint[%d][47] = %d\n", i,constraints[i][47]);
				//printf("valor do return %d \n", sum);
				//printf("valor do <= %d\n", constraints[i][47]);
				return 0;
			}
		}
	}

	//printf("valor final das constraints %d\n", sum);
	return 1;
}

int calc_expression(int array[45], int variable_change[45]) {
	int result = 0; 
	for(int i = 0; i < 45; i++) {
		result += (array[i] * constants[i] * variable_change[i]);
		// printf("result = %d,  array[%d] = %d, constants[%d] = %d, variable_change[%d] = %d\n", result, i, array[i], i, constants[i], i, variable_change[i]);
	}
	return result;
}

void parse_equation() {
	char scan;
	//int max_x;
	string number = "";
	x_count = 0;
	int positive = 1;

	while((scanf("%c",&scan))) {  
		//printf("sou o scan no inicio da parse_equation : %c\n", scan);
		if(scan == '+') {
			//printf("dentro do + da expressao o mano \n");
			number = "";
			positive = 1;
		} else if(scan == '-') {
			//printf("dentro do - da expressao o mano \n");
			number = "";
			positive = 0;
		} else if(scan == 'x') {
			//printf("dentro do x da expressao o mano \n");
			x_count++;
			string x_number = "";
			int x;

			scan = getchar();
			while(scan != '+' && scan != '-' && scan != '\n') {
				//printf("dentro do while dentro do x da expressao o mano \n");
				x_number += scan;
				scan = getchar();
			}

			x = atoi(x_number.c_str());
			xs_in_eq[x_count-1] = x-1;
			int n;

			if(number == "")
				number = "1";
			if(positive == 0) {
				n = 0 - atoi(number.c_str());
			} else {
				n = atoi(number.c_str());
			}

			constants[x-1] = n;
			
			if(scan == '+') {
				number = "";
				positive = 1;
			} else if(scan == '-') {
				number = "";
				positive = 0;
			}
		} else if(scan == 's') {
			char line_st[3];
			if(scanf("%s\n", line_st) == 1) {
				get_constraints();
			}
			return;
		} else {
			number += scan;
		}
	}
	//return max_x;
}

void algorithm(int max_or_min) {
	int xs[45];
	int variable_change[45];

	int bound = -99999;

	
	for(int i = 0; i < 45; i++) {
		variable_change[i] = 1;
		xs[i] = 0;
	}

	if(max_or_min == -1) {
		//ainda temos que garantir que na expressao inicial, todos os valores sao negativos, nos xs quando uma cena na expressão é >0 temos de fazer xi' = 1-xi
		for(int i =0; i < 45; i++) {
			if(xs_in_eq[i] > 0){
				variable_change[i] = -1; // mudanca de variavel, nao esquecer depois de verificar no fim do algoritmo. Estes so podem ser -1 ou 0.
			}
			xs_in_eq[i] *= -1;
		}
	}

	//printf("CONSTRAINTS COUNT = %d\n", constraints_count);
	int aux = constraints_count;
	for(int i=0; i < aux; i++) {
		if(constraints[i][45] == 1) {
			//printf("constraints[%d][0] = %d \n", i,constraints[i][0]);
			for(int j=0; j < 47; j++) {
				constraints[i][j] *= -1;
				//cout << "if >= " << i << " " << j << " =" << constraints[i][j] << endl;
			}
		} else if(constraints[i][45] == 0) {
			constraints[i][45] = -1;
			for(int j=0; j < 47; j++) {
				if (j != 45) {
					constraints[constraints_count][j] = constraints[i][j]*(-1);
				}
				//cout << "nova constraint do =, posicao no array: " << constraints_count-1 << " " << j << " =" << constraints[constraints_count-1][j] << endl;
			}
			constraints[constraints_count][45] = -1;
			constraints_count++;	
		}
	}

	//printf("AFTER - CONSTRAINTS COUNT = %d\n", constraints_count);

	/*for(int i = 0; i < constraints_count; i++) {
		for(int j = 0; j < 47; j++) {
			printf("constraints[%d][%d] = %d\n", i, j, constraints[i][j]);
		}
	}

	for(int k = 0; k < 45; k++) {
		printf("variable_change[%d] = %d\n", k, variable_change[k]);
	}*/


	for(int i = 0; i < 45; i++) {
		//meter todas as combinacoes de 0 e 1 possiveis nas variaveis.
		//comecar com x1 a 0, ver se passa nos 3 testes. se nao, meter o x1 a 1 e ver se passa nos testes. se passar fazer x1 1 e x2 0, testar, etc etc
		xs[i] = 0;
		if(test_constraints(xs) == 0) {// se xi = 0 nao passar nas constraints
			xs[i] = 1;
			if(test_constraints(xs) == 0) { // se xi = 1 nao passar nas constraints
				//printf("entrei aqui blyat 1\n");
				//printf("xs[%d]\n", i);
				printf("INFEASIBLE\n");
				return;
			} else {// se xi = 1 passar nas constraints
				int res = calc_expression(xs, variable_change); // calcular resultado do array atual na expressao inicial
				if(res > bound) { // se o resultado for melhor que o melhor possivel ate agora
					bound = res;
					continue; // continuar com o xi a 1
				} else {
					// se o resultado de xi = 1 for pior que o atual, e com xi = 0 nao passar nas constraints é impossível fazer melhor resultado que isto.
					if(bound != -99999999)
						printf("%d\n", bound);
					else {
						//printf("entrei aqui blyat 2\n");
						printf("INFEASIBLE\n");
					}
					return;
				}
			}
		} else { // se xi = 0 passar nas constraints
			int res = calc_expression(xs, variable_change); // calcular resultado da expressao com xi = 0; 
			if(res > bound) {	// se xi = 0 der melhor resultado que o atual
				bound = res; 
				xs[i] = 1;
				continue;	//continua com xi = 1;
			} else {	// se nao der melhor resultado que o atual 
				xs[i] = 1;

				if(test_constraints(xs) == 0) { // se xi =1 nao passar nas constraints
					printf("%d\n", bound);
					return;
				} else {	// se xi = 1 passar nas constraints 
					int res = calc_expression(xs, variable_change);
					if(res > bound) {	//se der melhor resultado que o atual
						bound = res; 
						continue;
					} else {
						printf("%d\n", bound);
						return;
					}
				}
			}
		}
	}

	if(bound != -99999999)
		printf("%d\n", bound);
	else
		printf("INFEASIBLE\n");
}


int main() {
	//clock_t begin = clock();
	ios::sync_with_stdio(false);
	char* line = (char*)malloc(50*sizeof(char));

	constraints_count = 0;
	while(scanf("%s\n",line) >= 1) {
		if(!strcmp("maximize",line)){
			//printf("dentro do maximize na main o mano \n");
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<47; j++) {
					constraints[i][j] = 0;
				}
			}
			constraints_count = 0;
			//cout << "maximize" << endl;
			//int max_x = parse_equation();
			parse_equation();
			algorithm(1);
			//printf("INFEASIBLE\n");
		} else if(!strcmp("minimize",line)) {
			//printf("dentro do minimize na main o mano \n");
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<47; j++) {
					constraints[i][j] = 0;
				}
			}
			constraints_count = 0;
			//cout << "minimize" << endl;
			////int max_x = parse_equation();
			parse_equation();
			algorithm(-1);
			//printf("INFEASIBLE\n");
		}

		free(line);
		line = (char*)malloc(50*sizeof(char));
	}

	//clock_t end = clock();
	//double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

	//printf("\nexecution time = %f\n", time_spent);

	return 0;
}