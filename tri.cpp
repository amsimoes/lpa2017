#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <time.h>

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
void print_puzzle();

int main(void) {
	//clock_t begin = clock();
	peca *pecas = (peca*) calloc(20, sizeof(peca));
	int i = 0; 
	//int j = 0;
		
	int size = input(pecas);
	if (size == 0) {
		return 1;
	}

	peca **tabuleiro = (peca**) calloc(2*size+1, sizeof(peca*));
	for(i=0;i<2*size+1;i++) {
		tabuleiro[i] = (peca*) calloc(2*size+1, sizeof(peca));
	}

	for(i=0;i<size;i++) {
		pecas[i].coords[0] = size;  
		pecas[i].coords[1] = size;
		pecas[i].orientacao = 0;
		pecas[i].used = 1;
		tabuleiro[size][size] = pecas[i];
		jogadas.push_back(pecas[i]);
		play(tabuleiro, pecas, 0, size);
		jogadas.clear();
		/*for(j=0;j<size;j++) {
			printf("usada = %d\n", pecas[j].used);
		}*/
		//pecas[i].used = 0;
	}

	printf("%d\n", maxscore);
	//clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	//printf("%f\n", time_spent);
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

void reset_peca(peca* pecas, int i) {
	int j;
	pecas[i].used = 0;
	for(j=0;j<3;j++) {
		pecas[i].arestas[j][2] = 0;
	}
	pecas[i].coords[0] = -1; pecas[i].coords[1] = -1;
	pecas[i].orientacao = 0;
}

void set_position(peca** tabuleiro, peca* pecas, int x, int y, int orientacao, int i) {
	pecas[i].orientacao = orientacao;
	tabuleiro[y][x] = pecas[i];
	pecas[i].used = 1;
	pecas[i].coords[0] = y;
	pecas[i].coords[1] = x;
}

int play(peca** tabuleiro, peca* pecas, int score, int size) {
	int i=0, k=0, l=0;
	unsigned int h=0;
	int x;
	int y;
	for(h=0;h<jogadas.size();h++){
		if(jogadas.size() == (unsigned int) size) 
			continue;
		//printf("\th = %d\n", h);
		x=jogadas.at(h).coords[1];
		y=jogadas.at(h).coords[0];
		for(i=0;i<size;i++) {
			//printf("\t\ti = %d | used = %d\n", i, pecas[i].used);
			if(pecas[i].used != 1) {
				for(k=0;k<3;k++) {
					if(jogadas.at(h).arestas[k][2] != 1) {	/* Se aresta não está já ligada */
						for(l=0;l<3;l++) {
							if(jogadas.at(h).arestas[k][0] == pecas[i].arestas[l][1] && jogadas.at(h).arestas[k][1] == pecas[i].arestas[l][0]) {
								/*printf("Peca a testar = %d %d %d | Used = %d\n",pecas[i].arestas[0][0],\
								pecas[i].arestas[1][0], pecas[i].arestas[2][0], pecas[i].used);*/
								jogadas.at(h).arestas[k][2] = 1;
								pecas[i].arestas[l][2] = 1;
								if(jogadas.at(h).orientacao == 0) {
									if(k == 0) { /* Nova peca na esquerda */
										/* SE TEM ALGUM BURACO */
										if(tabuleiro[x-2][y].used == 1 || tabuleiro[x-1][y+1].used == 1) {
											if(tabuleiro[x-1][y+1].used == 1) {
												if(l == 2) {
													if(tabuleiro[x-1][y+1].orientacao == 0) {
														if(tabuleiro[x-1][y+1].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-1][y+1].arestas[0][1] == pecas[i].arestas[1][0]) {
															if(tabuleiro[x-2][y].orientacao == 0) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															} else if(tabuleiro[x-2][y].orientacao == 2) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															} else if(tabuleiro[x-2][y].orientacao == 4) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															}
														} 
													} else if(tabuleiro[x-1][y+1].orientacao == 2) {
														
													} else if(tabuleiro[x-1][y+1].orientacao == 4) {
														
													}
												} else if(l == 1) {
													if(tabuleiro[x-1][y+1].orientacao == 0) {
														if(tabuleiro[x-1][y+1].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-1][y+1].arestas[0][1] == pecas[i].arestas[1][0]) {
															if(tabuleiro[x-2][y].orientacao == 0) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															} else if(tabuleiro[x-2][y].orientacao == 2) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															} else if(tabuleiro[x-2][y].orientacao == 4) {
																if(tabuleiro[x-2][y].arestas[1][0] == pecas[i].arestas[0][1] && tabuleiro[x-2][y].arestas[0][1] == pecas[i].arestas[1][0]) {
																	set_position(tabuleiro, pecas, x-1, y, 3, i);
																}
															}
														} 
													}
												} else if(l == 0) {

												}
											}
										} else {
												if(l == 0) {
													set_position(tabuleiro, pecas, x-1, y, 1, i);
												} else if(l == 1) {
													set_position(tabuleiro, pecas, x-1, y, 5, i);
												} else if(l == 2) {
													set_position(tabuleiro, pecas, x-1, y, 3, i);
												}
											}
										} else {

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
									/*printf("%d %d %d | ORIENTACAO UM\n", jogadas.at(h).arestas[0][0],\
										jogadas.at(h).arestas[1][0], jogadas.at(h).arestas[2][0]);*/
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
									/*printf("%d %d %d | ORIENTACAO DOIS\n", jogadas.at(h).arestas[0][0],\
										jogadas.at(h).arestas[1][0], jogadas.at(h).arestas[2][0]);*/
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
									/*printf("%d %d %d | ORIENTACAO TRES\n", jogadas.at(h).arestas[0][0],\
										jogadas.at(h).arestas[1][0], jogadas.at(h).arestas[2][0]);*/
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
									/*printf("%d %d %d | ORIENTACAO QUATRO\n", jogadas.at(h).arestas[0][0],\
										jogadas.at(h).arestas[1][0], jogadas.at(h).arestas[2][0]);*/
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
									/*printf("%d %d %d | ORIENTACAO CINCO\n", jogadas.at(h).arestas[0][0],\
										jogadas.at(h).arestas[1][0], jogadas.at(h).arestas[2][0]);*/
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
											set_position(tabuleiro, pecas, x, y+1, 2, i);
										} else if(l == 1) {
											set_position(tabuleiro, pecas, x, y+1, 0, i);
										} else if(l == 2) {
											set_position(tabuleiro, pecas, x, y+1, 4, i);
										}
									}
								}
								score += pecas[i].arestas[l][0] + pecas[i].arestas[l][1];
								jogadas.push_back(pecas[i]);
								//print_board(tabuleiro, size);
								//printf("-> PLAY | Puzzle size = %lu\n", jogadas.size());
								//print_puzzle();
								play(tabuleiro, pecas, score, size);
								//printf("-> AFTER PLAY\n");
								if(score > maxscore) {
									maxscore = score;
								}
								jogadas.pop_back();
								peca p_aux; default_peca(&p_aux);
								tabuleiro[pecas[i].coords[0]][pecas[i].coords[1]] = p_aux;
								reset_peca(pecas, i);
								//printf("PLAY | Usada = %d\n", pecas[i].used);
								jogadas.at(h).arestas[k][2] = 0;
								score -= (pecas[i].arestas[l][0] + pecas[i].arestas[l][1]);
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void print_puzzle() {
	unsigned int i;
	printf("##########\n");
	printf("# PUZZLE #\n");
	for(i=0;i<jogadas.size();i++) {
		printf("# %d %d %d  #\n", jogadas.at(i).arestas[0][0], jogadas.at(i).arestas[1][0],\
							jogadas.at(i).arestas[2][0]);
	}
	printf("##########\n");
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
