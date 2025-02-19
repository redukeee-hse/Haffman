#include "Huffman.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

long int getFileLength(FILE *file) {
    if (!file) {
        std::cout << "File can't be opened" << std::endl;
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    return length;
}


bool comp(NODE *a, NODE *b) {
    return a->freq < b->freq;
}

vector<Node *> createHuffmanTree(int &treeSize, vector<Node *> &tree) {
    for (int i = 0; i < (treeSize - 1); i = i + 2) {
        tree.push_back((NODE *) malloc(sizeof(NODE)));
        tree[treeSize]->symbol = 0;
        tree[treeSize]->freq = (tree[i]->freq + tree[i + 1]->freq);
        tree[treeSize]->left = tree[i];
        tree[treeSize]->right = tree[i + 1];
        tree[i]->next = tree[treeSize];
        tree[i + 1]->next = tree[treeSize];
        treeSize++;
        stable_sort(tree.begin(), tree.end(), comp);
    }
    for (int i = 0; i < treeSize; ++i) {
        if (tree[i]->left == nullptr && tree[i]->right == nullptr)
            tree[i]->isSymbol = true;
    }
    return tree;
}

vector<Node *> initTree(long &length, int size, vector<Node *> &tree, FILE *file) {
    for (int i = 0; i < size; ++i) // Создание нод
    {
        //tree.push_back((Node*) malloc(sizeof(Node))); - ????????
        tree[i]->symbol = 0;
        tree[i]->freq = 0;
    }

    for (int i = 0; i < length; ++i) {
        char ch = fgetc(file);
        if (tree[(unsigned char) ch]->freq == 0)
            tree[(unsigned char) ch]->symbol = ch;

        tree[(unsigned char) ch]->freq++;
    }
    return tree;
}

void clearTree(int &treeSize, vector<Node *> &tree) {
    for (int i = 0; i < treeSize; ++i) // Чистка
    {
        if (tree[i]->freq == 0) {
            tree.erase(tree.begin() + i);
            i--;
            treeSize--;
        }
    }
}

