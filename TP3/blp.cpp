#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <time.h>
#include <limits.h>

using namespace std;

int constants[45];
int xs_in_eq[45];
int constraints[1000][48];
int constraints_sum_pos[1000][45];
int constraints_sum_neg[1000][45];
bool xs_existent[45];

int best;
int constraints_count;
int x_count;
int constants_sum_pos[45];
int constants_sum_neg[45];
int infeasible;
bool solution;
int max_x;
int current_sum;
int x_test[45];

void get_constraints(){ 
	char scan;
	string number = "";
	int x_count_c = 0;
	int positive = 1;

	while((scan = getchar())) {
		if(scan == 'x') {
			x_count_c++;
			string x_number = "";
			int x;
			scan = getchar();

			while(scan != '+' && scan != '-' && scan != '\n' && scan != '>' && scan != '<' && scan != '=') {
				x_number += scan;
				scan = getchar();
			}

			x = atoi(x_number.c_str());
			
			xs_existent[x-1] = true;

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
			number = "";
			positive = 1;
		} else if(scan == '=') {
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
			number = "";
			positive = 0;
		} else if(scan == '\n') {
			number = "";
			x_count_c = 0;
			constraints_count++;
		} else if(scan == 'B') {
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
}

void parse_equation() {
	char scan;

	string number = "";
	x_count = 0;
	int positive = 1;

	while((scanf("%c",&scan))) {  
		if(scan == '+') {
			number = "";
			positive = 1;
		} else if(scan == '-') {
			number = "";
			positive = 0;
		} else if(scan == 'x') {
			x_count++;
			string x_number = "";
			int x;

			scan = getchar();
			while(scan != '+' && scan != '-' && scan != '\n') {
				x_number += scan;
				scan = getchar();
			}

			x = atoi(x_number.c_str());
			
			xs_existent[x-1] = true;
			
			if(x > max_x)
				max_x = x;
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
}

/*
	45 -> sinal: -1 <= | 0 == | 1 >=
	46 -> valor que igualas
	47 -> guardar soma
*/
// BOUNDING TBM
int test_constraints(int x_index) { // -1 -> impossi­vel || 0 -> certo || 1 -> pode continuar
	int flag = 0;
	for (int i=0; i<constraints_count; i++) {
		int aux = constraints[i][47];

		if (constraints[i][45] == 1 && aux < constraints[i][46]) {	// >=
			flag = 1;

			// sendo aux menor, vai somar todos os positivos que ainda faltam
			// e se mesmo assim o resultado for menor que o valor a igualar, é impossivel satisfazer a constraint
			aux += constraints_sum_pos[i][x_index+1];
			if(aux < constraints[i][46])	
				return -1;
		} else if(constraints[i][45] == 0) {	// = 
			if(aux > constraints[i][46]) {
				flag = 1;

				aux += constraints_sum_neg[i][x_index+1];
				if(aux > constraints[i][46])
					return -1;
			} else if(aux < constraints[i][46]) {
				flag = 1;
				aux += constraints_sum_pos[i][x_index+1];
				if(aux < constraints[i][46])
					return -1;
			}
		} else if(constraints[i][45] == -1 && aux > constraints[i][46]) {	// <=
			flag = 1;
			aux += constraints_sum_neg[i][x_index+1];
			if(aux > constraints[i][46])
				return -1;
		}
	}
	if(flag)
		return 1;
	return 0;
}

int find_next(int index){
	for(int i=index; i<45; i++){
		if(xs_existent[i])
			return i;
	}
	return -1;
}

void branch_and_bound(int x_index, int max_or_min, int current_sum) {

	// BOUNDING
	// constants_sum_pos acumula a soma até ao fim da primeira posicao para a final, na primeira tem a soma de todos os positivos da 2a pos ate a ultima
	// neg acumula com os negativos
	if (max_or_min == 1) { // Maximizar
		// UPPER BOUND
		// Se a soma atual + o acumulado ate ao fim das q faltam testar for menor que best, pode parar pq é impossivel
		if(current_sum + constants_sum_pos[x_index+1] < best)	
			return;
	} else if (max_or_min == -1) { // Minimizar
		// LOWER BOUND
		if(current_sum + constants_sum_neg[x_index+1] > best)
			return;
	}

	int test = test_constraints(x_index);

	if (test == 0) { // Se passar nas constraints, é uma solucao mas pode ainda haver melhor
		solution = true;	// Há pelo menos uma solucao

		if (max_or_min == 1) { // Maximizar
			if(current_sum > best)	// Atualizar o melhor valor
				best = current_sum;

			int next = find_next(x_index+1);	// proximo x existente
			if (next == -1)	//  se nao existir, para
				return;

			// BRANCHING

			x_test[next] = 0;
			branch_and_bound(next, max_or_min, current_sum); // Call for Branch and Bound with x_test[next] = 0

			// como queremos agora a testar o 1, somamos nas constraints o valor do x q vamos testar
			for(int i = 0; i<constraints_count; i++){
				constraints[i][47] += constraints[i][next];
			}
			
			x_test[next] = 1;
			// chamar com current_sum + constants[next], pq x está a 1
			branch_and_bound(next, max_or_min, current_sum + constants[next]); // Call for Branch and Bound with x_test[next] = 1
			
			// tem de ser por a 0 para quando volta a subir na recursao
			for(int i = 0; i<constraints_count; i++){
				constraints[i][47] -= constraints[i][next];
			}
			x_test[next] = 0;
			
			return;
		} else if(max_or_min == -1) { // Minimizar
			//printf("current_sum: %d, x_test[%d]: %d\n", current_sum, x_index, x_test[x_index]);
			if(current_sum < best)	// unica coisa a mudar do maximize
				best = current_sum;

			int next = find_next(x_index+1);
			if(next == -1)
				return;

			x_test[next] = 0;
			branch_and_bound(next, max_or_min, current_sum); // Call for Branch and Bound with x_test[next] = 0
			
			for(int i = 0; i<constraints_count; i++){
				constraints[i][47]+=constraints[i][next];
			}
			x_test[next] = 1;
			branch_and_bound(next, max_or_min, current_sum + constants[next]); // Call for Branch and Bound with x_test[next] = 1
			
			for(int i = 0; i<constraints_count; i++){
				constraints[i][47]-=constraints[i][next];
			}
			x_test[next] = 0;

			return;
		}

		return;

	} else if(test == 1) { // Ainda n ha solucao mas é possivel haver uma
		if (x_index == max_x-1)	// se for o ultimo, acaba n vale a pena testar mais
			return;
		
		int next = find_next(x_index+1);
		if(next == -1)	// redundante com o primeiro if, testar se ha mais algum
			return;
		
		x_test[next] = 0;
		branch_and_bound(next, max_or_min, current_sum); // Call for Branch and Bound with x_test[next] = 0

		x_test[next] = 1;
		for(int i = 0; i<constraints_count; i++){
			constraints[i][47]+=constraints[i][next];
		}
		branch_and_bound(next, max_or_min, current_sum + constants[next]); // Call for Branch and Bound with x_test[next] = 1
		

		for(int i = 0; i<constraints_count; i++){
			constraints[i][47]-=constraints[i][next];
		}
		x_test[next] = 0;

		return;
	} else if (test == -1) {	// Impossivel passar
		return;
	}
}

void algorithm(int max_or_min) {
	for (int i=0; i < 1; i++) {
		for (int j=0; j < 48; j++) {
			printf("constraints[%d][%d] = %d\n", i, j, constraints[i][j]);
		}
	}

	if (max_or_min == 1) {
		best = INT_MIN;
	} else {
		best = INT_MAX;
	}

	solution = false;
	int current_sum = 0;

	x_test[0] = 0;	
	branch_and_bound(0, max_or_min, current_sum); // Call for Branch and Bound with x_test[0] = 0
	
	x_test[0] = 1; // Change x_test[0] to call Branch and Bound
	for(int i = 0; i<constraints_count; i++){
		constraints[i][47] += constraints[i][0];
	}
	
	branch_and_bound(0, max_or_min, constants[0]); // Call for Branch and Bound with x_test[0] = 1
	
	if(!solution)
		printf("INFEASIBLE\n");
	else
		printf("%d\n",best);
}

int main() {
	//clock_t begin = clock();
	ios::sync_with_stdio(false);
	char* line = (char*)malloc(50*sizeof(char));
	constraints_count = 0;
	for(int i=0; i<45; i++){
		xs_existent[i] = false;
	}

	while(scanf("%s\n",line) >= 1) {

		if(!strcmp("maximize",line)) {
			for(int i=0; i<constraints_count; i++) {	// INICIALIZAR
				for(int j=0; j<48; j++) {
					constraints[i][j] = 0;
					constants[j] = 0;
					x_test[j] = 0;
					xs_existent[j] = false;
				}
			}

			constraints_count = 0;
			parse_equation();

			for(int i=0; i<constraints_count; i++){
				if(constraints[i][max_x-1] > 0)
					constraints_sum_pos[i][max_x-1] = constraints[i][max_x-1];
				else if(constraints[i][max_x-1] < 0)
					constraints_sum_neg[i][max_x-1] = constraints[i][max_x-1];
				else{
					constraints_sum_pos[i][max_x-1] = 0;
					constraints_sum_neg[i][max_x-1] = 0;
				}
				for(int j=43; j>=0; j--) {
					if(constraints[i][j] > 0) {
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1] + constraints[i][j];
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1];
					} else if(constraints[i][j] < 0) {
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1] + constraints[i][j];
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1];
					} else if(constraints[i][j] == 0) {
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1];
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1];
					}
				}
			}

			if(constants[44] > 0)
				constants_sum_pos[44] = constants[44];
			else
				constants_sum_pos[44] = 0;

			for(int i=43; i>=0; i--){
				if(constants[i] > 0){
					constants_sum_pos[i] = constants_sum_pos[i+1] + constants[i];
				} else {
					constants_sum_pos[i] = constants_sum_pos[i+1];
				}
			}

			// max_or_min = 1
			algorithm(1);

		} else if(!strcmp("minimize",line)) {
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<48; j++) {
					constraints[i][j] = 0;
					constants[j] = 0;
					x_test[j] = 0;
					xs_existent[j] = false;
				}
			}
			constraints_count = 0;
			parse_equation();

			for(int i=0; i<constraints_count; i++){
				if(constraints[i][max_x-1] > 0)
					constraints_sum_pos[i][max_x-1] = constraints[i][max_x-1];
				else if(constraints[i][max_x-1] < 0)
					constraints_sum_neg[i][max_x-1] = constraints[i][max_x-1];
				else{
					constraints_sum_pos[i][max_x-1] = 0;
					constraints_sum_neg[i][max_x-1] = 0;
				}

				for(int j=max_x-2; j>=0; j--){
					if(constraints[i][j] > 0){
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1] + constraints[i][j];
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1];
					} else if(constraints[i][j] < 0) {
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1] + constraints[i][j];
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1];
					} else {
						constraints_sum_neg[i][j] = constraints_sum_neg[i][j+1];
						constraints_sum_pos[i][j] = constraints_sum_pos[i][j+1];
					}
				}
			}

			if(constants[44] < 0)
				constants_sum_neg[44] = constants[44];
			else
				constants_sum_neg[44] = 0;

			for(int i=43; i>=0; i--){
				if(constants[i] < 0){
					constants_sum_neg[i] = constants_sum_neg[i+1] + constants[i];
				} else {
					constants_sum_neg[i] = constants_sum_neg[i+1];
				}
			}

			// max_or_min = -1
			algorithm(-1);
		}
	}

	return 0;
}
