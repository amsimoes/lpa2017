#include <stdio.h>
#include <stdlib.h>

struct Peca {
	int arestas[3][2];
	int rotacao = 0; /* 0 -> 5 */
	int posicao[2];
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

// retorna size
int input(struct Peca* pecas) {
	int v1, v2, v3;
	int i = 0;
	while(scanf("%d %d %d", &v1, &v2, &v3) == 3) {
		if (i == 19) {
			return 0;
		} else if (v1 > v2 || v1 > v3 || v2 > v3) {
			return 0;
		} else if (v1 > 5 || v2 > 5 || v3 > 5) {
			return 0;
		}

		//printf("%d %d %d\n", v1, v2, v3);
		pecas[i].arestas[0][0] = v1;
		pecas[i].arestas[0][1] = v2;
		pecas[i].arestas[1][0] = v2;
		pecas[i].arestas[1][1] = v3;
		pecas[i].arestas[2][0] = v3;
		pecas[i].arestas[2][1] = v1;
		i++;
	}
	return i;
}

int main(void) {
	struct Peca pecas[20];
	int size;

	size = input(pecas);
	if (size == 0) {
		return 1;
	}
	printf("Numero de pecas = %d\n", size);

	output(pecas, size);

	return 0;
}
