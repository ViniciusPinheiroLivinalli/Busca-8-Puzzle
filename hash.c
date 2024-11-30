#include <glib.h>

// Inicializando o Hash Table
GHashTable* visitedStates = g_hash_table_new(g_str_hash, g_str_equal);

// Adicionando um estado
g_hash_table_insert(visitedStates, state, NULL);

// Verificando se um estado já foi visitado
if (g_hash_table_contains(visitedStates, state)) {
    printf("Estado já visitado.\n");
}

// Liberando memória
g_hash_table_destroy(visitedStates);
