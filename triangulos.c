#include <stdio.h>
#include <stdlib.h>

struct Peca {
	int arestas[3][2];
};

void output(struct Peca* p, int size) {
	int i;
	for(i=0;i<size;i++) {
		printf("[ (%d, %d) (%d, %d) (%d, %d) ]\n",
			p[i].arestas[0][0], p[i].arestas[0][1],
			p[i].arestas[1][0], p[i].arestas[1][1],
			p[i].arestas[2][0], p[i].arestas[2][1]);
	}
}

int main(void) {
	struct Peca* pecas = (struct Peca*) malloc(sizeof(struct Peca));
	int v1, v2, v3;
	int i = 0;
	int size;

	while(scanf("%d %d %d", &v1, &v2, &v3) == 3) {
		if(i == 19) {
			return 1;
		}
		printf("%d %d %d\n", v1, v2, v3);
		pecas[i].arestas[0][0] = v1;
		pecas[i].arestas[0][1] = v2;
		pecas[i].arestas[1][0] = v2;
		pecas[i].arestas[1][1] = v3;
		pecas[i].arestas[2][0] = v3;
		pecas[i].arestas[2][1] = v1;
		i++;
		pecas = (struct Peca*) realloc(pecas, i*sizeof(struct Peca)+sizeof(struct Peca));
	}
	size = i;
	printf("Numero de pecas = %d\n", size);

	output(pecas, size);

	return 0;
}
