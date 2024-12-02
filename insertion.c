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

typedef struct spa {
    Node no;
    struct spa *next;
}Space;


// Function to insert a new_node in the result list.
Space *sortedInsert(Space *createNode, Space *sorted) {

    // Special case for the head end
    if (sorted == NULL ||
        sorted->no->f >= createNode->no->f) {
        createNode->next = sorted;
        sorted = createNode;
    }
    else {
        Space* curr = sorted;

        // Locate the node before the point of insertion
        while (curr->next != NULL && curr->next->no->val < createNode->no->val) {
            curr = curr->next;
        }
        createNode->next = curr->next;
        curr->next = createNode;
    }

    return sorted;
}

Space* insertionSort(Space* head) {

    // Initialize sorted linked list
    Space* sorted = NULL;
    Space* curr = head;

    // Traverse the given linked list and insert
    // every node to sorted
    while (curr != NULL) {

        // Store next for next iteration
        Space* next = curr->next;

        // Insert current in sorted linked list
        sorted = sortedInsert(curr, sorted);

        // Update current
        curr = next;
    }

    return sorted;
}

void printList(Space* curr) {
    while (curr != NULL) {
        printf(" %d", curr->no->f);
        curr = curr->next;
    }
}

Space* createNode(int x) {
    Space* node = (Space*)malloc(sizeof(Space));
    node->val = x;
    node->next = NULL;
    return node;
}

int main() {

    // Create a hard-coded linked list:
    // 5->4->1->3->2
    struct Node* head = createNode(5);
    head->next = createNode(4);
    head->next->next = createNode(1);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(2);

    head = insertionSort(head);

    printList(head);

    return 0;
}
