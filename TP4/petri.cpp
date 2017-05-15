#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

/* Estrutura para os pontos partida + outra para as transições */

struct trans_t {
	int n_dest;
	int n_from;
	int *from;
	int *dest;
};

/* Funcoes...

check if:
root node - petri net initial state
terminal node - this is any node from which no transition can fire
duplicate node - a node identical to a node already in the tree

node dominance - "x dominates y" if:
(a) y(p) <= x(p) for all values of p
(b) y(p) < x(p) for at least some p

*/

void print_cur_state(int* places, int n_places) {
	printf("STATE = [");
	int i = 0;
	for(i=0; i < n_places-1; i++) {
		printf("%d, ", places[i]);
	}
	printf("%d]\n", places[i]);
}

void print_transitions(trans_t** transitions, int n_places, int n_transitions) {
	//printf("+++++++++++++++++++++++++++\n");
	printf("###############################\n");
	for(int i=0; i < n_transitions; i++) {
		for(int j=0; j < n_places; j++) {
			printf("# transitions[%d]->from[%d] = %d #\n", i, j, transitions[i]->from[j]);
		}
		//printf("+++++++++++++++++++++++++++\n");
		printf("# --------------------------- #\n");
		for(int j=0; j < n_places; j++) {
			printf("# transitions[%d]->dest[%d] = %d #\n", i, j, transitions[i]->dest[j]);
		}
		printf("###############################\n");
	}
}

void dfs(int* places, trans_t** transitions, int n_places, int n_transitions, int level) {
	print_cur_state(places, n_places);
	print_transitions(transitions, n_places, n_transitions);

	// ver as transicoes que podem ser feitas, por ordem crescente ||||| 
	// se se puder fazer, alterar array de places, chamar a funcao recursiva |||| 
	// depois tirar a cena que foi alterada e continuar o for || se for 
	for(int i=0; i < n_transitions; i++) {
		int aux = 0;
		for(int j = 0; j<n_places; j++){
			if(places[j] < transitions[i]->from[j]){
				aux = -1;
				break;
			}
		}
		if(aux != -1){
			//pode-se executar esta transicao
			

		}
		
	}
}

void input(int &n_places, int &n_transitions, trans_t** &transitions, int* places) {
	scanf("%d %d", &n_places, &n_transitions);

	transitions = (trans_t**) malloc (n_transitions * sizeof(trans_t*));
	for(int i=0; i < n_transitions; i++) {
		transitions[i] = (trans_t*) malloc (sizeof(trans_t));
		transitions[i]->from = (int*) malloc(n_places * sizeof(int));
		for(int j = 0; j<n_places; j++){
			transitions[i]->from[j] = 0;
		}
		transitions[i]->dest = (int*) malloc(n_places * sizeof(int));
		for(int j = 0; j<n_places; j++){
			transitions[i]->dest[j] = 0;
		}
		transitions[i]->n_dest = 0;
		transitions[i]->n_from = 0;
	}

	char line[64];
	int n1, n2, type;

	while (scanf("%d %d %d", &n1, &n2, &type) == 3) {
		if (type == 1) {	// Transição n1 vai para n2
			transitions[n1-1]->dest[n2-1]++;
			transitions[n1-1]->n_dest++;
		} else {	// Transição n2 vem de n1
			transitions[n2-1]->from[n1-1]++;
			transitions[n2-1]->n_from++;
		}
	}

	fgets(line, 16, stdin);
	for(int i=0; i<n_places; i++){
		scanf("%d ",&places[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);	

	int n_places = 0;
	int n_transitions = 0;

	int* places = (int*) malloc (sizeof(int) * n_places);
	trans_t** transitions;

	input(n_places, n_transitions, transitions, places);
	dfs(places, transitions, n_places, n_transitions, 0);

	return 0;
}