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
int x_best[45];
int best;
int constraints_count;
int x_count;
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

int test_constraints(int x_index){ // -1 -> impossível || 0 -> certo || 1 -> pode continuar
	int flag = 0;
	for(int i=0; i<constraints_count; i++){
		int aux = constraints[i][47];
		if(constraints[i][45] == 1 && aux < constraints[i][46]){
			flag = 1;
			for(int j=x_index+1; j<max_x; j++){
				if(constraints[i][j] > 0)
					aux+=constraints[i][j];
			}
			if(aux < constraints[i][46])
				return -1;
		}
		else if(constraints[i][45] == 0){
			if(aux > constraints[i][46]){
				flag = 1;
				for(int j=x_index+1; j<max_x; j++){
					if(constraints[i][j] < 0)
						aux+=constraints[i][j];
				}
				if(aux > constraints[i][46])
					return -1;
			}
			else if(aux < constraints[i][46]){
				flag = 1;
				for(int j=x_index+1; j<max_x; j++){
					if(constraints[i][j] > 0)
						aux+=constraints[i][j];
				}
				if(aux < constraints[i][46])
					return -1;
			}
		}
		else if(constraints[i][45] == -1 && aux > constraints[i][46]){
			flag = 1;
			for(int j=x_index+1; j<max_x; j++){
				if(constraints[i][j] < 0)
					aux+=constraints[i][j];
			}
			if(aux > constraints[i][46])
				return -1;
		}
	}
	if(flag)
		return 1;
	return 0;
}

int find_next(int index){
	//printf("testing x%d\n", index);
	int v = 50;
	for(int i=0; i<constraints_count; i++){
		for(int j=index; j<max_x; j++){
			if((constraints[i][j] != 0 || constants[j] != 0) && j < v){
				//printf("next valid is x%d\n", j+1);
				v = j;
			}
		}
	}
	if (v == 50)
		return -1;

	//printf("there isn't a valid index\n");
	return v;
}

void branch_and_bound(int x_index, int max_or_min, int current_sum){
	//printf("\n\nentrei numa nova recursao:\n\n");

	/*for(int i = 0; i<max_x; i++){
		printf("x_test[%d] = %d\n", i, x_test[i]);
	}*/
	//printf("x_index = %d\n", x_index);
	// ----------
	// Verifies if x_index is on any constraint or the equation
	/*bool valid = false;
	for(int i=0; i<constraints_count; i++){
		if(constraints[i][x_index] != 0)
			valid = true;
	}
	if(!valid && constants[x_index] == 0){
		if(x_index != max_x - 1){
			branch_and_bound(x_index+1, max_or_min); // Call for Branch and Bound with x_test[x_index+1] = 0
			x_test[x_index+1] = 1;
			branch_and_bound(x_index+1, max_or_min); // Call for Branch and Bound with x_test[x_index+1] = 0
			x_test[x_index+1] = 0; // Reset for when returning from recursive call
			return;
		}
	}	*/
	// ----------


	int test = test_constraints(x_index);
	if(test == 0) { // Se passar nas constraints
		solution = true;
		//int val = calc_expression(); // Returns value of expression with current values of x_test
		if(max_or_min == 1){ // Maximizar
			//printf("current_sum: %d, x_test[%d]: %d\n", current_sum, x_index, x_test[x_index]);
			if(current_sum > best)
				best = current_sum;

			int next = find_next(x_index+1);
			if(next == -1)
				return;
			int sum_aux = 0;
			for (int k = next; k < 45; k++){
				if(constants[k]>0)
					sum_aux += constants[k];
			}
			if(current_sum + sum_aux > best){
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
		}
		else if(max_or_min == -1){ // Minimizar
			//printf("current_sum: %d, x_test[%d]: %d\n", current_sum, x_index, x_test[x_index]);
			if(current_sum < best)
				best = current_sum;

			int next = find_next(x_index+1);
			if(next == -1)
				return;
			int sum_aux = 0;
			for (int k = next; k < 45; k++){
				if(constants[k]<0)
					sum_aux += constants[k];
			}
			if(current_sum + sum_aux < best){
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
		}
		return;
	} else if(test == 1) { // Se não passar nas constraints
		if(x_index == max_x-1)
			return;
		//printf("current_sum: %d, x_test[%d]: %d\n", current_sum, x_index, x_test[x_index]);
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
	else if(test == -1){
		return;
	}
}


void algorithm(int max_or_min) {
	if (max_or_min == 1){
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
		constraints[i][47]+=constraints[i][0];
	}
	branch_and_bound(0, max_or_min, constants[0]); // Call for Branch and Bound with x_test[0] = 1
	if(!solution)
		printf("INFEASIBLE\n");
	else
		printf("%d\n",best);
}


int main() {
	clock_t begin = clock();
	ios::sync_with_stdio(false);
	char line[50];

	constraints_count = 0;
	while(scanf("%s\n",line) >= 1) {
		if(!strcmp("maximize",line)){
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<48; j++) {
					constraints[i][j] = 0;
					constants[j] = 0;
					x_test[j] = 0;
				}
			}
			constraints_count = 0;
			parse_equation();
			algorithm(1);
		} else if(!strcmp("minimize",line)) {
			for(int i=0; i<constraints_count; i++) {
				for(int j=0; j<48; j++) {
					constraints[i][j] = 0;
					constants[j] = 0;
					x_test[j] = 0;
				}
			}
			constraints_count = 0;
			parse_equation();
			algorithm(-1);
		}
	}

	clock_t end = clock();
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

	printf("\nexecution time = %f\n", time_spent);

	return 0;
}