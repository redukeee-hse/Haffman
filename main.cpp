#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include "Huffman.h"

using namespace std;

#define SIZE    256



int main() {  
    const char* filename = "saratov.txt"; // Путь к файлу
    FILE *file = fopen(filename, "rb"); 

    long int length = getFileLength(file); // Длина файла 

   
    //NODE* List[SIZE] = { NULL }; //создали массив указателей на нод
    vector<NODE*> tree; //саратов, я тебе не прощу то, что ты мое древо поменял на какое-то три....... иди в жопу
    for (int i = 0; i < SIZE; ++i)
    {
        tree.push_back((NODE*)malloc(sizeof(NODE))); //создали сами ноды
        tree[i]->symbol = 0;
        tree[i]->freq = 0;
    }

    for (int i = 0; i < length; ++i)
    {
        char ch = fgetc(file);
        if (tree[(unsigned char)ch]->freq == 0){
            tree[(unsigned char)ch]->symbol = ch;
        }
        tree[(unsigned char)ch]->freq++;
        
    }
    auto sizetree = size(tree); // штоб по сто раз не напрягался проц
    for (int i = 0; i < sizetree; ++i) // удалили пустышки
    {
        if (tree[i]->freq == 0)
        {
            tree.erase(tree.begin() + i);
            i--;
            sizetree--;
        }
    }
    stable_sort(tree.begin(), tree.end(), comp);
    //for (int i = 0; i < size(tree); ++i)
        //cout << tree[i]->symbol << " " << tree[i]->freq << "\n";
    // cout << size(tree) << endl;
    for (int i = 0; i < (sizetree - 1); i = i + 2)
    {
        tree.push_back((NODE*)malloc(sizeof(NODE)));
        tree[sizetree]->symbol = 0;
        tree[sizetree]->freq = (tree[i]->freq + tree[i + 1]->freq);
        tree[sizetree]->left = tree[i];
        tree[sizetree]->right = tree[i+1];
        tree[i]->next = tree[sizetree];
        tree[i + 1]->next = tree[sizetree];
        sizetree++;
        stable_sort(tree.begin(), tree.end(), comp);
    }
    for (int i = 0; i < size(tree); ++i)
        cout << tree[i]->symbol << " " << tree[i]->freq << "\n";
    fclose(file);
    return 0;
}
