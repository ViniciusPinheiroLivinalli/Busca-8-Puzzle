#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROFUNDIDADE 100

typedef struct {
    int tabuleiro[3][3];
    int profundidade;
    int pos_vazio_i;
    int pos_vazio_j;
} Estado;

typedef struct No {
    Estado estado;
    struct No* proximo;
} No;

typedef struct {
    No* topo;
} Pilha;

// Movimentos possíveis: cima, baixo, esquerda, direita
const int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void inicializarPilha(Pilha* p) {
    p->topo = NULL;
}

void empilhar(Pilha* p, Estado estado) {
    No* novo = (No*)malloc(sizeof(No));
    novo->estado = estado;
    novo->proximo = p->topo;
    p->topo = novo;
}

Estado desempilhar(Pilha* p) {
    Estado estado = p->topo->estado;
    No* temp = p->topo;
    p->topo = p->topo->proximo;
    free(temp);
    return estado;
}

int pilhaVazia(Pilha* p) {
    return p->topo == NULL;
}

int estadoFinal(Estado* estado) {
    int objetivo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(estado->tabuleiro[i][j] != objetivo[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int movimentoValido(int i, int j) {
    return i >= 0 && i < 3 && j >= 0 && j < 3;
}

int IDFS(Estado estadoInicial) {
    for(int limite = 0; limite < MAX_PROFUNDIDADE; limite++) {
        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, estadoInicial);

        while(!pilhaVazia(&pilha)) {
            Estado atual = desempilhar(&pilha);

            if(estadoFinal(&atual)) {
                printf("Solução encontrada na profundidade %d\n", atual.profundidade);
                return 1;
            }

            if(atual.profundidade < limite) {
                for(int m = 0; m < 4; m++) {
                    int novo_i = atual.pos_vazio_i + movimentos[m][0];
                    int novo_j = atual.pos_vazio_j + movimentos[m][1];

                    if(movimentoValido(novo_i, novo_j)) {
                        Estado novo = atual;
                        novo.profundidade++;

                        // Realizar movimento
                        novo.tabuleiro[atual.pos_vazio_i][atual.pos_vazio_j] =
                            atual.tabuleiro[novo_i][novo_j];
                        novo.tabuleiro[novo_i][novo_j] = 0;
                        novo.pos_vazio_i = novo_i;
                        novo.pos_vazio_j = novo_j;

                        empilhar(&pilha, novo);
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    Estado inicial = {
        .tabuleiro = {{1,2,3},{4,0,6},{7,5,8}},
        .profundidade = 0,
        .pos_vazio_i = 1,
        .pos_vazio_j = 1
    };

    if(!IDFS(inicial)) {
        printf("Sem solução encontrada\n");
    }
    return 0;
}
