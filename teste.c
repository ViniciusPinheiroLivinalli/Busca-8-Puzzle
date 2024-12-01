#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3 // Tamanho do tabuleiro (3x3)
#define PROFUNDIDADE_MAX 15 // Limite máximo de profundidade

// Estrutura para armazenar o estado do tabuleiro
typedef struct {
    int tabuleiro[N][N];
    int profundidade;
    int pos_vazio_i;
    int pos_vazio_j;
} Estado;

// Funções auxiliares
void printTabuleiro(int tabuleiro[N][N]);
bool compararTabuleiros(int tabuleiro1[N][N], int tabuleiro2[N][N]);
bool estadoFinal(int tabuleiro[N][N]);
void moverEspacoVazio(int* i, int* j, int movimento);
bool movimentoValido(int i, int j);
void copiarTabuleiro(int destino[N][N], int origem[N][N]);

// Função DFS Iterativa
bool dfsIterativa(Estado inicial);

// Função principal
int main() {
    Estado inicial = {
        .tabuleiro = {{1, 2, 7}, {6, 4, 8}, {0, 3, 5}}, // Tabuleiro inicial
        .profundidade = 0,
        .pos_vazio_i = 2, // Posição do vazio (0)
        .pos_vazio_j = 2
    };

    if (dfsIterativa(inicial)) {
        printf("Solução encontrada!\n");
    } else {
        printf("Não foi possível encontrar uma solução.\n");
    }

    return 0;
}

// Função para imprimir o tabuleiro
void printTabuleiro(int tabuleiro[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" _ ");
            } else {
                printf(" %d ", tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para comparar dois tabuleiros
bool compararTabuleiros(int tabuleiro1[N][N], int tabuleiro2[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabuleiro1[i][j] != tabuleiro2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Função para verificar se o tabuleiro está no estado final
bool estadoFinal(int tabuleiro[N][N]) {
    int objetivo[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    return compararTabuleiros(tabuleiro, objetivo);
}

// Função para mover o espaço vazio no tabuleiro
void moverEspacoVazio(int* i, int* j, int movimento) {
    int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right
    *i += movimentos[movimento][0];
    *j += movimentos[movimento][1];
}

// Função para verificar se o movimento é válido
bool movimentoValido(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < N;
}

// Função para copiar o tabuleiro de um estado para outro
void copiarTabuleiro(int destino[N][N], int origem[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            destino[i][j] = origem[i][j];
        }
    }
}

// Função DFS Iterativa
bool dfsIterativa(Estado inicial) {
    Estado pilha[PROFUNDIDADE_MAX];
    int topo = -1;

    for (int limite = 0; limite < PROFUNDIDADE_MAX; limite++) {
        pilha[++topo] = inicial;

        while (topo >= 0) {
            Estado atual = pilha[topo--];

            // Verifica se encontrou a solução
            if (estadoFinal(atual.tabuleiro)) {
                printTabuleiro(atual.tabuleiro);
                return true;
            }

            if (atual.profundidade < limite) {
                int movimentos[4] = {0, 1, 2, 3}; // Up, Down, Left, Right

                for (int i = 0; i < 4; i++) {
                    int nova_i = atual.pos_vazio_i;
                    int nova_j = atual.pos_vazio_j;

                    // Copia o tabuleiro para o novo estado
                    Estado novoEstado;
                    copiarTabuleiro(novoEstado.tabuleiro, atual.tabuleiro);

                    moverEspacoVazio(&nova_i, &nova_j, movimentos[i]);

                    // Verifica se o movimento é válido
                    if (movimentoValido(nova_i, nova_j)) {
                        // Troca a posição do vazio com o número correspondente
                        novoEstado.tabuleiro[atual.pos_vazio_i][atual.pos_vazio_j] = novoEstado.tabuleiro[nova_i][nova_j];
                        novoEstado.tabuleiro[nova_i][nova_j] = 0;

                        novoEstado.pos_vazio_i = nova_i;
                        novoEstado.pos_vazio_j = nova_j;
                        novoEstado.profundidade = atual.profundidade + 1;

                        pilha[++topo] = novoEstado;
                        printTabuleiro(novoEstado.tabuleiro);
                        system("pause");
                        system("cls");
                    }
                }
            }
        }
    }

    return false; // Caso não encontre a solução dentro do limite de profundidade
}
