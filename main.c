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

void gerar(int *lista); //Crio a função gerar
void print(int matriz[3][3]);
void loc(int matriz[3][3], int *i, int *j);
void sucessora(int movimento, int *i, int *j, int matriz[3][3]);
int avalia(int m_comparar[3][3]);

int main(){

    setlocale(LC_ALL,"portuguese");

    int tela[9], pos1 = 0, pos2 = 0, tecla; //Crio a variável do array (pode ser global se quiserem)
    char tela2[9];
    gerar(tela); //Com a função, transformo o array criado em uma tela resolvível
    int retorno = 0;
    int m[3][3], pos = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            m[i][j] = tela[pos];
            pos++;
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

    while(retorno

    != 1){ //O while dura enquanto o jogo terminar (falta a função objetivo)


        printf("\n\n\n\n\n");
        print(m);
        printf("\n\n\n\n");
        loc(m, &pos1, &pos2);
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

    return 0;
}

void gerar(int *lista){ //Defino a variável gerar

    int valor = 0; //Crio a variável valor já no começo, pois ela será o valor lógico do While
    srand(time(NULL)); // Inicializa o gerador de números aleatórios (Utilizando o fator random do relógio do computador)
    while (valor != 1){

        // GERAR LISTA:
        int i, j, temp; // Definição de variáveis
        // Inicializa a lista com valores aleatórios:
        for (i = 0; i < 9; i++) {
            lista[i] = i; // inicializa a lista com valores de 0 a 9
        }
        // Embaralha a lista utilizando um algoritmo de Fisher-Yates
        for (i = 8; i > 0; i--) {
            j = rand() % (i + 1); // gera um índice aleatório
            temp = lista[i];
            lista[i] = lista[j];
            lista[j] = temp; // troca os valores
        }


        //CALCULAR INVERSÕES:

        int inv = 0; //Defino a variável que contará o número de inversões
        for(int i = 0; i < 8; i++)
        {
            for(int j = i + 1; j < 9; j++ ) //Crio um for dentro de outro para verificar todas as combinações de dois valores do array
            {
                if(lista[i] > lista[j] && lista[i] != 0 && lista[j] != 0) //Se houverem inversões de posição (Um valor maior que o outro na lista) e diferente de 0 (Zero é o vazio):
                {
                    inv++; //Adiciono +1 na contagem de reversões
                }
            }
        }

        //VALIDAR
        for(int i = 0; i < 9; i++){ //Crio um for para ler a lista
            if(lista[i] == 0){ //Acho o vazio
                if((i+1) % 2 == 0 && inv % 2 == 0){ //Verifico se a posição inicial do vazio é par e se o número de inversões também é
                    valor = 1; //Caso seja, a tela gerada é válida
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

void loc(int matriz[3][3], int *i, int *j){
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            if(matriz[x][y] == 0){
                *i = x;
                *j = y;
            }
        }
    }

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
