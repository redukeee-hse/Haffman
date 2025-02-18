#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Huffman.h"
using namespace std;
#define SIZE    256
int main() {
    FILE* file = fopen("saratov.txt", "rb");
    if (!file) {
        cout << "File can't be opened" << endl;
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long leng = ftell(file);
    fseek(file, 0, SEEK_SET);

    NODE* List[SIZE] = { NULL }; //создали массив указателей на нод
    for (int i = 0; i < SIZE; ++i)
    {
        List[i] = (NODE*)malloc(sizeof(NODE)); //создали сами ноды
        List[i]->symbol = 0;
        List[i]->freq = 0;
    }

    for (int i = 0; i < leng; ++i)
    {
        char ch = fgetc(file);

        List[(unsigned char)ch]->symbol = ch;
        List[(unsigned char)ch]->freq++;
        
    }
    sort(List, List + SIZE, comp);

    for (int i = 0; i < SIZE; ++i)
        cout << List[i]->symbol << " " << List[i]->freq << "\n";

    fclose(file);
    return 0;
}
