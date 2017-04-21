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
int x_best[45];
int best;
int constraints_count;

int l_bound;
int best_min;
int best_max;

int x_count;

int xarray[45];
int last_x;
int last_x_constraint = 0;

int max_or_min;

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

void print_used_xs(int xarray[45]) {
	for(int i = 0; i < 45; i++) {
		printf("xarray[%d] = %d | constants[%d] = %d\n", i, xarray[i], i, constants[i]);
	}
}

int test_constraints(int x_index) {
	int sum = 0;
	int flag = 0;

	//printf("\n## TESTING CONSTRAINTS ##\n\n");
	//printf("xarray[%d] = %d\n", x_index, xarray[x_index]);
	//print_used_xs(xarray);

	for(int i = 0; i < constraints_count; i++) { // passar por todas as constraints
		sum = 0; 
		for(int j = 0; j < last_x_constraint; j++) { //passar por todos os x numa constraint
			//printf("xarray[%d] = %d\n", j, xarray[j]);
			if(xarray[j] == 1) {
				//printf("xarray[%d] = %d | constants[%d] = %d | constraints[%d][%d] = %d\n", j, xarray[j], j, constants[j], i, j, constraints[i][j]);
				sum += constraints[i][j] * xarray[j];

				//printf("sum = %d | constraints[%d][46] = %d\n", sum, i, constraints[i][46]);

				if(sum > constraints[i][46]) {
					flag = 0;
				} else {
					flag = 1;
				}
			}
		}
		if(!flag)
			return 0;
	}

	return flag;
}

int calc_expression(int array[45], int variable_change[45]) {
	int result = 0; 
	printf("--- CALC EXPRESSION ---\n");
	for(int i = 0; i < last_x; i++) {
		//if(array[i] != 0) { -> OTIMIZADO
		result += (array[i] * constants[i]);
		printf("array[%d] = %d | constants[%d] = %d | variable_change[%d] = %d | Result = %d\n", i, array[i], i, constants[i], i, variable_change[i], result);
	}
	//printf("\n--- CALC EXPRESSION ---\n");
	return result;
}

