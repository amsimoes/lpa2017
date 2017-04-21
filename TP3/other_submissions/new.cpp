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
int l_bound = -99999;
int x_count;
int infeasible;
int max_x;
int x_test[45];

void get_constraints(){ 
	char scan;
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

int test_constraints() {
	int sum;
	for(int i = 0; i < constraints_count; i++) { // passar por todas as constraints
		sum = 0; 
		for(int j = 0; j < max_x; j++) { //passar por todos os x numa constraint
			//printf("x_test[%d]: %d\n",j,x_test[j]);
			if(constraints[i][j] != 0)
				sum += constraints[i][j] * x_test[j];
		}
		/*printf("sum = %d on constraint %d\n", sum, i);
		if(constraints[i][45] == -1)
			printf("<= %d\n",constraints[i][46]);
		if(constraints[i][45] == 1)
			printf(">= %d\n",constraints[i][46]);
		if(constraints[i][45] == 0)
			printf("= %d\n",constraints[i][46]);
		*/
		if(sum < constraints[i][46] && constraints[i][45] == 1){
			//printf("entrei aqui <\n");
			return 0;
		}
		else if(sum > constraints[i][46] && constraints[i][45] == -1){
			//printf("entrei aqui >\n");
			return 0;
		}
		else if(sum != constraints[i][46] && constraints[i][45] == 0){
			//printf("entrei aqui !=\n");
			return 0;
		}

	}
	return 1;
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
	//return max_x;
}


int calc_expression() {
	int result = 0; 
	for(int i = 0; i < max_x; i++) {
		if(constants[i] != 0)
			result += (x_test[i] * constants[i]);
		//printf("result = %d, array[%d] = %d, constants[%d] = %d\n", result, i, x_test[i], i, constants[i]);
	}
	return result;
}

void branch_and_bound(int x_index, int max_or_min){
	if(x_index > max_x)
		return;
	bool valid = false;
	/*for(int i=0; i<45; i++){
		//printf("x_test[%d] = %d\n", i, x_test[i]);
	}*/
	for(int i=0; i<constraints_count; i++){
		if(constraints[i][x_index] != 0)
			valid = true;
	}
	if(!valid && constants[x_index] == 0){
		//printf("dentro do invalid with x_test[%d+1] = 0\n",x_index);
		if(x_index != 43){
			x_test[x_index+2] = 1;
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 1;
			x_test[x_index+2] = 0;
			//printf("dentro do invalid with x_test[%d+1] = 1\n",x_index);
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 0;
			return;
		}
	}
	//printf("x_test[%d]: %d\n",x_index, x_test[x_index]);
	if(test_constraints() == 1){ // Se passar nas constraints´
		infeasible = 0;
		int val = calc_expression();
		//printf("val: %d\n",val);
		if(max_or_min == 1){ // Maximizar
			int aux = val;
			for(int i=x_index; i<45; i++){ // Verificar
				if(constants[i] > 0){
					aux += constants[i];
				}
			}
			if(aux < best)
				return;
			if(val > best){
				best = val;
			}
		}
		else if(max_or_min == -1){ // Minimizar
			int aux = val;
			for(int i=x_index; i<45; i++){
				if(constants[i] < 0){
					aux += constants[i];
				}
			}
			if(aux > best)
				return;
			if(val < best){
				best = val;
			}
		}
		if(x_index != 43){
			//printf("se passar nas constraints e x_index != 43 with x_test[%d+1] = 0\n",x_index);
			x_test[x_index+2] = 1;
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 1;
			x_test[x_index+2] = 0;
			//printf("se passar nas constraints e x_index != 43 with x_test[%d+1] = 1\n",x_index);
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 0;
			return;
		}
	}
	else{ // Se não passar nas constraints
		if(x_index != 43){
			//printf("call for branch_and_bound with x_test[%d+1] = 0\n",x_index);
			x_test[x_index+2] = 1;
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 1;
			x_test[x_index+2] = 0;
			//printf("call for branch_and_bound with x_test[%d+1] = 1\n",x_index);
			branch_and_bound(x_index+1, max_or_min);
			x_test[x_index+1] = 0;
			return;
		}
	}
}

void algorithm(int max_or_min) {
	best = 0;
	infeasible = 1;
	x_test[1] = 1;
	branch_and_bound(0, max_or_min);
	x_test[0] = 1;
	x_test[1] = 0;
	branch_and_bound(0, max_or_min);
	if(infeasible)
		printf("INFEASIBLE\n");
	else
		printf("%d\n",best);
}


int main() {
	//clock_t begin = clock();
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
			algorithm(1);
		} else if(!strcmp("minimize",line)) {
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<47; j++) {
					constraints[i][j] = 0;
				}
			}
			constraints_count = 0;
			parse_equation();
			algorithm(-1);
		}

		free(line);
		line = (char*)malloc(50*sizeof(char));
	}

	//clock_t end = clock();
	//double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

	//printf("\nexecution time = %f\n", time_spent);

	return 0;
}