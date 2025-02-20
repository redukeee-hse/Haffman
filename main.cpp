#include "Huffman.h"
#include <iostream>
#include <unordered_map>

int main() {
    system("chcp 65001");
    std::string inputFilename;
    std::cout << "Типочек, ну ка файлик дай:  ";
    std::cin >> inputFilename;

    std::vector<Node *> nodes = readFileAndCreateNodes(inputFilename);

    auto huffmanTree = buildHuffmanTree(nodes);
    std::unordered_map<char, std::string> huffmanCodes;

    if (!huffmanTree.empty()) {
        generateHuffmanCodes(huffmanTree.back(), "", huffmanCodes);
    }


    std::string compressedFilename = "compressed_output.bin"; // Имя файла для сжатых данных
    writeEncodedFile(inputFilename, huffmanCodes, compressedFilename);

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
