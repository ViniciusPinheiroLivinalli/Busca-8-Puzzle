#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#include "pilhaA.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

typedef struct node{
    int puzzle[3][3]; //estado
    int g; // Custo do caminho até agora
    int h; // Valor da heurística
    int f; // Custo total (f = g + h)
    struct node *parent; // Ponteiro para o estado pai
} Node;

void gerar(int *lista);
void print(int matriz[3][3]);
void sucessora(int movimento, int *i, int *j, int matriz[3][3]);
void sucessoraIa(Node *current, int i_moves,int *zeroX, int *zeroY, int *newX, int *newY);
int avalia(int m_comparar[3][3]);
int heuristica(int atual[3][3]);
Node *criaNo(int puzzle[3][3], int g, int h, Node *parent);
int visitado(Node* atual, int puzzle[3][3]);
void imprimePilha (Pilha* p);

int main(){
    int jogar = 1;
    char resp;
    while(jogar == 1){

        setlocale(LC_ALL,"portuguese");

        int tela[9], pos1 = 0, pos2 = 0, tecla;
        char tela2[9];
        gerar(tela);
        int retorno = 0, escolha, escolhaIA;
        int m[3][3], pos = 0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                m[i][j] = tela[pos];
                pos++;
                }
            }

        for(int x = 0; x < 3; x++){
            for(int y = 0; y < 3; y++){
                if(m[x][y] == 0){
                    pos1 = x;
                    pos2 = y;
                }
            }
        }

        system("color 9F");
        printf("\n\n\n\n\n");
        printf("\t\t\t  **********************************\n");
        printf("\t\t\t  *          8-PUZZLE GAME         *\n");
        printf("\t\t\t  **********************************\n");
        printf("\n");

        printf("\n");
        printf("\t\tO objetivo do 8-Puzzle � organizar os n�meros de 1 a 8\n");
        printf("\t\tem ordem crescente, com o espa�o vazio no �ltimo lugar.\n");
        printf("\t\tVoc� pode mover o espa�o vazio aos blocos adjacentes.\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n");
        system("pause");
        system("cls");

        menu_inicial(&escolha);
        if(escolha == 1){
            while(retorno!= 1){
                printf("\n\n\n\n\n");
                print(m);
                printf("\n\n\n\n");
                printf("\t\t  i = %d | j = %d", pos1 + 1, pos2 + 1);
                tecla = getch();
                sucessora(tecla, &pos1, &pos2, m);
                retorno = avalia(m);
                system("cls");
            }
        }else{
            if(escolha == 2){
                menu_IA(&escolhaIA);
            }
            if(escolhaIA == 1){
                //A*

                aStar(m);
            }
            else if(escolhaIA ==2){
                //DFS iterativa
            }
        }
        printf("\n\nParab�ns voc� conseguiu encontrar a solu��o!!\n\n\n\n\n\n\n\n\n");
        system("pause");
        system("cls");
        printf("Deseja jogar novamente? <S/N> ");
        fflush(stdin);
        resp = getchar();
        if(toupper(resp) == 'N'){
            jogar = 0;
        }
    }
    return 0;
}

void imprimePilha (Pilha* p){
    No* q;
    for (q=p->Topo; q!=NULL; q=q->prox){
        print(q->puzzle);
    }
};

void gerar(int *lista){

    int valor = 0;
    srand(time(NULL));
    while (valor != 1){

        int i, j, temp;
        for (i = 0; i < 9; i++) {
            lista[i] = i;
        }
        for (i = 8; i > 0; i--) {
            j = rand() % (i + 1);
            temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp;
        }

        int inv = 0;
        for(int i = 0; i < 8; i++)
        {
            for(int j = i + 1; j < 9; j++ )
            {
                if(lista[i] > lista[j] && lista[i] != 0 && lista[j] != 0) //Se houverem invers�es de posi��o (Um valor maior que o outro na lista) e diferente de 0 (Zero � o vazio):
                {
                    inv++;
                }
            }
        }


        for(int i = 0; i < 9; i++){
            if(lista[i] == 0){
                if((i+1) % 2 == 0 && inv % 2 == 0){ //Verifico se a posi��o inicial do vazio � par e se o n�mero de invers�es tamb�m �
                    valor = 1;
                }
            }

        }

    }
}

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

void sucessora(int movimento, int *i, int *j, int matriz[3][3]){// adicionar matriz como parametro e c�pia
    int aux_valor, aux_i, aux_j;
    aux_i = *i; //guardando a posi��o inicial do vazio
    aux_j = *j;

    if (movimento == KEY_UP && (*i) > 0) { //fazendo a verifica��o e alterando a posi��o
        (*i)--;
    }
    else if (movimento == KEY_DOWN && (*i) < 2) {
        (*i)++;
    }
    else if (movimento == KEY_RIGHT && (*j) < 2) {
        (*j)++;
    }
    else if (movimento == KEY_LEFT && (*j) > 0) {
        (*j)--;
    }
    else {
        return; // se n�o for v�lido
    }

    aux_valor = matriz[*i][*j]; //guardando o valor que o vazio vai ocupar futuramente
    matriz[*i][*j] = 0; //definindo a nova posi��o como vazio
    matriz[aux_i][aux_j] = aux_valor; //definindo a posi��o antiga do vazio com o novo valor
}

