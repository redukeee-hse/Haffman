#include "Huffman.h"
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <bitset>
#include <time.h>
#include <bitset>

using namespace std;

vector<Node *> buildHuffmanTree(vector<Node *> &nodes) {
    if (nodes.empty()) // пустой ли файл
        exit(1);

    vector<Node *> huffmanNodes = nodes; // создание доп вектора, из которого будем удалять обработанные элементы

    while (huffmanNodes.size() > 1) { 
        auto left = huffmanNodes[0];
        auto right = huffmanNodes[1];

        Node *newNode = new Node('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        huffmanNodes.erase(huffmanNodes.begin(), huffmanNodes.begin() + 2); //стираем обработанные

        auto position = lower_bound(huffmanNodes.begin(), huffmanNodes.end(), newNode, 
                                    [](Node *a, Node *b) { return a->frequency < b->frequency; }); //лямбда функция, условие сортировки
//определяем позицию для нового нода. lower bound ищет первое не меньшее элемента 
// и возвращает позицию, таким образом новый элемент будет всегда слева равных ему
        huffmanNodes.insert(position, newNode);
    }

    return huffmanNodes;
}

void generateHuffmanCodes(Node *root, const string &code, unordered_map<char, string> &huffmanCodes) {
    if (!root)
        return;

    if (root->symbol != '\0') {
        huffmanCodes[root->symbol] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

vector<Node *> readFileAndCreateNodes(const string &filename) {
    ifstream file(filename);
    unordered_map<char, int> frequencyMap; 
    
    // if (file) {
    //     string line;
    //     while (getline(file, line)) {
    //         for (char ch: line)
    //             frequencyMap[ch]++;
    //     }
    //     file.close(); // без /n 


    if (file) {
        char ch;
        while (file.get(ch)) { //get берет символ, записывает в ch и сдвигает указатель в файле
            frequencyMap[ch]++;
        }
        file.close(); // с /n
    
    } else {
        cerr << "файл не открылся :( " << filename << endl;
        exit(1);
    }

    vector<Node *> nodes;
    for (const auto &pair: frequencyMap)
        nodes.push_back(new Node(pair.first, pair.second));
    sort(nodes.begin(), nodes.end(), [](Node *a, Node *b) { return a->frequency < b->frequency; });

    return nodes;
}

void writeEncodedFile(const string &inputFilename, const unordered_map<char, string> &huffmanCodes,
    const string &compressedFilename) {
    ifstream inputFile(inputFilename);
    ofstream compressedFile(compressedFilename, std::ios::binary);
    // FILE* inputFile = fopen(inputFilename.c_str(), "r");
    // FILE* compressedFile = fopen(compressedFilename.c_str(), "wb");

    if (!inputFile) {
        cerr << "Не удалось открыть файл для чтения: " << inputFilename << endl;
        return;
    }

    if (!compressedFile) {
        cerr << "Не удалось открыть файл для сжатых данных: " << compressedFilename << endl;
        return;
    }

    string expansion = inputFilename.substr(inputFilename.find_last_of('.') + 1);
    int pairs = huffmanCodes.size();


    compressedFile << pairs << "\n";
    compressedFile << expansion << "\n";

    // Запись кодов символов в файл
    for (const auto &pair : huffmanCodes) {
        compressedFile << pair.first << pair.second << "\n"; // Символ и его код
    }

    char ch;
    string encodedStr = "";
    while (inputFile.get(ch)) {
        auto it = huffmanCodes.find(ch);
        if (it != huffmanCodes.end()) {
            encodedStr += it->second;
        }
    }

    // Запись сжатых данных в двоичный файл
    size_t bitIndex = 0;
    vector<unsigned char> buffer;
    int countByts;

    while (bitIndex < encodedStr.size()) {
        unsigned char byte = 0;
        for (int i = 0; i < 8 && bitIndex < encodedStr.size(); ++i, ++bitIndex) {
        byte = (byte << 1) | (encodedStr[bitIndex] == '1' ? 1 : 0);
        countByts = i;
    }
    buffer.push_back(byte);
    }
    compressedFile << countByts << "\n";

    compressedFile.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    compressedFile.close();
    inputFile.close();

    cout << "Сжатые данные были записаны в файл: " << compressedFilename << endl;
}

void decode(const string &outputFilename, const string &compressedFilename) {
    FILE* file = fopen(compressedFilename.c_str(), "rb");
    FILE* fin = fopen(outputFilename.c_str(), "wb");

    unordered_map<string, char> codes;

    char* pairs = (char*)calloc(50, sizeof(char)); // количество пар вида символ - код
    fgets(pairs, 50, file);
    pairs[strlen(pairs) - 1] = '\0'; 

    char* exp = (char*)calloc(4, sizeof(char)); // расширение
    fgets(exp, 4, file);
    exp[strlen(exp) - 1] = '\0';

    int pairss = stoi(pairs);
    fgetc(file); // перенос строки
    
    for (int i = 0; i < pairss; i++) {
        char symb = fgetc(file);
        char c;
        string code;
        while ((c = fgetc(file)) != '\n') {
            code += c;
        }
        
        codes.insert({code, symb});
    }

    int mainByts = fgetc(file) - '0';
    fgetc(file); // перенос строки

    char c;
    string buff = "";

    while (!feof(file)) {
        c = fgetc(file);
        bitset<8> bs(c);
        for (int j = 7; j >= 0; j--){
            if (bs[j] == 1){
                buff += "1";
            } else {
                buff += "0";
            }

            if (codes.find(buff) != codes.end()) {
                char curr = codes.find(buff)->second;
                fputc(curr, fin);
                buff.clear();
            }
        }
    }

    const int lastByteEffectiveBit = 1 ;
    bitset<lastByteEffectiveBit> bs(mainByts);
    for (int j = lastByteEffectiveBit - 1; j >= 0; j--){
        if (bs[j] == 1){
            buff += "1";
        } else {
            buff += "0";
        }
        if (codes.find(buff.c_str()) != codes.end()){
        
            char curr = codes.find(buff)->second;
            fputc(curr, fin);
            buff.clear(); 
        }
    }

    fclose(file);
    fclose(fin);
}
