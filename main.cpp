#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Huffman.h"
using namespace std;

#define SIZE    256
int main() {
    FILE* file = fopen("X:/Repositories/Haffman/cmake-build-debug/saratov.txt", "rb");
    
    FILE* fileForRead = fopen("X:/Repositories/Haffman/cmake-build-debug/saratov.txt", "rb");
    if (!file) {
        cout << "File can't be opened" << endl;
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long leng = ftell(file);
    fseek(file, 0, SEEK_SET);

    NODE* List[SIZE] = { NULL };
    for (int i = 0; i < SIZE; ++i)
    {
        List[i] = (NODE*)malloc(sizeof(NODE));
        List[i]->symbol = '\0';
        List[i]->freq = 0;
    }
    
    for (int i = 0; i < leng; ++i)
    {
        char ch = fgetc(fileForRead);

        List[(unsigned char)ch]->symbol = ch;
        List[(unsigned char)ch]->freq++;
        
    }
    puts("1");
    for (int i = 0; i < SIZE; ++i)
        cout << (int)List[i]->symbol << " " << List[i]->freq << "\n";

    fclose(file);
    return 0;
}
