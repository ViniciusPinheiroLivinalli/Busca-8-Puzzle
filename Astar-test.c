#include <stdio.h>
#include <stdlib.h>
#include "pilhaA.h"


typedef struct nod {
    int puzzle[3][3]; //estado
    int g; // Custo do caminho até agora
    int h; // Valor da heurística
    int f; // Custo total (f = g + h)
    struct nod* parent; // Ponteiro para o estado pai
} Node;

void print(int matriz[3][3]){
    for(int i=0; i<3; i++)
    {
        printf("\n\n");
        for(int j=0; j<3; j++)
        {
            if(matriz[i][j] == 0){
                printf("\t_\t");
            }else{
                printf("\t%d\t",matriz[i][j]);
            }
        }
    }
    return;
}

void imprimePilha (Pilha* p){
    No* q;
    if(!p){
        printf("\n\n\tPILHA VAZIA!!!!\n\n");
        printf("\n\n\tPILHA VAZIA!!!!\n\n");
    } else{
        printf("\n\n\tImpress o da Pilha: ");
        for (q=p->Topo; q!=NULL; q=q->prox){
            print(q->puzzle);
        }
        printf("\n\n");
    }
}

Node* criaNo(int puzzle[3][3], int g, int h, Node* parent) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    memcpy(novoNo->puzzle, puzzle, sizeof(novoNo->puzzle));
    novoNo->g = g;
    novoNo->h = h;
    novoNo->f = g + h;
    novoNo->parent = parent;
    return novoNo;
}


int main(){

    int ex[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    Node *teste = criaNo(ex, 0, 0, NULL);
    Pilha*p = CriaPilha();
    push(p, teste->puzzle);
    push(p, teste->puzzle);
    push(p, teste->puzzle);

    imprimePilha(p);

//    while (atual != NULL) {
//        print(atual->puzzle);
//        atual = atual->parent;
//    }
    return 0;
}


