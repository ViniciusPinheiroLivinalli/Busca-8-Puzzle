#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000000
#define PROFUNDIDADE_MAXIMA 31

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
    if (p->topo == NULL) {
        Estado vazio = {{0}};
        return vazio;
    }
    Estado estado = p->topo->estado;
    No* temp = p->topo;
    p->topo = p->topo->proximo;
    free(temp);
    return estado;
}

int pilhaVazia(Pilha* p) {
    return p->topo == NULL;
}

int movimentoValido(int i, int j) {
    return i >= 0 && i < 3 && j >= 0 && j < 3;
}

// Função para verificar se chegou ao estado objetivo
int avalia(int tabuleiro[3][3]) {
    int objetivo[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(tabuleiro[i][j] != objetivo[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void print(int matriz[3][3]) {
    for(int i = 0; i < 3; i++) {
        printf("\n");
        for(int j = 0; j < 3; j++) {
            if(matriz[i][j] == 0)
                printf(" _ ");
            else
                printf(" %d ", matriz[i][j]);
        }
    }
    printf("\n");
}

int hash_estado(int tabuleiro[3][3]) {
    int hash = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            hash = hash * 10 + tabuleiro[i][j];
        }
    }
    return hash;
}

int BuscaProfundidadeIterativa(Estado inicial) {
    int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    char* direcoes[4] = {"CIMA", "BAIXO", "ESQUERDA", "DIREITA"};

    for (int limite = 0; limite <= PROFUNDIDADE_MAXIMA; limite++) {
        printf("\n=== Iniciando busca com profundidade %d ===\n", limite);

        int* estados_visitados = (int*)calloc(HASH_SIZE, sizeof(int));
        if (!estados_visitados) {
            printf("Erro de alocação de memória!\n");
            return -1;
        }

        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, inicial);

        int movimentos_explorados = 0;

        while (!pilhaVazia(&pilha)) {
            Estado atual = desempilhar(&pilha);
            movimentos_explorados++;

            printf("\nEstado atual (Prof: %d):\n", atual.profundidade);
            print(atual.tabuleiro);

            if (avalia(atual.tabuleiro)) {
                printf("\nSolução encontrada!\n");
                printf("Profundidade: %d\n", atual.profundidade);
                printf("Estados explorados: %d\n", movimentos_explorados);
                free(estados_visitados);
                return 1;
            }

            if (atual.profundidade < limite) {
                for (int m = 3; m >= 0; m--) {
                    int novo_i = atual.pos_vazio_i + movimentos[m][0];
                    int novo_j = atual.pos_vazio_j + movimentos[m][1];

                    if (movimentoValido(novo_i, novo_j)) {
                        Estado novo = atual;
                        novo.profundidade++;

                        // Realiza o movimento
                        novo.tabuleiro[atual.pos_vazio_i][atual.pos_vazio_j] =
                            novo.tabuleiro[novo_i][novo_j];
                        novo.tabuleiro[novo_i][novo_j] = 0;
                        novo.pos_vazio_i = novo_i;
                        novo.pos_vazio_j = novo_j;

                        int hash = hash_estado(novo.tabuleiro) % HASH_SIZE;
                        if (!estados_visitados[hash]) {
                            estados_visitados[hash] = 1;
                            empilhar(&pilha, novo);

                            printf("Movimento: %s\n", direcoes[m]);
                            print(novo.tabuleiro);
                        }
                    }
                }
            }
        }

        free(estados_visitados);
        printf("\nNão encontrou solução na profundidade %d\n", limite);
    }
    return 0;
}

int main() {
    Estado inicial = {
        .tabuleiro = {
            {1, 2, 3},
            {4, 0, 5},
            {7, 8, 6}
        },
        .profundidade = 0,
        .pos_vazio_i = 1,
        .pos_vazio_j = 1
    };

    printf("Estado inicial:\n");
    print(inicial.tabuleiro);

    int resultado = BuscaProfundidadeIterativa(inicial);

    if (resultado == 1) {
        printf("\nBusca concluída com sucesso!\n");
    } else if (resultado == 0) {
        printf("\nNão foi possível encontrar uma solução.\n");
    } else {
        printf("\nErro durante a busca.\n");
    }

    return 0;
}
