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
#define HASH_TABLE_SIZE 10007

typedef struct node {
    int puzzle[3][3];
    int g, h, f;
    struct node *parent;
} Node;

typedef struct noOrd {
    Node *no;
    struct noOrd *next;
}noOrdenado;

typedef struct HashNode {
    unsigned int hashValue;    // Valor hash do estado
    struct HashNode* next;     // Encadeamento para colisões
} HashNode;

typedef struct {
    HashNode* buckets[HASH_TABLE_SIZE];
} HashSet;

void gerar(int *lista);
void print(int matriz[3][3]);
void sucessora(int movimento, int *i, int *j, int matriz[3][3]);
void menu_IA(int *escolha);
void menu_inicial(int *escolha);

void sucessoraIa(Node *current, int i_moves,int *zeroX, int *zeroY, int *newX, int *newY);
int avalia(int m_comparar[3][3]);
int heuristica(int atual[3][3]);
Node *criaNo(int puzzle[3][3], int g, int h, Node *parent);
int visitado(Node* atual, int puzzle[3][3]);
void imprimePilha (Pilha* p);
void aStar(int start[3][3]);
noOrdenado *sortedInsert(Node *addNo, noOrdenado *sorted);

HashSet* createHashSet();
unsigned int computeHash(int puzzle[3][3]);
void insertHash(HashSet* set, unsigned int hashValue);
int containsHash(HashSet* set, unsigned int hashValue);
void freeHashSet(HashSet* table);


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

//void sucessoraIa(Node *current, int i_moves,int *zeroX, int *zeroY, int *newX, int *newY){
//
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (current->puzzle[i][j] == 0) {
//                    *zeroX = i;
//                    *zeroY = j;
//                }
//            }
//        }
//
//         int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movimentos possíveis (cima, baixo, esquerda, direita)
//            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
//                *newX = *zeroX + moves[i_moves][0];
//                *newY = *zeroY + moves[i_moves][1];
//            }
//}

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

// Função para calcular a heurística (distância de Manhattan)
int heuristica(int atual[3][3]) {
    int distancia = 0;
    int objetivo[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (atual[i][j] != 0) { // Ignorar o espaço vazio
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        if (atual[i][j] == objetivo[x][y]) {
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


void imprimePilha (Pilha* p){
    No* q;
    for (q=p->Topo; q!=NULL; q=q->prox){
        print(q->puzzle);
        printf("\t\n\nPressione qualquer tecla para continuar...\n");
        getch();
        system("cls");
    }
}

noOrdenado *sortedInsert(Node *addNo, noOrdenado *sorted) {
    noOrdenado *createNode = NULL;
    createNode->no = addNo;
    createNode->next = NULL;
    // Special case for the head end
    if (sorted == NULL || sorted->no->f >= createNode->no->f) {
        createNode->next = sorted;
        sorted = createNode;
    }
    else {
        noOrdenado* curr = sorted;

        // Locate the node before the point of insertion
        while (curr->next != NULL && curr->next->no->f < createNode->no->f) {
            curr = curr->next;
        }
        createNode->next = curr->next;
        curr->next = createNode;
    }

    return sorted;
}

// Funções para o hashset

HashSet* createHashSet() {
    // Alocar memória para a tabela hash
    HashSet* table = (HashSet*)malloc(sizeof(HashSet));
    if (table == NULL) {
        printf("Erro ao alocar memória para a tabela hash.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar todos os buckets como NULL
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

unsigned int computeHash(int puzzle[3][3]) {
    unsigned int hash = 0;
    unsigned int prime = 31;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            hash = hash * prime + puzzle[i][j];
        }
    }
    return hash;
}

void insertHash(HashSet* set, unsigned int hashValue) {
    unsigned int index = hashValue % HASH_TABLE_SIZE;
    HashNode* current = set->buckets[index];

    // Verificar se o valor já existe
    while (current != NULL) {
        if (current->hashValue == hashValue) {
            return; // Hash já presente
        }
        current = current->next;
    }

    // Inserir nova hash
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->hashValue = hashValue;
    newNode->next = set->buckets[index];
    set->buckets[index] = newNode;
}

int containsHash(HashSet* set, unsigned int hashValue) {
    unsigned int index = hashValue % HASH_TABLE_SIZE;
    HashNode* current = set->buckets[index];

    while (current != NULL) {
        if (current->hashValue == hashValue) {
            return 1; // Hash encontrada
        }
        current = current->next;
    }
    return 0; // Hash não encontrada
}

void freeHashSet(HashSet* table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* current = table->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp); // Libera o nó
        }
    }
    free(table); // Libera a tabela hash
}


// Função principal A*
void aStar(int start[3][3]) {
    Node* inicioNo = criaNo(start, 0, heuristica(start), NULL);
    noOrdenado *head = NULL;
    head->no = inicioNo;
    head->next = NULL;

    HashSet* visitedStates = createHashSet();

    while (head->next != NULL) {
        int objetivo[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
        Node *atual = head->no;
        // Verificar se o estado atual é o estado objetivo
        if (memcmp(atual->puzzle, objetivo, sizeof(atual->puzzle)) == 0) {
            printf("Solução encontrada!\n");

            // Passo 1: Armazena os estados na ordem inversa (usando uma pilha)
            Pilha *p = CriaPilha();

            while (atual != NULL) {
                push(p, atual->puzzle); // Adiciona o nó atual à pilha
                atual = atual->parent; // Move para o nó pai
            }

            // Passo 2: Exibe os estados na ordem correta
            imprimePilha(p);
            libera(p);
            freeHashSet(visitedStates);
            return;
        }
        //Remove o nó atual
        head = head->next;
        // Inserir estado atual no hashset
        insertHash(visitedStates, computeHash(atual->puzzle));

        // Encontrar a posição do zero
        int zeroX, zeroY;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (atual->puzzle[i][j] == 0) {
                    zeroX = i;
                    zeroY = j;
                }
            }
        }
        int movimentos[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        // Gerar estados sucessores
        for (int i = 0; i < 4; i++) {
            int newX = zeroX + movimentos[i][0];
            int newY = zeroY + movimentos[i][1];

            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                int novoPuzzle[3][3];
                memcpy(novoPuzzle, atual->puzzle, sizeof(novoPuzzle));
                novoPuzzle[zeroX][zeroY] = novoPuzzle[newX][newY];
                novoPuzzle[newX][newY] = 0;

                if (!containsHash(visitedStates, novoPuzzle)) {
                    Node* novoNo = criaNo(novoPuzzle, atual->g + 1, heuristica(novoPuzzle), atual);
                    head = sortedInsert(novoNo, head);
                }
            }
        }
    }

    printf("Nenhuma solução encontrada.\n");
}
