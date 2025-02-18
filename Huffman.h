#ifndef HUFFMAN_H
#define HUFFMAN_H
#define CODE_SIZE   8
typedef struct Node
{
    bool isSymbol;
    char symbol;
    char code[CODE_SIZE];
    int freq;
    struct Node* left;
    struct Node* right;
    struct Node* next;
}NODE;
#endif // HUFFMAN_H

#ifndef COMP
#define COMP
bool comp(NODE* a, NODE* b);
#endif