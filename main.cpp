#include "Huffman.h"
#include <chrono>
#include <time.h>

using namespace std;;
using namespace std::chrono;

int main() {
    system("chcp 65001"); // смена кодировки на UTF8 для консоли
    string inputFilename;
    cout << "Файл для чтения:  "; 
    cin >> inputFilename; // ввод имени файла

    clock_t tStart = clock(); // начало замера времени

    vector<Node *> nodes = readFileAndCreateNodes(inputFilename); //чтение файла и создание нода с частотой и символами

    auto huffmanTree = buildHuffmanTree(nodes); // дерево Хаффмана на векторе
    unordered_map<char, std::string> huffmanCodes; //создание неупорядоченного по ключам словаря

    if (!huffmanTree.empty()) { //пустое ли?
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes); // символ - код
    }
    else {
        exit(1);
    }


    string compressedFilename = "compressed_output.bin"; // Имя файла для сжатых данных
    writeEncodedFile(inputFilename, huffmanCodes, compressedFilename);
    printf("Time taken to encode: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); //окончание замера времени, вывод на экран

    string decodedOutput = "decoded" + inputFilename.substr(inputFilename.find_last_of('.')); //вторая функция берет расширение

    decode(decodedOutput, compressedFilename);
    printf("Time taken overall: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    for (auto node: nodes) {
        delete node;
    }

    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    return 0;
}
