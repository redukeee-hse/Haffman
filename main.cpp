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

    //NODE* List[SIZE] = { NULL }; //создали массив указателей на нод
    vector<NODE*> drevo;
    for (int i = 0; i < SIZE; ++i)
    {
        drevo.push_back((NODE*)malloc(sizeof(NODE))); //создали сами ноды
        drevo[i]->symbol = 0;
        drevo[i]->freq = 0;
    }

    for (int i = 0; i < leng; ++i)
    {
        char ch = fgetc(file);
        if (drevo[(unsigned char)ch]->freq == 0){
            drevo[(unsigned char)ch]->symbol = ch;
        }
        drevo[(unsigned char)ch]->freq++;
        
    }
    sort(drevo.begin(), drevo.end(), comp);
    for (int i = 0; i < SIZE; ++i)
        cout << drevo[i]->symbol << " " << drevo[i]->freq << "\n";

    fclose(file);
    return 0;
}
