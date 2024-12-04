#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct no
{
    int puzzle[3][3];
    struct no *prox;
}No;

typedef struct pilha
{
   No *Topo;
}Pilha;

Pilha* CriaPilha (void)
{
     Pilha *p;
     p=(Pilha*)malloc(sizeof(Pilha));
     p->Topo = NULL;
   return p;
};

No* ins_ini (No* t, int addedPuzzle[3][3])
{
    No* aux = (No*) malloc(sizeof(No));
    memcpy(aux->puzzle, addedPuzzle, sizeof(aux->puzzle));
    aux->prox = t;
    return aux;
};

void push (Pilha* p, int addedPuzzle[3][3])
{
    p->Topo = ins_ini(p->Topo,addedPuzzle);
};

No* ret_ini (No* l)
{
    No* p = l->prox;
    free(l);
    return p;
};


void pop(Pilha* p) {
    if (p == NULL || p->Topo == NULL) {
        exit(1); // Aborta o programa em caso de pilha vazia
    }
//    memcpy(removedPuzzle, p->Topo->puzzle, sizeof(p->Topo->puzzle));
    p->Topo = ret_ini(p->Topo);
}

//void imprimePilha (Pilha* p){
//    No* q;
//    if(!p){
//        printf("\n\n\tPILHA VAZIA!!!!\n\n");
//        printf("\n\n\tPILHA VAZIA!!!!\n\n");
//    } else{
//        printf("\n\n\tImpress o da Pilha: ");
//        for (q=p->Topo; q!=NULL; q=q->prox){
//            printf("% 2d",q->info);
//        }
//        printf("\n\n");
//    }
//}


Pilha * libera (Pilha* p)
{
    No *q = p->Topo;
    while (q!=NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return(NULL);
};

int vaziaPilha(Pilha *p)
{
    if (p->Topo==NULL)
    {
        return 1; //pilha vazia
    }
    return 0;
}

//// Verificar se o objetivo foi alcançado
//        if (memcmp(atual->puzzle, objetivo, sizeof(atual->puzzle)) == 0) {
//            printf("Solução encontrada!\n");
//
//            // Passo 1: Armazena os estados na ordem inversa (usando uma pilha)
//            Pilha *P=NULL;
//            P = CriaPilha(); // Criando pilha
//            int contTopo = 0;
//
//            while (atual != NULL) {
//                push(P,atual); // Adiciona o nó atual à pilha
//                atual = atual->parent; // Move para o nó pai
//            }
//
//            // Passo 2: Exibe os estados na ordem correta (desempilha e exibe)
//            while (!vaziaPilha(P)) {
//                system("cls"); // Limpa a tela
//                printf("Estado atual:\n");
//                imprimePilha(P);
//                pop(P);
//                printf("\n\n");
//            }


//void pop(Pilha* p) {
//    if (p == NULL || p->Topo == NULL) {
//        exit(1); // Aborta o programa em caso de pilha vazia
//    }
////    memcpy(removedPuzzle, p->Topo->puzzle, sizeof(p->Topo->puzzle));
//    p->Topo = ret_ini(p->Topo);
//}
//
//
//Pilha * libera (Pilha* p)
//{
//    No *q = p->Topo;
//    while (q!=NULL)
//    {
//        No* t = q->prox;
//        free(q);
//        q = t;
//    }
//    free(p);
//    return(NULL);
//};
//
//int vaziaPilha(Pilha *p)
//{
//    if (p->Topo==NULL)
//    {
//        return 1; //pilha vazia
//    }
//    return 0;
//}


#endif // PILHA_H_INCLUDED
