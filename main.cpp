#include "Huffman.h"
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <time.h>

using namespace std;;
using namespace std::chrono;

int main() {
    system("chcp 65001");
    std::string inputFilename;
    std::cout << "Файл для чтения:  ";
    std::cin >> inputFilename;

    clock_t tStart = clock();

    std::vector<Node *> nodes = readFileAndCreateNodes(inputFilename);

    auto huffmanTree = buildHuffmanTree(nodes);
    std::unordered_map<char, std::string> huffmanCodes;

    if (!huffmanTree.empty()) {
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes);
    }


    std::string compressedFilename = "compressed_output.bin"; // Имя файла для сжатых данных
    writeEncodedFile(inputFilename, huffmanCodes, compressedFilename);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    for (Node *node: nodes) {
        delete node;
    }

    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    for (Node *node: nodes) {
        delete node;
    }
    if (!huffmanTree.empty()) {
        delete huffmanTree.back();
    }

    return 0;
}
