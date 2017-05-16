#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

/* Estrutura para os pontos partida + outra para as transições */

struct trans_t {
	int n_from;
	int n_dest;
	int *from;
	int *dest;
};

struct node_t {
	int* places;
	int terminal;
	int duplicated;
	int depth_level;
	int n_children;
	node_t* parent;
	node_t** children;
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

void new_node(int* places, int n_places, int depth_level, int terminal, node_t* parent) {
	node_t* n = (node_t*) malloc (sizeof(node_t));
	n->places = malloc (sizeof(int) * n_places);
	memcpy(n->places, places, n_places * sizeof(int));
	n->depth_level = depth_level;
	n->terminal = terminal;
	n->n_children = 0;
	if (parent != NULL) {
		n->parent = (node_t*) malloc (sizeof(node_t));
		memcpy(n->parent, parent, sizeof(node_t));
	} else {
		n->parent = NULL;
	}
}

void insert_children_node(node_t* &parent, node_t* &child) {
	parent->n_children++;
	parent->children = (node_t**) realloc (parent->children, sizeof(node_t*) * n_children);
	memcpy(parent->children[n_children-1], child, sizeof(node_t));

	child->parent = (node_t*) malloc (sizeof(node_t));
	memcpy(child->parent, parent, sizeof(node_t));
}

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

int evaluate_transition(int* places, int* from, int n_places) {
	for(int i=0; i < n_places; i++) {
		if (places[i] < from[i]) {
			return 0;
		}
	}
	return 1;
}

void dfs(int* places, trans_t** transitions, int n_places, int n_transitions, int level) {
	print_cur_state(places, n_places);
	print_transitions(transitions, n_places, n_transitions);

	// evaluate the transition function for all transitions
	int trans_defined = 0;
	for (int i=0; i < n_transitions; i++) {
		if (evaluate_transition(places, transitions[i]->from, n_places)) {
			trans_defined = 1;
			new_node
		}
	}

	if (!trans_defined) {	// mark place as terminal, nenhuma transition possivel

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

	fgets(line, 16, stdin);	// STATE line

	// root node
	for(int i=0; i<n_places; i++) {
		scanf("%d ", &places[i]);
	}
	new_node()
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