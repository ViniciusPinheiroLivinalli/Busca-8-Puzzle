#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75

#define PROFUNDIDADE 5

void gerar(int *lista);
void print(int matriz[3][3]);
void sucessora(int movimento, int *i, int *j, int matriz[3][3]);
int avalia(int m_comparar[3][3]);
void menu_inicial(int *escolha);
void menu_IA(int *escolha);

//DFS ITERATIVA
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

//PILHA

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

int movimentoValido(int i, int j) {
    return i >= 0 && i < 3 && j >= 0 && j < 3;
}


//FUNÇÃO DFS
//int profIterativa(Estado estado);


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
        printf("\t\tO objetivo do 8-Puzzle é organizar os números de 1 a 8\n");
        printf("\t\tem ordem crescente, com o espaço vazio no último lugar.\n");
        printf("\t\tVocê pode mover o espaço vazio aos blocos adjacentes.\n\n\n\n\n\n\n\n\n\n\n");
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
            }
            else if(escolhaIA == 2){
                //DFS iterativa
                Pilha pilha;
                inicializarPilha(&pilha);
                Estado inicial = {
                .tabuleiro = {{m[0][0], m[0][1], m[0][2]},
                              {m[1][0], m[1][1], m[1][2]},
                              {m[2][0], m[2][1], m[2][2]}},
                .profundidade = 0,
                .pos_vazio_i = pos1,
                .pos_vazio_j = pos2
                };
                for(int limite = 0; limite < PROFUNDIDADE; limite++) {
                    empilhar(&pilha, inicial);
                    while(!pilhaVazia(&pilha)) {
                        Estado atual = desempilhar(&pilha);

                        if (avalia(atual.tabuleiro)) {
                            printf("Solução encontrada na profundidade %d\n", atual.profundidade);
                            print(atual.tabuleiro);
                            system("pause");
                            return;
                        }

                        if (atual.profundidade < limite) {
                            int movimentos_i[4] = {1, 0, -1, 0};
                            int movimentos_j[4] = {0, 1, 0, -1};
                            Estado novo = atual;
                            int vaz_i = novo.pos_vazio_i, vaz_j = novo.pos_vazio_j, mov_i = vaz_i, mov_j = vaz_j;

                            for (int m = 0; m < 4; m++) {

                                // Apenas realiza alterações se o movimento for válido
                                if (movimentoValido(mov_i + movimentos_i[m], mov_j + movimentos_j[m])) {
                                    mov_i += movimentos_i[m];
                                    mov_j += movimentos_j[m];
                                    // Realiza a troca no tabuleiro
                                    novo.tabuleiro[vaz_i][vaz_j] = novo.tabuleiro[mov_i][mov_j];
                                    novo.tabuleiro[mov_i][mov_j] = 0;

                                    // Atualiza a posição vazia
                                    novo.pos_vazio_i = mov_i;
                                    novo.pos_vazio_j = mov_j;

                                    // Incrementa a profundidade do estado
                                    novo.profundidade++;

                                    // Empilha o estado novo
                                    empilhar(&pilha, novo);

                                }

                                // Caso contrário, ignora o estado e não empilha
                                printf("\n\n\n\n\n");
                                print(novo.tabuleiro);
                                printf("\n\n\n\n");
                                printf("\t\t  i = %d | j = %d\n\n\n", novo.pos_vazio_i + 1, novo.pos_vazio_j + 1);
                                system("pause");
                                system("cls");
                            }
                        }

                    }
                }
            }
        }
        printf("\n\nParabéns você conseguiu encontrar a solução!!\n\n\n\n\n\n\n\n\n");
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
    else if (movimento == KEY_DOWN  && (*i) < 2) {
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

void menu_inicial(int *escolha){
    int tecla = 0;
    *escolha = 1;

    while (1) {
        system("cls");

        printf("\n\n\n\t\t\t   *******************     8 Puzzle   ********************\n");
        printf("\t\t\t   *                  | Selecione um Opção |                  *\n");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   * %s 8 Puzzle Manual                                       *\n", (*escolha == 1) ? "->" : "  ");
        printf("\t\t\t   * %s 8 Puzzle com Inteligência Artificial                  *\n", (*escolha == 2) ? "->" : "  ");
        printf("\t\t\t   *                                                          *\n");
        printf("\t\t\t   ************************************************************\n");

        tecla = getch();

        //NAVEGAÇÃO
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

        //NAVEGAÇÃO
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

/*int profIterativa(Estado estado){
    for(int limite = 0; limite < PROFUNDIDADE; limite++){
        Pilha pilha;
        inicializarPilha(&pilha);
        empilhar(&pilha, estado);

        while(!pilhaVazia(&pilha)) {
            Estado atual = desempilhar(&pilha);

            if(avalia(&atual)){
                printf("Solução encontrada na profundidade %d\n", atual.profundidade);
                return 1;
            }

            if(atual.profundidade < limite){

            }
        }
    }
} */

