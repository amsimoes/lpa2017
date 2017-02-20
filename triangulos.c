#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Peca {
	int arestas[3][2];
	int orientacao; /* 0 -> 5 */
	int coords[2];
	int used;
} peca;

int maxscore = 0;

void output(peca* p, int size);
int input(peca* p);
void print_board(peca** tabuleiro, int size);
peca *connected(int *coords, int orientacao, peca** tabuleiro);
int search_connection(peca atual, peca** tabuleiro, int score, peca pecas[], int size);

int main(void) {
	peca pecas[20];
	int i;

	int size = input(pecas);
	if (size == 0) {
		return 1;
	}
	printf("Numero de pecas = %d\n", size);

	peca **tabuleiro = (peca**) calloc(2*size, sizeof(peca*));
	for(i=0;i<2*size;i++) {
		tabuleiro[i] = (peca*) calloc(2*size, sizeof(peca));
	}

	print_board(tabuleiro, size); 

	int score = 0;
	score = search_connection(pecas[0], tabuleiro, maxscore, pecas, size);
	/* printf("%d\n", score); */

	return 0;
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
	printf("\n-> BOARD [%dx%d] [%d PECAS EM JOGO]\n", 2*size, 2*size, ingame(tabuleiro, size));
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

int* reverse_aresta(int aresta[]){
	int temp;
	temp = aresta[0];
	aresta[0] = aresta[1];
	aresta[1] = temp;
	return aresta;
}

/*
void flipa_arestas(peca peca, int num_rotatos){
	/*arestasm devem ser esquerda[0], direita[1], cima/baixo[2]
	for (int i = 0; i<num_rotatos; i++){
		peca.arestas[0][0] = peca.arestas[0]
	}
}  */

int search_connection(peca atual, peca** tabuleiro, int score, peca pecas[], int size){
	/*comparar score com max score no fim e se for maior atualizar valor |||||||||| quando atualizar valor de score?*/
	if (atual.orientacao == 0) {
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, cima*/
		for(int i = 0; i<size; i++){
			for (int k= 0; k<3; k++){
				/*se encontrarmos o par contrario da aresta numa posicao 0, como os triangulos estao na posicao 0 originalmente, é a aresta da esquerda
				para ligar a uma cena numa posicao par, se for igual à cena da esquerda, vai ter de rodar até à posicao 5*/
				if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
					/*encontrou igual à esquerda da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
                        nova.coords[1] = y-1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k==1 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x;
                        nova.coords[1] = y-1;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y-1].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x;
                        nova.coords[1] = y-1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;

						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
				/*se encontrarmos o par contrario da aresta numa posicao 1, como os triangulos estao na posicao 0 originalmente, é a aresta da direita
				para ligar a uma cena numa posicao par, se for igual à cena da direita, vai ter de todar até à posicao 5*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
                        nova.coords[1] = y+1;
 						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado direito */
                        nova.coords[0] = x;
                        nova.coords[1] = y+1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y+1].used ==0){
						/*aresta de cima*/
						nova.coords[0] = x;
                        nova.coords[1] = y+1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
					}
				}
				/*se encontrarmos o par contrario da aresta numa posicao 2, como os triangulos estao na posicao 0 originalmente, é a aresta de cima
				para ligar a uma cena numa posicao par*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado esquerdo*/
                        nova.coords[0] = x+1;
                        nova.coords[1] = y;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado direito FEITA*/
                        nova.coords[0] = x+1;
                        nova.coords[1] = y;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x+1][y].used == 0) {
						/*aresta de cima*/
						nova.coords[0] = x+1;
                        nova.coords[1] = y;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
			}
		}
	}
	else if (atual.orientacao == 1){
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, baixo*/
        for(int i = 0; i< size; i++){
            for (int k= 0; k<3; k++){
                /*se encontrarmos o par contrario da aresta numa posicao 0, como os triangulos estao na posicao 0 originalmente, é a aresta da esquerda
                para ligar a uma cena numa posicao par, se for igual à cena da esquerda, vai ter de rodar até à posicao 5*/
                if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
                    /*encontrou igual à esquerda da peça atual*/
                    int x = atual.coords[0];
                    int y = atual.coords[1];
                    peca nova = pecas[i];
                    /*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
                    if (k==0 && tabuleiro[x][y-1].used == 0){
                        /*aresta do lado esquerdo*/
                        nova.coords[0] = x;
                        nova.coords[1] = y-1;
                        nova.orientacao = 4;
                        nova.used = 1;
                        tabuleiro[x][y-1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
                    }
                    if (k == 1 && tabuleiro[x][y-1].used == 0){
                        /*aresta do lado direito*/
                        nova.coords[0] = x;
                        nova.coords[1] = y-1;
                        nova.orientacao = 0;
                        nova.used = 1;
                        tabuleiro[x][y-1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
                    }
                    else if(tabuleiro[x][y-1].used == 0){
                        /*aresta de cima*/
                        nova.coords[0] = x;
                        nova.coords[1] = y-1;
                        nova.orientacao = 2;
                        nova.used = 1;
                        tabuleiro[x][y-1] = nova;

                        return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
                    }
                }
                    /*se encontrarmos o par contrario da aresta numa posicao 1, como os triangulos estao na posicao 0 originalmente, é a aresta da direita
                    para ligar a uma cena numa posicao par, se for igual à cena da direita, vai ter de todar até à posicao 5*/
                else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
                    /*encontrou igual à direita da peça atual*/
                    int x = atual.coords[0];
                    int y = atual.coords[1];
                    peca nova = pecas[i];
                    /*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
                    if (k==0 && tabuleiro[x][y+1].used == 0){
                        /*aresta do lado esquerdo*/
                        nova.coords[0] = x;
                        nova.coords[1] = y+1;
                        nova.orientacao = 0;
                        nova.used = 1;
                        tabuleiro[x][y+1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
                    }
                    if (k == 1 && tabuleiro[x][y+1].used == 0){
                        /*aresta do lado direito */
                        nova.coords[0] = x;
                        nova.coords[1] = y+1;
                        nova.orientacao = 2;
                        nova.used = 1;
                        tabuleiro[x][y+1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
                    }
                    else if(tabuleiro[x][y+1].used ==0){
                        /*aresta de cima*/
                        nova.coords[0] = x;
                        nova.coords[1] = y+1;
                        nova.orientacao = 4;
                        nova.used = 1;
                        tabuleiro[x][y+1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
                    }
                }
                    /*se encontrarmos o par contrario da aresta numa posicao 2, como os triangulos estao na posicao 0 originalmente, é a aresta de baixo
                    para ligar a uma cena numa posicao par*/
                else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
                    /*encontrou igual à direita da peça atual*/
                    int x = atual.coords[0];
                    int y = atual.coords[1];
                    peca nova = pecas[i];
                    /*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
                    if (k==0 && tabuleiro[x-1][y].used == 0){
                        /*aresta do lado esquerdo*/
                        nova.coords[0] = x-1;
                        nova.coords[1] = y;
                        nova.orientacao = 2;
                        nova.used = 1;
                        tabuleiro[x+1][y] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
                    }
                    if (k == 1 && tabuleiro[x-1][y].used == 0){
                        /*aresta do lado direito*/
                        nova.coords[0] = x-1;
                        nova.coords[1] = y;
                        nova.orientacao = 4;
                        nova.used = 1;
                        tabuleiro[x+1][y] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
                    }
                    else if(tabuleiro[x-1][y].used == 0){
                        /*aresta de cima*/
                        nova.coords[0] = x-1;
                        nova.coords[1] = y;
                        nova.orientacao = 0;
                        nova.used = 1;
                        tabuleiro[x][y+1] = nova;
                        return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
                    }
                }
            }
        }
	}
	else if (atual.orientacao == 2){
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, baixo*/
		for(int i = 0; i< size; i++){
			for (int k= 0; k<3; k++){
				/*se encontrar o contrario da posicao 0 vai ter de ligar em cima porque esta peça está rodada 1 vez para a direita
				 * comparando com a cena original*/
				if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
					/*encontrou igual à esquerda da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x+1][y].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;

						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
					/*se encontrou igual ao contrario do lado direito original, vai ter de ligar do lado esquerdo*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado direito */
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y-1].used ==0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
					}
				}
					/*encontrou o contrario da aresta de cima , tem que ligar do lado direito agora*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y+1].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
			}
		}
	}
	else if (atual.orientacao == 3){
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, baixo*/
		for(int i = 0; i< size; i++){
			for (int k= 0; k<3; k++){
				/*peça está rodada 3 vezes para a direita, lado esquerdo é agora lado direito.
				 * nova peça se igual ao contrario da aresta 0 vai ligar do lado direito*/
				if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
					/*encontrou igual à esquerda da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 2;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y+1].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 4;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;

						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
					/*aresta do lado direito é agora a do lado esquerdo*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 4;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado direito */
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y-1].used ==0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 2;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
					}
				}
					/*aresta de cima é agora a aresta de baixo*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 2;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 4;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x-1][y].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
			}
		}
	}
	else if (atual.orientacao == 4){
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, baixo*/
		for(int i = 0; i< size; i++){
			for (int k= 0; k<3; k++){
				/*aresta da esquerda é agora aresta da direita*/
				if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
					/*encontrou igual à esquerda da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y+1].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;

						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
					/*aresta do lado direito é agora aresta de cima*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x+1][y].used == 0){
						/*aresta do lado direito */
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x+1][y].used ==0){
						/*aresta de cima*/
						nova.coords[0] = x+1;
						nova.coords[1] = y;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
					}
				}
					/*aresta de cima é agora aresta do lado esquerdo */
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y-1].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y-1].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y-1;
						nova.orientacao = 1;
						nova.used = 1;
						tabuleiro[x][y-1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
			}
		}
	}
	else if (atual.orientacao == 5){
		/*procurar candidatos nas posicoes adequadas. Procurar esquerda, direita, baixo*/
		for(int i = 0; i< size; i++){
			for (int k= 0; k<3; k++){
				/*aresta da esquerda é agora aresta de baixo */
				if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[0]) && pecas[i].used != 1){
					/*encontrou igual à esquerda da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 2;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 4;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x-1][y].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x-1][y] = nova;

						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
					/*aresta da direita é agora aresta da direita*/
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[1]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x][y+1].used == 0){
						/*aresta do lado direito */
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 3;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x][y+1].used ==0){
						/*aresta de cima*/
						nova.coords[0] = x;
						nova.coords[1] = y+1;
						nova.orientacao = 5;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0],pecas, size);
					}
				}
					/*aresta de cima é agora aresta da esquerda */
				else if (pecas[i].arestas[k] == reverse_aresta(atual.arestas[2]) && pecas[i].used != 1){
					/*encontrou igual à direita da peça atual*/
					int x = atual.coords[0];
					int y = atual.coords[1];
					peca nova = pecas[i];
					/*verificar a cena dos buracos em funcao da orientacao da peca atual, se é em cima ou em baixo. Posicoes das outras pecas sao sempre as mms*/
					if (k==0 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado esquerdo*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 4;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[0][1] + nova.arestas[0][0], pecas, size);
					}
					if (k == 1 && tabuleiro[x-1][y].used == 0){
						/*aresta do lado direito*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 0;
						nova.used = 1;
						tabuleiro[x+1][y] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[1][1] + nova.arestas[1][0], pecas, size);
					}
					else if(tabuleiro[x-1][y].used == 0){
						/*aresta de cima*/
						nova.coords[0] = x-1;
						nova.coords[1] = y;
						nova.orientacao = 2;
						nova.used = 1;
						tabuleiro[x][y+1] = nova;
						return search_connection(nova, tabuleiro, score + nova.arestas[2][1] + nova.arestas[2][0], pecas, size);
					}
				}
			}
		}
	}
	if(score > maxscore)
		maxscore = score;
	return score;
}
