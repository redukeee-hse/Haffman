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
    const char* filename = "X:/Repositories/Haffman/cmake-build-debug/saratov.txt"; // Путь к файлу  
    FILE *file = fopen(filename, "rb"); 

    long int length = getFileLength(file); // Длина файла 

   
    //NODE* List[SIZE] = { NULL }; //создали массив указателей на нод
    vector<NODE*> tree;
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
    sort(tree.begin(), tree.end(), comp);
    for (int i = 0; i < SIZE; ++i)
        cout << tree[i]->symbol << " " << tree[i]->freq << "\n";

    fclose(file);
    return 0;
}
