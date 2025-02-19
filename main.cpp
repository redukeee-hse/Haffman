#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "Huffman.h"


using namespace std;
#define SIZE    256


int main() {
    const char *filename = "saratov.txt"; // Путь к файлу
    FILE *file = fopen(filename, "rb");

    long int length = getFileLength(file); // Длина файла

    vector<Node*> tree; // = initTree(length, SIZE, tree, file); // Создание дерева

    for (int i = 0; i < SIZE; ++i) // Создание нод
    {
        tree.push_back((Node*) malloc(sizeof(Node)));
        tree[i]->symbol = 0;
        tree[i]->freq = 0;
    }


    for (int i = 0; i < length; ++i) {
        char ch = fgetc(file);
        if (tree[(unsigned char) ch]->freq == 0)
            tree[(unsigned char) ch]->symbol = ch;

        tree[(unsigned char) ch]->freq++;
    }

    int treeSize = size(tree);

    stable_sort(tree.begin(), tree.end(), comp); // Сортируем вектор

    Node *root = createHuffmanTree(treeSize, tree)[treeSize - 1]; // Указание на корень

    cout << "root: " << root->freq << endl;

    fclose(file);
    return 0;
}
