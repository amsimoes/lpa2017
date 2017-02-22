#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>

typedef struct Peca {
	int arestas[3][3];
	int orientacao; /* 0 -> 5 */
	int coords[2];
	int used;
} peca;

int maxscore = 0;
int repetidos = 0;
std::vector<peca> jogadas;

void output(peca* p, int size);
int input(peca* p);
void print_board(peca** tabuleiro, int size);
void set_position(peca** tabuleiro, peca* pecas, int x, int y, int orientacao, int i);
int play(peca** tabuleiro, peca* pecas, int score, int size);
void reset_peca(peca* p);
int ingame(peca** tabuleiro, int size);
void default_peca(peca* p);
void check_repeated(peca* pecas, int size);

int main(void) {
	peca *pecas = (peca*) calloc(20, sizeof(peca));
	int i = 0;
	int j = 0;

	int size = input(pecas);
	if (size == 0) {
		return 1;
	}

	//check_repeated(pecas, size);
	//printf("Tem repetidos = %d\n", repetidos);

	peca **tabuleiro = (peca**) calloc(2*size+1, sizeof(peca*));
	for(i=0;i<2*size+1;i++) {
		tabuleiro[i] = (peca*) calloc(2*size+1, sizeof(peca));
	}

	for(i=0;i<size;i++) {
		//printf("main i = %d\n", i);
		pecas[i].coords[0] = size;  pecas[i].coords[1] = size;
		set_position(tabuleiro, pecas, size, size, 0, i);
		//printf("jogadas.size = %lu\n", jogadas.size());
		if(jogadas.size() != 0){
			jogadas.at(0) = pecas[i];
		}
		else
			jogadas.push_back(pecas[i]);
		play(tabuleiro, pecas, 0, size);
		//printf("erase main\n");
		//jogadas.erase(jogadas.begin()+ jogadas.size());
		//printf("after erase\n");
		for(j=0;j<size;j++) {
			pecas[j].used = 0;
			pecas[j].orientacao = 0;
		}
	}

	printf("%d\n", maxscore);

	return 0;
}

void check_repeated(peca* pecas, int size) {
	int i = 0, j = 0;
	for(i=0;i<size;i++){
		for(j=i+1;j<size-1;j++) {
			if(pecas[i].arestas[0][0] == pecas[j].arestas[0][0] && \
			   pecas[i].arestas[1][0] == pecas[j].arestas[1][0] && \
			   pecas[i].arestas[2][0] == pecas[j].arestas[2][0]) {
				repetidos = 1;
				return;
			}
		}
	}
	return;
}

void reset_peca(peca* p) {
	int i;
	for(i=0;i<3;i++) {
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

int play(peca** tabuleiro, peca* pecas, int score, int size) {
	int i=0, k=0, l=0, h=0;
	int x;
	int y;
	for(h=0;h<jogadas.size();h++){
		x=jogadas.at(h).coords[1];
		y=jogadas.at(h).coords[0];
		for(i=0;i<size;i++) {
			if(pecas[i].used != 1) {
				//printf("pecas[%d].used = %d\n", i, pecas[i].used);
				for(k=0;k<3;k++) {
					if(jogadas.at(h).arestas[k][2] != 1) {	/* Se aresta não está já ligada */
						for(l=0;l<3;l++) {
							if(jogadas.at(h).arestas[k][0] == pecas[i].arestas[l][1] && jogadas.at(h).arestas[k][1] == pecas[i].arestas[l][0]) {
								/*printf("Peca a testar = %d %d %d | Used = %d\n",pecas[i].arestas[0][0],\
								pecas[i].arestas[1][0], pecas[i].arestas[2][0], pecas[i].used);*/
								//printf("Coordenadas = (%d, %d)\n", x, y);
								jogadas.at(h).arestas[k][2] = 1;
								pecas[i].arestas[l][2] = 1;
								if(jogadas.at(h).orientacao == 0) {
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
								} else if(jogadas.at(h).orientacao == 1) {
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
								} else if(jogadas.at(h).orientacao == 2) {
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
								} else if(jogadas.at(h).orientacao == 3) {
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
								} else if(jogadas.at(h).orientacao == 4) {
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
								} else if(jogadas.at(h).orientacao == 5) {
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
											set_position(tabuleiro, pecas, x+1, y, 0, i);
										} else if(l == 1) {
											set_position(tabuleiro, pecas, x+1, y, 4, i);
										} else if(l == 2) {
											set_position(tabuleiro, pecas, x+1, y, 2, i);
										}
									} else if(k == 2) { /* Nova peca em baixo */
										if(l == 0) {
											set_position(tabuleiro, pecas, x, y-1, 2, i);
										} else if(l == 1) {
											set_position(tabuleiro, pecas, x, y-1, 0, i);
										} else if(l == 2) {
											set_position(tabuleiro, pecas, x, y-1, 4, i);
										}
									}
								}
								//printf("Novas coordenadas = (%d, %d)\n", pecas[i].coords[0], pecas[i].coords[1]);
								score += pecas[i].arestas[l][0] + pecas[i].arestas[l][1];
								jogadas.push_back(pecas[i]);
								play(tabuleiro, pecas, score, size);
								jogadas.pop_back();
								peca p_aux;
								default_peca(&p_aux);
								tabuleiro[pecas[i].coords[0]][pecas[i].coords[1]] = p_aux;
								reset_peca(&pecas[i]);
								jogadas.at(h).arestas[k][2] = 0;
								score -= pecas[i].arestas[l][0] + pecas[i].arestas[l][1];
							}
						}
					}
				}
			}
		}
	}
	if(score > maxscore) {
		maxscore = score;
	}
	peca p_aux;
	default_peca(&p_aux);
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

		pecas[i].arestas[0][2] = 0;
		pecas[i].arestas[1][2] = 0;
		pecas[i].arestas[2][2] = 0;

		pecas[i].coords[0] = -1;
		pecas[i].coords[1] = -1;

		pecas[i].used = 0;
		pecas[i].orientacao = 0;
		i++;
	}
	return i;
}

int ingame(peca** tabuleiro, int size) {
	int i = 0; int j = 0;
	int count = 0;
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
