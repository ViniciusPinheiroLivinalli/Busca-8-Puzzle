#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

typedef struct {
    int puzzle[3][3]; //estado
    int g; // Custo do caminho até agora
    int h; // Valor da heurística
    int f; // Custo total (f = g + h)
    struct No* parent; // Ponteiro para o estado pai
} No;


void gerar(int *lista);
void print(int matriz[3][3]);
void sucessora(int movimento, int *i, int *j, int matriz[3][3]);
int avalia(int m_comparar[3][3]);
int heuristica(int atual[3][3]);
No* criaNo(int puzzle[3][3], int g, int h, No* parent);
int visitado(No* atual, int puzzle[3][3]);

int main(){
    int jogar = 1;
    char resp;
    int v_procurado[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    while(jogar == 1){

        setlocale(LC_ALL,"portuguese");

        int tela[9], pos1 = 0, pos2 = 0, tecla;
        char tela2[9];
        gerar(tela);
        int retorno = 0;
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
            printf("\t\tO objetivo do 8-Puzzle é organizar os números de 1 a 8\n");
            printf("\t\tem ordem crescente, com o espaço vazio no último lugar.\n");
            printf("\t\tVocê pode mover o espaço vazio aos blocos adjacentes.\n");
            printf("\n");
            //sleep(5);
            system("cls");

        while(retorno!= 1){


            printf("\n\n\n\n\n");
            print(m);
            printf("\n\n\n\n");
            printf("\t\t  i = %d | j = %d", pos1 + 1, pos2 + 1);
            tecla = getch();

            if(tecla == 224){
                tecla = getch();
                // switch redundante
                switch(tecla){
                case 72:
                    tecla = KEY_UP;
                    break;
                case 80:
                    tecla = KEY_DOWN;
                    break;
                case 75:
                    tecla = KEY_LEFT;
                    break;
                case 77:
                    tecla = KEY_RIGHT;
                    break;
                }
            }else if(tecla == 27){
                printf("esc");
                break;
            }


            sucessora(tecla, &pos1, &pos2, m);
            retorno = avalia(m);
            system("cls");
        }
        printf("Parabéns você conseguiu encontrar a solução!!");
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
                if(lista[i] > lista[j] && lista[i] != 0 && lista[j] != 0) //Se houverem inversões de posição (Um valor maior que o outro na lista) e diferente de 0 (Zero é o vazio):
                {
                    inv++;
                }
            }
        }


        for(int i = 0; i < 9; i++){
            if(lista[i] == 0){
                if((i+1) % 2 == 0 && inv % 2 == 0){ //Verifico se a posição inicial do vazio é par e se o número de inversões também é
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

void sucessora(int movimento, int *i, int *j, int matriz[3][3]){// adicionar matriz como parametro e cópia
    int aux_valor, aux_i, aux_j;
    aux_i = *i; //guardando a posição inicial do vazio
    aux_j = *j;

    if (movimento == KEY_UP && (*i) > 0) { //fazendo a verificação e alterando a posição
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
        return; // se não for válido
    }

    aux_valor = matriz[*i][*j]; //guardando o valor que o vazio vai ocupar futuramente
    matriz[*i][*j] = 0; //definindo a nova posição como vazio
    matriz[aux_i][aux_j] = aux_valor; //definindo a posição antiga do vazio com o novo valor
}

int avalia(int m_comparar[3][3]){
    int v_procurado[3][3] = {{1,2,3},{4,5,6},{7,8,0}}, sum = 0; // usar soma pra verificar quantos numeros estão em uma posição correta

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(v_procurado[i][j] == m_comparar[i][j]){
                sum++;
            }
        }
    }
    if (sum == 9){
            return 1; // caso a soma seja 9, todos os valores estão na posição correta, a solução foi encontrada
    } else {
        return 0; // caso o vetor atual nao seja igual ao objetivo, ele retorna 0, ou seja, a solução não foi encontrada
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

No* criaNo(int puzzle[3][3], int g, int h, No* parent) {
    No* novoNo = (No*)malloc(sizeof(No));
    memcpy(novoNo->puzzle, puzzle, sizeof(novoNo->puzzle));
    novoNo->g = g;
    novoNo->h = h;
    novoNo->f = g + h;
    novoNo->parent = parent;
    return novoNo;
}

int visitado(No* atual, int puzzle[3][3]) {
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

    No* openList[1000]; // Lista de nós a serem explorados
    int openCount = 0;

    No* inicioNo = criaNo(start, 0, heuristica(start), NULL);
    openList[openCount++] = inicioNo;

    while (openCount > 0) {
        // Encontrar o nó com menor f na openList
        int minIndex = 0;
        for (int i = 1; i < openCount; i++) {
            if (openList[i]->f < openList[minIndex]->f) {
                minIndex = i;
            }
        }

        No* atual = openList[minIndex];

        // Verificar se o objetivo foi alcançado
        if (avalia(atual->puzzle)) {
            printf("Solução encontrada!\n");
            while (atual != NULL) {
                print(atual->puzzle);
                atual = atual->parent;
            }
            return;
        }

        // Remover o nó atual da openList
        for (int i = minIndex; i < openCount - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openCount--;

        // Gerar os sucessores
        int zeroX, zeroY;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (atual->puzzle[i][j] == 0) {
                    zeroX = i;
                    zeroY = j;
                }
            }
        }

        int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Movimentos possíveis (cima, baixo, esquerda, direita)
        for (int i = 0; i < 4; i++) {
            int newX = zeroX + moves[i][0];
            int newY = zeroY + moves[i][1];

            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                int newPuzzle[3][3];
                memcpy(newPuzzle, atual->puzzle, sizeof(newPuzzle));
                // Trocar o espaço vazio com a posição adjacente
                newPuzzle[zeroX][zeroY] = newPuzzle[newX][newY];
                newPuzzle[newX][newY] = 0;

                if (visitado(atual, newPuzzle) != 1) {
                    No* successor = criaNo(newPuzzle, atual->g + 1, heuristica(newPuzzle), atual);
                    openList[openCount++] = successor;
                }
            }
        }
    }

    printf("Nenhuma solução encontrada.\n");
}


