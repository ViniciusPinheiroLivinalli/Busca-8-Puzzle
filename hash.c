// C program to sort linked list using insertion sort
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 10007 // Um número primo para reduzir colisões
typedef struct node{
    int puzzle[3][3]; //estado
    int g; // Custo do caminho até agora
    int h; // Valor da heurística
    int f; // Custo total (f = g + h)
    struct node *parent; // Ponteiro para o estado pai
} Node;

typedef struct HashNode {
    unsigned int hashValue;    // Valor hash do estado
    struct HashNode* next;     // Encadeamento para colisões
} HashNode;

typedef struct {
    HashNode* buckets[HASH_TABLE_SIZE];
} HashSet;

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

int main() {

    HashSet* visitedStates = createHashSet();

    int puzzle1[3][3] = {
        {1, 2, 3},
        {4, 0, 5},
        {7, 8, 6}
    };

    int puzzle2[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    // Calcular hashes
    unsigned int hash1 = computeHash(puzzle1);
    unsigned int hash2 = computeHash(puzzle2);

    // Inserir estados
    insertHash(visitedStates, hash1);

    // Verificar estados
    if (containsHash(visitedStates, hash1)) {
        printf("Estado 1 já visitado.\n");
    } else {
        printf("Estado 1 não foi visitado.\n");
    }

    if (containsHash(visitedStates, hash2)) {
        printf("Estado 2 já visitado.\n");
    } else {
        printf("Estado 2 não foi visitado.\n");
    }

    // Liberar memória
    freeHashSet(visitedStates);


    return 0;
}
