#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct noa
{
    int puzzle[3][3];
    struct noa *prox;
}NoA;

typedef struct pilhaa
{
   NoA *Topo;
}PilhaA;

PilhaA* CriaPilhaA (void)
{
     PilhaA *p;
     p=(PilhaA*)malloc(sizeof(PilhaA));
     p->Topo = NULL;
   return p;
};

NoA* ins_ini (NoA* t, int addedPuzzle[3][3])
{
    NoA* aux = (NoA*) malloc(sizeof(NoA));
    memcpy(aux->puzzle, addedPuzzle, sizeof(aux->puzzle));
    aux->prox = t;
    return aux;
};

void push (PilhaA* p, int addedPuzzle[3][3])
{
    p->Topo = ins_ini(p->Topo,addedPuzzle);
};

PilhaA * liberaA (PilhaA* p)
{
    NoA *q = p->Topo;
    while (q!=NULL)
    {
        NoA* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return(NULL);
};


#endif // PILHA_H_INCLUDED
