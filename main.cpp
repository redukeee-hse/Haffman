#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
int main() {
    FILE* file = fopen("saratov.txt", "rb");
    if (!file) {
        cout << "File can't be opened" << endl;
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long dlina = ftell(file);
    fseek(file, 0, SEEK_SET);
    map<char,int> periodich;
    for (int i = 0; i < dlina; ++i)
    {
        periodich[fgetc(file)]++;
    }
    for (auto r = periodich.begin(); r!=periodich.end(); r++){
        cout << r->first << " "<< r->second << endl;
    }
    fclose(file);
    return 0;
}
