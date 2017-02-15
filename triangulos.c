#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Peca {
	int arestas[3][2];
	int orientacao; /* 0 -> 5 */
	int coords[2];
	int used;
} peca;

void output(peca* p, int size) {
	int i;
	for(i=0;i<size;i++) {
		printf("[ (%d, %d) (%d, %d) (%d, %d) ]\n",
			p[i].arestas[0][0], p[i].arestas[0][1],
			p[i].arestas[1][0], p[i].arestas[1][1],
			p[i].arestas[2][0], p[i].arestas[2][1]);
	}
}

// retorna size = n de pecas
int input(peca* pecas) {
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

		pecas[i].coords[0] = -1;
		pecas[i].coords[1] = -1;
		i++;
	}
	return i;
}

/* PAR -> Em cima | IMPAR -> Em baixo */
peca *connected(int *coords, int orientacao, peca **tabuleiro) {
	peca vizinhas[3];	/* Esquerda | Direita | Cima ou Baixo */ 
	if (orientacao % 2 == 0) {
		if (tabuleiro[coords[0]-1][coords[1]].used != 0) {	/* Peça em cima */
			vizinhas[2] = tabuleiro[coords[0]-1][coords[1]];
		}
	} else {
		if (tabuleiro[coords[0]+1][coords[1]].used != 0) {	/* Peça em baixo */
			vizinhas[2] = tabuleiro[coords[0]+1][coords[1]];
		}
	}
	if (tabuleiro[coords[0]][coords[1]-1].used != 0) {	/* Peça na esquerda */
		vizinhas[0] = tabuleiro[coords[0]][coords[1]-1];
	} if (tabuleiro[coords[0]][coords[1]+1].used != 0) {	/* Peça na direita */
		vizinhas[1] = tabuleiro[coords[0]][coords[1]+1];
	}
	return vizinhas;
}

int main(void) {
	peca pecas[20];
	printf("%d\n", pecas[0].arestas[0][0]);
	int i, j;

	int size = input(pecas);
	if (size == 0) {
		return 1;
	}
	printf("Numero de pecas = %d\n", size);
	output(pecas, size);

	int score = 0;
	peca **tabuleiro = (peca**) calloc(2*size, sizeof(peca*));
	for(i=0;i<2*size;i++) {
		tabuleiro[i] = (peca*) calloc(2*size, sizeof(peca));
	}

	for(i=0;i<2*size;i++) {
		for(j=0;j<2*size;j++) {
			printf("%d ", tabuleiro[i][j].used);
		}
		printf("\n");
	}

	/*for(i=0;i<size;i++) {
		tabuleiro[size][size] = pecas[i];	// Peça inicial
		pecas[i].used = 1;
		pecas[i].coords = [size, size];
	}*/

	return 0;
}
