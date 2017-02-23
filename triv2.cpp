#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <stdexcept>
#include <iostream>
#include <utility>

typedef struct Peca {
	int arestas[3][3];
	int orientacao;
	int coords[2];
  std::vector<Peca> matches;
	std::vector<std::pair<int,int> > matches_arestas;
	int used;
} Peca;

int maxscore = 0;
int repetidos = 0;
std::vector<Peca> jogadas;

void get_matches(std::vector<Peca>* pecas, int x);
int input(std::vector<Peca>* pecas);
void default_peca(Peca* p);

int main(){
	std::vector<Peca> pecas;
	int i;
	Peca p;
	default_peca(&p);
	for(i=0;i<20;i++){
		pecas.push_back(p);
	}
	int size = input(&pecas);
	if (size == 0) {
		return 1;
	}

	Peca **tabuleiro = (Peca**) calloc(2*size+1, sizeof(Peca*));
	for(i=0;i<2*size+1;i++) {
		tabuleiro[i] = (Peca*) calloc(2*size+1, sizeof(Peca));
	}
	for(int j=0;j<size;j++) {
		get_matches(&pecas, j);
	}

	for(i=0;i<size;i++) {
		pecas.at(i).coords[0] = size;
		pecas.at(i).coords[1] = size;
		pecas.at(i).orientacao = 0;
		pecas.at(i).used = 1;
		tabuleiro[size][size] = pecas.at(i);
		jogadas.push_back(pecas.at(i));
		//play(tabuleiro, pecas, 0, size);
		jogadas.clear();
	}

	printf("%d\n",maxscore);
	return 0;
}
/*
void play(Peca** tabuleiro, std::vector<Peca>* pecas, int score, int size){
	for(int i=0; i<jogadas.size(); i++){
		for(int j=0; j<size; j++){
			if(pecas->at(j).used != 1){
				for(int k=0; k<jogadas->at(i).matches.size(); k++){
					//Peca for igual
					if(jogadas->at(i).matches->at(k).arestas[0][0] == pecas->at(j).arestas[0][0] && jogadas->at(i).matches->at(k).arestas[1][0] == pecas->at(j).arestas[1][0] && jogadas->at(i).matches->at(k).arestas[2][0] == pecas->at(j).arestas[2][0]){
						if(jogadas->at(i).orientacao == 0){
							if(jogadas->at(i).matches_arestas->first == 0){
								if(jogadas->at(i).matches_arestas->last == 0){

								}
							}
						}
						if(jogadas->at(i).orientacao == 1){

						}
						if(jogadas->at(i).orientacao == 2){

						}
						if(jogadas->at(i).orientacao == 3){

						}
						if(jogadas->at(i).orientacao == 4){

						}
						if(jogadas->at(i).orientacao == 5){

						}
					}
				}
			}
		}
	}
}
*/
void get_matches(std::vector<Peca>* pecas, int x){
	int pos=x;
	bool find = false;
	int yolo = 0;
	for(int i=0;i<pecas->size();i++){
		printf("\n");
		find = false;
		if(i!=pos){
			//printf("\n%d\n",pecas->at(i).arestas[0][0]);
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					if(pecas->at(pos).arestas[j][0] == pecas->at(i).arestas[k][1] && pecas->at(pos).arestas[j][1] == pecas->at(i).arestas[k][0]){
						yolo++;
						if(!find){
							printf("Atual: [%d, %d, %d]-> Match: [%d, %d, %d]\n", pecas->at(pos).arestas[0][0], pecas->at(pos).arestas[1][0], pecas->at(pos).arestas[2][0], pecas->at(i).arestas[0][0], pecas->at(i).arestas[1][0], pecas->at(i).arestas[2][0]);
							pecas->at(pos).matches.push_back(pecas->at(i));
							//GUARDA ARESTAS QUE DÃO MATCH
							//J = ARESTA PECA ATUAL
							//K = ARESTA MATCH
							find = true;
						}
							pecas->at(pos).matches_arestas.push_back(std::make_pair(j,k));
							printf("Aresta peca atual: %d\n",pecas->at(pos).matches_arestas.at(yolo-1).first);
							printf("Aresta peca match: %d\n",pecas->at(pos).matches_arestas.at(yolo-1).second);
					}
				}
			}
		}
	}
}

void reset_peca(std::vector<Peca>* pecas, int i) {
	int j;
	pecas->at(i).used = 0;
	for(j=0;j<3;j++) {
		pecas->at(i).arestas[j][2] = 0;
	}
	pecas->at(i).coords[0] = -1; pecas->at(i).coords[1] = -1;
	pecas->at(i).orientacao = 0;
}

int input(std::vector<Peca>* pecas) {
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
		pecas->at(i).arestas[0][0] = v1;
		pecas->at(i).arestas[0][1] = v2;
		pecas->at(i).arestas[1][0] = v2;
		pecas->at(i).arestas[1][1] = v3;
		pecas->at(i).arestas[2][0] = v3;
		pecas->at(i).arestas[2][1] = v1;

		pecas->at(i).arestas[0][2] = 0;
		pecas->at(i).arestas[1][2] = 0;
		pecas->at(i).arestas[2][2] = 0;

		pecas->at(i).coords[0] = -1;
		pecas->at(i).coords[1] = -1;

		pecas->at(i).used = 0;
		pecas->at(i).orientacao = 0;
		i++;

	}
	return i;
}

void default_peca(Peca* p) {
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
