#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int value;
    struct Node* firstChild;
    struct Node* nextSibling;
} Node;

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Deklarace funkce:
Node* parseTree(const char* str, int* pos);

// Pomocná funkce pro načtení čísla ze řetězce
int readNumber(const char* str, int* pos) {
    int num = 0;
    while (isdigit(str[*pos])) {
        num = num * 10 + (str[*pos] - '0');
        (*pos)++;
    }
    return num;
}

Node* parseTree(const char* str, int* pos) {
    // Očekáváme, že aktuální znak je '('
    if (str[*pos] != '(') return NULL;
    (*pos)++;  // přeskočíme '('

    // Přečteme hodnotu uzlu
    int value = readNumber(str, pos);
    Node* node = createNode(value);

    // Zpracujeme všechny potomky: každé dítě začíná '('
    Node* lastChild = NULL;
    while (str[*pos] == '(') {
        Node* child = parseTree(str, pos);
        if (!node->firstChild) {
            node->firstChild = child;
        } else {
            lastChild->nextSibling = child;
        }
        lastChild = child;
    }

    // Očekáváme uzavírací závorku ')'
    if (str[*pos] == ')') {
        (*pos)++;  // přeskočíme ')'
    }
    return node;
}