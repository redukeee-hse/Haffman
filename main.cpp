#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
int main() {
    FILE* file = fopen("saratov.txt", "rb");
    if (!file) {
        cout << "File can't be opened" << endl;
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long leng = ftell(file);
    fseek(file, 0, SEEK_SET);
    map<char,int> periodich;
    vector<pair<char, int>> sort_freq;
    for (int i = 0; i < leng; ++i)
    {
        periodich[fgetc(file)]++;
    }
    for (auto r = periodich.begin(); r!=periodich.end(); r++){
        sort_freq.push_back({r->first, r->second});
    }
    for (auto r = sort_freq.begin(); r!=sort_freq.end(); r++){
        cout << r->first << " "<< r->second << endl;
    }
    fclose(file);
    return 0;
}
