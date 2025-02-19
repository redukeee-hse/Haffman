#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <vector>

using namespace std;

#define CODE_SIZE   256
typedef struct Node {
    bool isSymbol;
    char symbol;
    char code[CODE_SIZE];
    int freq;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} NODE;

bool comp(NODE *a, NODE *b);

long int getFileLength(FILE *file);

vector<Node *> createHuffmanTree(int &treeSize, vector<Node *> &tree);

//  vector<Node *> initTree(long &length, int size, vector<Node *> &tree, FILE *file);

// void clearTree(int &treeSize, vector<Node *> &tree);

#endif // HUFFMAN_H