void sucessoraIa(Node *current, int i_moves,int *zeroX, int *zeroY, int *newX, int *newY){

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (current->puzzle[i][j] == 0) {
                    *zeroX = i;
                    *zeroY = j;
                }
            }
        }

         int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movimentos possíveis (cima, baixo, esquerda, direita)
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                *newX = *zeroX + moves[i_moves][0];
                *newY = *zeroY + moves[i_moves][1];
            }
}

int avalia(int m_comparar[3][3]){
    int v_procurado[3][3] = {{1,2,3},{4,5,6},{7,8,0}}, sum = 0; // usar soma pra verificar quantos numeros est�o em uma posi��o correta

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(v_procurado[i][j] == m_comparar[i][j]){
                sum++;
            }
        }
    }
    if (sum == 9){
            return 1; // caso a soma seja 9, todos os valores est�o na posi��o correta, a solu��o foi encontrada
    } else {
        return 0; // caso o vetor atual nao seja igual ao objetivo, ele retorna 0, ou seja, a solu��o n�o foi encontrada
    }
}

void menu_inicial(int *escolha){
    int tecla = 0;
    *escolha = 1;

    while (1) {
        system("cls");

        printf("\n\n\n\t\t\t   *******************     8 Puzzle   ********************\n");
        printf("\t\t\t   *                  | Selecione um Op��o |                  *\n");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   * %s 8 Puzzle Manual                                       *\n", (*escolha == 1) ? "->" : "  ");
        printf("\t\t\t   * %s 8 Puzzle com Intelig�ncia Artificial                  *\n", (*escolha == 2) ? "->" : "  ");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   ************************************************************\n");

        tecla = getch();

        //NAVEGA��O
        if (tecla == KEY_UP) {
            if (*escolha > 1) (*escolha)--;
        } else if (tecla == KEY_DOWN) {
            if (*escolha < 2) (*escolha)++;
        } else if (tecla == 27 || tecla == 13) {
            system("cls");
            return;
        }
    }
}

void menu_IA(int *escolha){
    int tecla = 0;
    *escolha = 1;

    while (1) {
        system("cls");

        printf("\n\n\n\t\t\t   *******************     8 Puzzle   ********************\n");
        printf("\t\t\t   *                  | Selecione a busca |                   *\n");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   * %s Algoritmo de A*                                       *\n", (*escolha == 1) ? "->" : "  ");
        printf("\t\t\t   * %s Algoritmo de Busca em Profundidade Iterativa          *\n", (*escolha == 2) ? "->" : "  ");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   ************************************************************\n");

        tecla = getch();

        //NAVEGA��O
        if (tecla == KEY_UP) {
            if (*escolha > 1) (*escolha)--;
        } else if (tecla == KEY_DOWN) {
            if (*escolha < 2) (*escolha)++;
        } else if (tecla == 27 || tecla == 13) {
            system("cls");
            return;
        }
    }
}

int heuristica(int atual[3][3]){
    int distancia = 0;
    int m_objetivo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (atual[i][j] != 0) { // Ignorar o espaço vazio
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (atual[i][j] == m_objetivo[x][y]) {
                            distancia += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return distancia;
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

int visitado(Node* atual, int puzzle[3][3]) {
    while (atual != NULL) {
        if (memcmp(atual->puzzle, puzzle, sizeof(atual->puzzle)) == 0) {
            return 1;
        }
        atual = atual->parent;
    }
    return 0;
}


void aStar(int start[3][3]) {
    int m_objetivo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};

    Node* openList[1000]; // Lista de nós a serem explorados
    int openCount = 0;

    Node* inicioNo = criaNo(start, 0, heuristica(start), NULL);
    openList[openCount++] = inicioNo;
    int *zeroX, *zeroY, *newX, *newY, newPuzzle[3][3];

    while (openCount > 0) {
        // Encontrar o nó com menor f na openList
        int minIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i]->f < openList[minIndex]->f) {
                minIndex = i;
            }
        }

        Node *atual = openList[minIndex];

        // Verificar se o objetivo foi alcançado
        if (avalia(atual->puzzle)) {
            Pilha *p = CriaPilha;
            printf("Solução encontrada!\n");

            while (atual != NULL) {
                push(p, atual->puzzle);
                atual = atual->parent;
            }
            imprimePilha(p);

            libera(p);
            return;
        }

        // Remover o nó atual da openList
        for (int i = minIndex; i < openCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openCount--;
        memcpy(atual->puzzle, newPuzzle, sizeof(newPuzzle));
        for (int i = 0; i < 4; i++) {
                sucessoraIa(atual, i, zeroX, zeroY, newX, newY);
                newPuzzle[*zeroX][*zeroY] = newPuzzle[*newX][*newY];
                newPuzzle[*newX][*newY] = 0;

                if (visitado(atual, newPuzzle) != 1) {
                    Node* successor = criaNo(newPuzzle, atual->g + 1, heuristica(newPuzzle), atual);
                    openList[openCount++] = successor;
                }
            }
        }
       printf("Nenhuma solução encontrada.\n");
    }


