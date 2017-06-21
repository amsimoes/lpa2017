#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcoes...

check if:
root node - petri net initial state
terminal node - this is any node from which no transition can fire
duplicate node - a node identical to a node already in the tree

node dominance - "x dominates y" if:
(a) y(p) <= x(p) for all values of p
(b) y(p) < x(p) for at least some p

*/

using namespace std;

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

node_t* new_node(int* places, int n_places, int depth_level, int terminal, int duplicated, node_t* parent) {
	node_t* n = (node_t*) malloc (sizeof(node_t));
	n->places = (int*) malloc (sizeof(int) * n_places);
	memcpy(n->places, places, n_places * sizeof(int));
	n->depth_level = depth_level;
	n->terminal = terminal;
	n->duplicated = duplicated;
	n->n_children = 0;
	if (parent != NULL) {
		n->parent = (node_t*) malloc (sizeof(node_t));
		memcpy(n->parent, parent, sizeof(node_t));
	} else {
		n->parent = NULL;
	}
	n->children = NULL;
	return n;
}

void insert_children_node(node_t* &parent, node_t* &child) {
	parent->n_children++;
	int n_children = parent->n_children;
	parent->children = (node_t**) realloc (parent->children, sizeof(node_t*) * n_children);
	parent->children[n_children-1] = (node_t*) malloc (sizeof(node_t));
	memcpy(parent->children[n_children-1], child, sizeof(node_t));

	child->parent = (node_t*) malloc (sizeof(node_t));
	memcpy(child->parent, parent, sizeof(node_t));
}

void set_node_terminal(node_t* n) {
	n->terminal = 1;
}

void print_cur_state(node_t* n, int n_places) {
	printf("STATE = [");
	int i = 0;
	for(i=0; i < n_places-1; i++) {
		printf("%d, ", n->places[i]);
	}
	printf("%d]\n", n->places[i]);
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
		//printf("places[%d] = %d / from[%d] = %d\n", i, places[i], i, from[i]);
		if (places[i] < from[i] && places[i] != -2) {
			return 0;
		}
	}
	return 1;
}

int compare_nodes(int* n1, int* n2, int len) {
	for(int i=0; i < len; i++) {
		if (n1[i] != n2[i])
			return 0;
	}
	return 1;
}

int check_duplicate(node_t* parent, int* new_places, int n_places) {
	node_t* aux = parent;
	while (aux != NULL) {
		if (compare_nodes(aux->places, new_places, n_places)) {
			return 1;
		}
		aux = aux->parent;
	}
	return 0;
}

void compare_dominated(int* arr_parent, int* &arr_child, int len) {
	for (int i=0; i < len; i++) {
		if (arr_parent[i] > arr_child[i]) {
			return;
		}
	}
	for (int i=0; i < len; i++) {
		if (arr_parent[i] < arr_child[i]) {
			arr_child[i] = -2;
		}
	}
}

void check_dominated(node_t* parent, int* &new_places, int n_places) {
	node_t* aux = parent;
	while (aux != NULL) {
		compare_dominated(aux->places, new_places, n_places);
		aux = aux->parent;
	}
}

void calc_transition(int* places, int* &new_places, int n_places, int* from, int* dest) {
	/*for (int k=0; k < n_places; k++) {
		printf("places[%d] = %d / from[%d] = %d / dest[%d] = %d\n", k, places[k], k, from[k], k, dest[k]);
	}*/
	for (int i=0; i < n_places; i++) {
		if (places[i] == -2) {
			new_places[i] = -2;
			continue;	
		} else if (dest[i] > 0) {
			new_places[i] = places[i] + dest[i];
			new_places[i] -= from[i]; 
		} else {
			new_places[i] = places[i] - from[i];
		}
	}
}

void print_state(int* new_places, int n_places, int level) {
	int i;
	for (i=0; i < level; i++) {
		printf(" ");
	}

	for (i=0; i < n_places - 1; i++) {
		if (new_places[i] == -2)
			printf("w ");
		else 
			printf("%d ", new_places[i]);
	}
	if (new_places[n_places-1] == -2)
		printf("w\n");
	else
		printf("%d\n", new_places[n_places-1]);

}

void dfs(node_t* parent, trans_t** transitions, int n_places, int n_transitions, int level) {
	//print_cur_state(parent, n_places);

	// evaluate the transition function for all transitions
	int trans_defined = 0;
	for (int i=0; i < n_transitions; i++) {
		/*for(int k=0; k < n_places; k++) {
			printf("from[%d] = %d\n", k, transitions[i]->from[k]);
		}*/
		if (evaluate_transition(parent->places, transitions[i]->from, n_places)) {
			//printf("TRANSICAO %d\n", i);

			//for (int k = 0; k < n_places; k++)
			//	printf("places[%d] = %d\n", k, parent->places[k]);
			int* new_places = (int*) malloc (sizeof(int) * n_places);
			calc_transition(parent->places, new_places, n_places, transitions[i]->from, transitions[i]->dest);
			
			/*for (int k = 0; k < n_places; k++)
				printf("new_places[%d] = %d\n", k, new_places[k]);*/

			if (check_duplicate(parent, new_places, n_places)) {
				//printf("DUPLICATED\n");
				node_t* child = new_node(new_places, n_places, level+1, 0, 1, parent);
				insert_children_node(parent, child);
				print_state(new_places, n_places, level+1);
				//return;
			} else {
				check_dominated(parent, new_places, n_places);
				node_t* child = new_node(new_places, n_places, level+1, 0, 0, parent);	
				insert_children_node(parent, child);
				//print_cur_state(child, n_places);
				print_state(new_places, n_places, level+1);
				dfs(child, transitions, n_places, n_transitions, level+1);
				trans_defined = 1;
			}
		}
	}

	if (!trans_defined) {	// mark place as terminal, nenhuma transition possivel
		set_node_terminal(parent);
		return;
	}
}

void print_tree(node_t* node, int n_places) {
	int i;
	for (i=0; i < node->depth_level; i++) {
		printf(" ");
	}

	for (i=0; i < n_places - 1; i++) {
		if (node->places[i] == -2)
			printf("w ");
		else 
			printf("%d ", node->places[i]);
	}

	printf("%d\n", node->places[n_places-1]);

	for (i=0; i < node->n_children; i++) {
		print_tree(node->children[i], n_places);
	}
}

node_t* input(int &n_places, int &n_transitions, trans_t** &transitions, int* places) {
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
	return new_node(places, n_places, 0, 0, 0, NULL);
}

int main() {
	ios::sync_with_stdio(false);	

	int n_places = 0;
	int n_transitions = 0;

	int* places = (int*) malloc (sizeof(int) * n_places);
	trans_t** transitions;

	node_t* root_node = input(n_places, n_transitions, transitions, places);

	//print_transitions(transitions, n_places, n_transitions);
	print_state(places, n_places, 0);
	dfs(root_node, transitions, n_places, n_transitions, 0);
	//print_tree(root_node, n_places);


	return 0;
}