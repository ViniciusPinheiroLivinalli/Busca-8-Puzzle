// C program to sort linked list using insertion sort
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int puzzle[3][3]; //estado
    int g; // Custo do caminho até agora
    int h; // Valor da heurística
    int f; // Custo total (f = g + h)
    struct node *parent; // Ponteiro para o estado pai
} Node;

typedef struct noOrd {
    Node *no;
    struct noOrd *next;
}noOrdenado;


// Function to insert a new_node in the result list.
noOrdenado *sortedInsert(noOrdenado *createNode, noOrdenado *sorted) {

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
        createNode->next = curr->nex 211 1t;
        curr->next = createNode;
    }

    return sorted;
}

noOrdenado* insertionSort(noOrdenado* head) {

    // Initialize sorted linked list
    noOrdenado * sorted = NULL;
    noOrdenado * curr = head;

    // Traverse the given linked list and insert
    // every node to sorted
    while (curr != NULL) {

        // Store next for next iteration
        noOrdenado* next = curr->next;

        // Insert current in sorted linked list
        sorted = sortedInsert(curr, sorted);

        // Update current
        curr = next;
    }

    return sorted;
}

void printList(noOrdenado* curr) {
    while (curr != NULL) {
        printf(" %d", curr->no->f);
        curr = curr->next;
    }
}

noOrdenado* createNode(int x) {
    noOrdenado* node = (noOrdenado*)malloc(sizeof(noOrdenado));
    node->no = (Node*)malloc(sizeof(Node));
    node->no->f = x;
    node->next = NULL;
    return node;
}

int main() {

    // Create a hard-coded linked list:
    // 5->4->1->3->2
    noOrdenado* head = createNode(5);
//    head->next = createNode(4);
//    head->next->next = createNode(1);
//    head->next->next->next = createNode(3);
//    head->next->next->next->next = createNode(2);
//
//    head = insertionSort(head);

    head = sortedInsert(createNode(2), head);
    head = sortedInsert(createNode(9), head);
    head = sortedInsert(createNode(2), head);

    printList(head);

    return 0;
}