int calc_expression2(int array[45], int variable_change[45]) {
	int result = 0; 
	for(int i = 0; i < 45; i++) {
		result += ((array[i] + variable_change[i]) * constants[i]);
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

void print_expression() {
	for(int i = 0; i < 47; i++) {
		printf("constants[%d] = %d\n", i, constants[i]);
	}
}

void print_xbest() {
	for(int i = 0; i < 45; i++) {
		printf("xbest[%d] = %d\n", i, x_best[i]);
	}
}

void used_vars(int xarray[45]) {
	for(int k = 0; k < 45; k++) {
		if(xarray[45] == 1)
			printf("(%d, %d) ", k, constants[k]);
	}
	printf("\n");
}

void print_variable_change(int var_change[45]) {
	for(int i = 0; i<45; i++)
		printf("variable_change[%d] = %d\n", i, var_change[i]);
}

void last_constraint() {
	int last = 0;
	for(int i = 0; i < constraints_count; i++) {
		for(int j = 45; j >= last_x_constraint; j--) {
			if(constraints[i][j] != 0) {
				last = j;
				break;
			}
		}
		if(last > last_x_constraint)
			last_x_constraint = last;
	}
}

void last_var() {
	for(int i = 44; i >= 0; i--) {
		if(constants[i] != 0) {
			last_x = i;
			return;
		}
	}
}

void branch_and_blyat(int variable_change[45], int x_index) {
	int intermediate = 0;

	//meter todas as combinacoes de 0 e 1 possiveis nas variaveis.
	//comecar com x1 a 0, ver se passa nos 3 testes. se nao, meter o x1 a 1 e ver se passa nos testes. se passar fazer x1 1 e x2 0, testar, etc etc
	
	xarray[x_index] = 1;

	//printf("BB | Testing X_INDEX = %d | xarray[%d] = %d\n", x_index, x_index, xarray[x_index]);

	if(test_constraints(x_index) == 1) { // se passar nas constraints com xindex = 1
		intermediate = calc_expression(xarray, variable_change);
		//printf("\nPASSED CONSTRAINTS | X_INDEX = %d | NEW Intermediate = %d\n", x_index, intermediate);

		if(max_or_min == 1) { // maximizar

			if(intermediate > l_bound) {
				//printf("\nMaximize | Intermediate = %d > l_bound = %d\n", intermediate, l_bound);
				//memcpy(x_best, xarray, sizeof(x_best));

				l_bound = intermediate;
				//printf("Maximize | LOWER BOUND = %d\n", l_bound);
				branch_and_blyat(variable_change, x_index+1);
			}
		} else if(max_or_min == -1) { // minimizar

			if(intermediate < l_bound) {
				//printf("\nMinimize | Intermediate = %d < l_bound = %d\n", intermediate, l_bound);
				//memcpy(x_best, xarray, sizeof(x_best));

				l_bound = intermediate;
				//printf("Minimize | LOWER BOUND = %d\n", l_bound);
				branch_and_blyat(variable_change, x_index+1);				
			}
		}

	} else {	// N PASSA NAS CONSTRAINTS
		if(x_index <= last_x) {
			//printf("x_index = %d | Nao passa nas constraints -> A chamar branch_and_blyat...\n", x_index);
			xarray[x_index] = 0;
			branch_and_blyat(variable_change, x_index+1);
		}
	}

	if(x_index <= last_x)
		branch_and_blyat(variable_change, x_index+1);
	return;
}

void algorithm() {
	int variable_change[45];

	//print_expression();

	for(int i = 0; i < 45; i++) {
		variable_change[i] = 0;
		xarray[i] = 0;
	}

	/*if(max_or_min == -1) {
		//ainda temos que garantir que na expressao inicial, todos os valores sao negativos, nos xs quando uma cena na expressão é >0 temos de fazer xi' = 1-xi
		for(int i = 0; i < 45; i++) {
			if(constants[i] < 0){
				variable_change[i] = -1; // mudanca de variavel, nao esquecer depois de verificar no fim do algoritmo. Estes so podem ser -1 ou 0.
				constants[i] *= -1;
			}
		}
	}*/

	int aux = constraints_count;
	for(int i=0; i < aux; i++) {
		if(constraints[i][45] == 1) {
			for(int j=0; j < 47; j++) {
				constraints[i][j] *= -1;
			}
		} else if(constraints[i][45] == 0) {
			constraints[i][45] = -1;
			for(int j=0; j < 47; j++) {
				if (j != 45) {
					constraints[constraints_count][j] = constraints[i][j]*(-1);
				}
			}
			constraints[constraints_count][45] = -1;
			constraints_count++;	
		}
	}

	print_expression();
	branch_and_blyat(variable_change, 0);

	if(l_bound == -99999 || l_bound == 99999) {
		printf("INFEASIBLE\n");
	} else {
		//print_xbest();
		//print_variable_change(variable_change);
		//int res = calc_expression2(x_best, variable_change);
		printf("%d\n", l_bound);
	}
}


int main() {
	clock_t begin = clock();
	ios::sync_with_stdio(false);
	char* line = (char*)malloc(50*sizeof(char));

	constraints_count = 0;
	while(scanf("%s\n",line) >= 1) {
		if(!strcmp("maximize",line)){
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<47; j++) {
					constraints[i][j] = 0;
				}
			}
			constraints_count = 0;
			parse_equation();
			last_var();
			last_constraint();
			//printf("last x = %d\n", last_x);
			max_or_min = 1;
			l_bound = -99999;
			algorithm();
		} else if(!strcmp("minimize",line)) {
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<47; j++) {
					constraints[i][j] = 0;
				}
			}
			constraints_count = 0;
			parse_equation();
			last_var();
			last_constraint();
			//printf("last x = %d\n", last_x);
			max_or_min = -1;
			l_bound = 99999;
			algorithm();
		}

		free(line);
		line = (char*)malloc(50*sizeof(char));
	}

	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

	printf("execution time = %f\n", time_spent);

	return 0;
}