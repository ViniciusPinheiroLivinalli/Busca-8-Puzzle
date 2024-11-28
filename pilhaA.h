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


#endif // PILHA_H_INCLUDED
