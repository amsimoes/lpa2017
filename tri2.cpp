#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Peca {
	int arestas[3][3];
	int orientacao; /* 0 -> 5 */
	int coords[2];
	int used;
} peca;

int maxscore = 0;

void output(peca* p, int size);
int input(peca* p);
void print_board(peca** tabuleiro, int size);
void set_position(peca** tabuleiro, peca* pecas, int x, int y, int orientacao, int i);
int play(peca p, peca** tabuleiro, peca* pecas, int score, int size);
void reset_peca(peca* p, int size);
int ingame(peca** tabuleiro, int size);
void default_peca(peca* p);


int main(void) {
	peca pecas[20];
	int i;

	int size = input(pecas);
	if (size == 0) {
		return 1;
	}
	//printf("Numero de pecas = %d\n", size);

	peca **tabuleiro = (peca**) calloc(2*size+1, sizeof(peca*));
	for(i=0;i<2*size+1;i++) {
		tabuleiro[i] = (peca*) calloc(2*size+1, sizeof(peca));
	}

	for(i=0;i<size;i++) {
		pecas[i].coords[0] = size;  pecas[i].coords[1] = size;
		set_position(tabuleiro, pecas, size, size, 0, i);
		play(pecas[i], tabuleiro, pecas, 0, size);
	}

	printf("%d\n", maxscore);

	return 0;
}

/*int check_lock(peca peca, peca** tabuleiro, peca *pecas, int x, int y, int orientacao, int i) {
	Verificar diagonais (que têm a mesma orientacao) 
	return 1;
} */ 

void reset_peca(peca* p, int size) {
	int i;
	for(i=0;i<size;i++) {
		p->arestas[i][2] = 0;
	}
	p->used = 0;
	p->coords[0] = -1; p->coords[1] = -1;
	p->orientacao = 0;
}

void set_position(peca** tabuleiro, peca* pecas, int x, int y, int orientacao, int i) {
	pecas[i].orientacao = orientacao;
	tabuleiro[y][x] = pecas[i];
	pecas[i].used = 1;
	pecas[i].coords[0] = y;
	pecas[i].coords[1] = x;
}

int play(peca p, peca** tabuleiro, peca* pecas, int score, int size) {
	int i, k, l;
	int x = p.coords[1]; 
	int y = p.coords[0];
	for(i=0;i<size;i++) {
		//printf("USADA = %d\n", pecas[i].used);
		if(pecas[i].used != 1) {
			for(k=0;k<3;k++) {
				if(p.arestas[k][2] != 1) {	/* Se aresta não está já ligada */
					for(l=0;l<3;l++) {
						if(p.arestas[k][0] == pecas[i].arestas[l][1] && p.arestas[k][1] == pecas[i].arestas[l][0]) {
							p.arestas[k][2] = 1;
							pecas[i].arestas[l][2] = 1;
							if(p.orientacao == 0) {
								if(k == 0) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 1, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 5, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 3, i);
									}
								} else if(k == 1) { /* Nova peca em cima */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y-1, 3, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y-1, 1, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y-1, 5, i);
									}
								} else if(k == 2) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 5, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 3, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 1, i);
									}
								}
							} else if(p.orientacao == 1) {
								if(k == 0) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 0, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 4, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 2, i);
									}
								} else if(k == 1) { /* Nova peca em baixo */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y+1, 2, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y+1, 0, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y+1, 4, i);
									}
								} else if(k == 2) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 4, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 2, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 0, i);
									}
								}
							} else if(p.orientacao == 2) {
								if(k == 0) { /* Nova peca em cima */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y-1, 3, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y-1, 1, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y-1, 5, i);
									}
								} else if(k == 1) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 5, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 3, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 1, i);
									}
								} else if(k == 2) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 1, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 5, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 3, i);
									}
								}
							} else if(p.orientacao == 3) {
								if(k == 0) { /* Nova peca em baixo */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y+1, 2, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y+1, 0, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y+1, 4, i);
									}
								} else if(k == 1) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 4, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 2, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 0, i);
									}
								} else if(k == 2) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 0, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 4, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 2, i);
									}
								}
							} else if(p.orientacao == 4) {
								if(k == 0) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 5, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 3, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 1, i);
									}
								} else if(k == 1) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 1, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 5, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 3, i);
									}
								} else if(k == 2) { /* Nova peca em cima */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y-1, 3, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y-1, 1, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y-1, 5, i);
									}
								}
							} else if(p.orientacao == 5) {
								if(k == 0) { /* Nova peca na esquerda */
									if(l == 0) {
										set_position(tabuleiro, pecas, x-1, y, 4, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x-1, y, 2, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x-1, y, 0, i);
									}
								} else if(k == 1) { /* Nova peca na direita */
									if(l == 0) {
										set_position(tabuleiro, pecas, x, y-1, 0, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x, y-1, 4, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x, y-1, 2, i);
									}
								} else if(k == 2) { /* Nova peca em baixo */
									if(l == 0) {
										set_position(tabuleiro, pecas, x+1, y, 2, i);
									} else if(l == 1) {
										set_position(tabuleiro, pecas, x+1, y, 0, i);
									} else if(l == 2) {
										set_position(tabuleiro, pecas, x+1, y, 4, i);
									}
								}
							}
							score += pecas[i].arestas[l][0] + pecas[i].arestas[l][1];
							//printf("PECAS JOGADAS = %d | SCORE = %d\n", count, score);
							//printf("\nPECA = %d %d %d | COORDS = (%d, %d)\n",
							//pecas[i].arestas[0][0], pecas[i].arestas[1][0], pecas[i].arestas[2][0], y, x);
							//print_board(tabuleiro, size);
							//printf("SCORE = %d\n", score);
							play(pecas[i], tabuleiro, pecas, score, size);
							reset_peca(&p, size);
							score -= pecas[i].arestas[l][0] + pecas[i].arestas[l][1];
						}
					}
				}
			}
		}
	}
	if(score > maxscore) {
		maxscore = score;
	} 
	peca p_aux; default_peca(&p_aux);
	tabuleiro[y][x] = p_aux;

	return 0;	
}

void default_peca(peca* p) {
	int i;
	for(i=0;i<3;i++) {
		p->arestas[i][0] = 0;
		p->arestas[i][1] = 0;
		p->arestas[i][2] = 0;
	}
	p->used = 0;
	p->coords[0] = -1; p->coords[1] = -1;
	p->orientacao = 0;
}

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

int ingame(peca** tabuleiro, int size) {
	int i = 0; int j = 0;
	int count;
	for(i=0;i<2*size;i++) {
		for(j=0;j<2*size;j++) {
			if(tabuleiro[i][j].used == 1) 
				count++;
		}
	}
	return count;
}

void print_board(peca** tabuleiro, int size) {
	int i, j;
	//int count = ingame(tabuleiro, size);
	printf("\n-> BOARD [%dx%d]\n", 2*size, 2*size);
	printf("+ "); for(j=0;j<2*size;j++) printf("+ + + + "); printf("+ \n");
	for(i=0;i<2*size;i++) {
		printf("+ ");
		for(j=0;j<2*size;j++) {
			printf("(%d %d %d) ", tabuleiro[i][j].arestas[0][0], tabuleiro[i][j].arestas[1][0], tabuleiro[i][j].arestas[2][0]);
		}
		printf("+\n");
	}
	printf("+ "); for(j=0;j<2*size;j++) printf("+ + + + "); printf("+ \n\n");
}



int* reverse_aresta(int aresta[]){
	int temp;
	temp = aresta[0];
	aresta[0] = aresta[1];
	aresta[1] = temp;
	return aresta;
}
